#include "stdafx.h"
#include "..\include\Serializer.h"
#include "..\..\MetaData\include\IContainer.h"
#include "..\..\MetaData\include\SimpleString.h"
#include "..\..\include\CharArray.h"

#define D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE		(0x00000001)
#define D_SERIALIZER_ENTITY_TAG_BASE_TYPE			(0x00000002)

#define D_SERIALIZER_ICONTAINER_ELE_NAME	"Ele_of_IContainer"

//CSerializer
CSerializer::CSerializer(void)
	:m_pTreeSerial(NULL)
{
}

CSerializer::~CSerializer(void)
{
}

void CSerializer::SetSerial(ISerial *pSerial)
{
	if (pSerial)
	{
		IInterface *pIntf;
		if (pSerial->QueryInterface("ITreeSerial", &pIntf))
		{
			m_pTreeSerial = reinterpret_cast<ITreeSerial*>(pIntf);
		}
		else
		{
			m_pTreeSerial = NULL;
		}
	}
	else
	{
		m_pTreeSerial = NULL;
	}
}

bool CSerializer::DoSerialize(CMetaDataType *pType, void *pObj, const char *pName)
{
	if (!pType || !pObj || !m_pTreeSerial || !m_pTreeSerial->Root()) return false;

	ISerialEntity *pEnt;
	m_pTreeSerial->Root()->ClearChildren();
	switch(pType->GetTypeID())
	{
	case D_META_DATA_TYPE_ID_CLASS_TYPE:
		pEnt = m_pTreeSerial->Root()->NewChild();
		pEnt->SetName(pName);
		return SerializeCustomTypeWrapper(reinterpret_cast<CMetaDataCustomType*>(pType), pObj, pEnt, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
	case D_META_DATA_TYPE_ID_INNER_TYPE:
		pEnt = m_pTreeSerial->Root()->NewChild();
		pEnt->SetName(pName);
		return SerializeInnerType(reinterpret_cast<CMetaDataInnerType*>(pType), pObj, pEnt);
	default:
		break;
	}
	return false;
}

bool CSerializer::DoUnserialize(CMetaDataType *pType, void *pObj, const char *pName)
{
	if (!pType || !pObj || !m_pTreeSerial || !m_pTreeSerial->Root()) return false;

	CCharArray TypeName(256);
	ISerialEntity *pEnt;
	if (!pType->GetFullName(TypeName.char_array(), 256))
	{
		return false;
	}
	pEnt = m_pTreeSerial->Root()->FindChild(pName, TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
	if (!pEnt)
	{
		return false;
	}
	switch(pType->GetTypeID())
	{
	case D_META_DATA_TYPE_ID_CLASS_TYPE:
		return UnserializeCustomType(pEnt, reinterpret_cast<CMetaDataCustomType*>(pType), pObj, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
	case D_META_DATA_TYPE_ID_INNER_TYPE:
		return UnserializeInnerType(pEnt, reinterpret_cast<CMetaDataInnerType*>(pType), pObj);
	default:
		break;
	}
	return false;
}

bool CSerializer::SerializeCustomTypeWrapper(CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, unsigned int EntTag)
{
	if (TypeTraits<SimpleString>::GetMetaDataType() != pType)
	{
		return SerializeCustomType(pType, pObj, pSEntity, EntTag);
	}
	else
	{
		CCharArray TypeName(256);
		SimpleString *pStr(reinterpret_cast<SimpleString*>(pObj));
		if (!pType->GetFullName(TypeName.char_array(), 256))
		{
			return false;
		}
		pSEntity->SetEntTypeName(TypeName.char_array());
		pSEntity->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
		pSEntity->SetValue(pStr->GetValue());
		return true;
	}
}

bool CSerializer::SerializeCustomType(CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, unsigned int EntTag)
{
	IInterface *pIntf;
	unsigned int i;
	CMetaDataCustomType *pCustomType;
	CMetaDataCustomTypeMemberVar *pMemVar;
	ISerialEntity *pChild;
	void *pO;
	CCharArray TypeName(256);

	if (!pType->GetFullName(TypeName.char_array(), 256))
	{
		return false;
	}

	pSEntity->SetEntTypeName(TypeName.char_array());
	pSEntity->SetTag(EntTag);

	//基类数据序列化
	for (i = 0; i < pType->GetBaseTypeCount(); ++i)
	{
		pCustomType = pType->GetBaseType(i);
		pChild = pSEntity->NewChild();
		pChild->SetName(pCustomType->GetName());
		pO = reinterpret_cast<void*>((reinterpret_cast<unsigned int>(pObj) + pType->GetBaseTypeOffset(i)));
		if (!SerializeCustomTypeWrapper(pCustomType, pO, pChild, D_SERIALIZER_ENTITY_TAG_BASE_TYPE))
		{
			pSEntity->DelChild(pChild);
			return false;
		}
	}

	//IContainer元素序列化
	if (pType->QueryInterface(pObj, "IContainer", &pIntf))
	{
		IContainer *pContainter(reinterpret_cast<IContainer*>(pIntf));
		if (pContainter->GetItemType())
		{
			for (i = 0; i < pContainter->Count(); ++i)
			{
				pO = pContainter->GetItem(i);
				if (!pO) continue;
				pChild = pSEntity->NewChild();
				pChild->SetName(D_SERIALIZER_ICONTAINER_ELE_NAME);
				switch (pContainter->GetItemType()->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
					if (!SerializeCustomTypeWrapper(reinterpret_cast<CMetaDataCustomType*>(pContainter->GetItemType()), pO, pChild, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE))
					{
						pSEntity->DelChild(pChild);
						return false;
					}
					break;
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					if (!SerializeInnerType(reinterpret_cast<CMetaDataInnerType*>(pContainter->GetItemType()), pO, pChild))
					{
						pSEntity->DelChild(pChild);
						return false;
					}
					break;
				default:
					break;
				}
			}
		}
	}

	//成员变量序列化
	for (i = 0; i < pType->GetMemberVarCount(); ++i)
	{
		pMemVar = pType->GetMemberVar(i);
		pChild = pSEntity->NewChild();
		pChild->SetName(pMemVar->GetName());
		if (pMemVar->GetPtrLevel() == 0)
		{
			pO = reinterpret_cast<void*>((reinterpret_cast<unsigned int>(pObj) + pMemVar->GetOffset()));
		}
		else if (pMemVar->GetPtrLevel() == 1)
		{
			pO = *reinterpret_cast<void**>((reinterpret_cast<unsigned int>(pObj) + pMemVar->GetOffset()));
		}
		else continue;
		switch(pMemVar->GetMDType()->GetTypeID())
		{
		case D_META_DATA_TYPE_ID_CLASS_TYPE:
			if (!SerializeCustomTypeWrapper(reinterpret_cast<CMetaDataCustomType*>(pMemVar->GetMDType()), pO, pChild, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE))
			{
				pSEntity->DelChild(pChild);
				return false;
			}
			break;
		case D_META_DATA_TYPE_ID_INNER_TYPE:
			if (!SerializeInnerType(reinterpret_cast<CMetaDataInnerType*>(pMemVar->GetMDType()), pO, pChild))
			{
				pSEntity->DelChild(pChild);
				return false;
			}
			break;
		default:
			pSEntity->DelChild(pChild);
			return false;
		}
	}

	return true;
}

bool CSerializer::SerializeInnerType(CMetaDataInnerType *pType, void *pObj, ISerialEntity *pSEntity)
{
	bool ret(true);
	CCharArray TypeName(256);

	if (!pType->GetFullName(TypeName.char_array(), 256))
	{
		return false;
	}

	pSEntity->SetEntTypeName(TypeName.char_array());
	pSEntity->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);

	if (pType == TypeTraits<char>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<char*>(pObj));
	}
	else if (pType == TypeTraits<short>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<short*>(pObj));
	}
	else if (pType == TypeTraits<long>::GetMetaDataType())
	{
		pSEntity->SetValue((long)*reinterpret_cast<long*>(pObj));
	}
	else if (pType == TypeTraits<int>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<int*>(pObj));
	}
	else if (pType == TypeTraits<unsigned char>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<unsigned char*>(pObj));
	}
	else if (pType == TypeTraits<unsigned short>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<unsigned short*>(pObj));
	}
	else if (pType == TypeTraits<unsigned long>::GetMetaDataType())
	{
		pSEntity->SetValue((long long)*reinterpret_cast<unsigned long*>(pObj));
	}
	else if (pType == TypeTraits<unsigned int>::GetMetaDataType())
	{
		pSEntity->SetValue((long long)*reinterpret_cast<unsigned int*>(pObj));
	}
	else if (pType == TypeTraits<float>::GetMetaDataType())
	{
		pSEntity->SetValue((long double)*reinterpret_cast<float*>(pObj));
	}
	else if (pType == TypeTraits<double>::GetMetaDataType())
	{
		pSEntity->SetValue((long double)*reinterpret_cast<double*>(pObj));
	}
	else if (pType == TypeTraits<bool>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<bool*>(pObj));
	}
	else ret = false;

	return ret;
}

bool CSerializer::UnserializeCustomTypeWrapper(ISerialEntity *pSEntity, CMetaDataCustomType *pType, void *pObj, unsigned int EntTag)
{
	if (TypeTraits<SimpleString>::GetMetaDataType() != pType)
	{
		return UnserializeCustomType(pSEntity, pType, pObj, EntTag);
	}
	else
	{
		CCharArray TypeName(256);
		if (!pType->GetFullName(TypeName.char_array(), 256))
		{
			return false;
		}
		if (strcmp(TypeName.char_array(), pSEntity->GetEntTypeName()) == 0
			&& EntTag == pSEntity->GetTag()
			&& pSEntity->GetValue().type == vtSTR_PTR)
		{
			SimpleString *pStr(reinterpret_cast<SimpleString*>(pObj));
			pStr->SetValue(pSEntity->GetValue().value._pstr);
			return true;
		}
		else return false;
	}
}

bool CSerializer::UnserializeCustomType(ISerialEntity *pSEntity, CMetaDataCustomType *pType, void *pObj, unsigned int EntTag)
{
	IInterface *pIntf;
	unsigned int i;
	CMetaDataCustomType *pCustomType;
	CMetaDataCustomTypeMemberVar *pMemVar;
	ISerialEntity *pChild;
	void *pO;
	CCharArray TypeName(256);

	if (!pType->GetFullName(TypeName.char_array(), 256))
	{
		return false;
	}
	if (strcmp(TypeName.char_array(), pSEntity->GetEntTypeName()) != 0 || EntTag != pSEntity->GetTag()) return false;

	//基类数据反序列化
	for (i = 0; i < pType->GetBaseTypeCount(); ++i)
	{
		pCustomType = pType->GetBaseType(i);
		if (!pCustomType->GetFullName(TypeName.char_array(), 256))
		{
			continue;
		}
		pChild = pSEntity->FindChild(pCustomType->GetName(), TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_BASE_TYPE);
		if (pChild)
		{
			pO = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(pObj) + pType->GetBaseTypeOffset(i));
			if (!UnserializeCustomTypeWrapper(pChild, pCustomType, pO, D_SERIALIZER_ENTITY_TAG_BASE_TYPE))
			{
				return false;
			}
		}
	}

	//IContainer元素反序列化
	if (pType->QueryInterface(pObj, "IContainer", &pIntf))
	{
		IContainer *pContainter(reinterpret_cast<IContainer*>(pIntf));
		if (pContainter->GetItemType())
		{
			if (!pContainter->GetItemType()->GetFullName(TypeName.char_array(), 256))
			{
				return false;
			}
			for (i = 0; i < pSEntity->GetChildrenCount(); ++i)
			{
				pChild = pSEntity->GetChildren(i);
				if (strcmp(TypeName.char_array(), pChild->GetEntTypeName()) != 0
					|| strcmp(D_SERIALIZER_ICONTAINER_ELE_NAME, pChild->GetName()) != 0)
					continue;

				pO = NewObject(pContainter->GetItemType());
				if (!pO) return false;
				pContainter->AddItem(pO);
				
				switch (pContainter->GetItemType()->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
					if (!UnserializeCustomTypeWrapper(pChild, reinterpret_cast<CMetaDataCustomType*>(pContainter->GetItemType()), pO, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE))
					{
						return false;
					}
					break;
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					if (!UnserializeInnerType(pChild, reinterpret_cast<CMetaDataInnerType*>(pContainter->GetItemType()), pO))
					{
						return false;
					}
					break;
				default:
					return false;
				}
			}
		}
	}

	//成员变量反序列化
	for (i = 0; i < pType->GetMemberVarCount(); ++i)
	{
		pMemVar = pType->GetMemberVar(i);
		if (!(pMemVar->GetMDType()) || !(pMemVar->GetMDType()->GetFullName(TypeName.char_array(), 256)))
		{
			continue;
		}
		pChild = pSEntity->FindChild(pMemVar->GetName(), TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
		if (pChild)
		{
			if (pMemVar->GetPtrLevel() == 0)
			{
				pO = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(pObj) + pMemVar->GetOffset());
			}
			else if (pMemVar->GetPtrLevel() == 1)
			{
				pO = NewObject(pMemVar->GetMDType());
				if (pO)
				{
					*reinterpret_cast<void**>(reinterpret_cast<unsigned int>(pObj) + pMemVar->GetOffset()) = pO;
				}
				else return false;
			}
			else continue;
		}
		else return false;
		switch(pMemVar->GetMDType()->GetTypeID())
		{
		case D_META_DATA_TYPE_ID_CLASS_TYPE:
			if (!UnserializeCustomTypeWrapper(pChild, reinterpret_cast<CMetaDataCustomType*>(pMemVar->GetMDType()), pO, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE))
			{
				return false;
			}
			break;
		case D_META_DATA_TYPE_ID_INNER_TYPE:
			if (!UnserializeInnerType(pChild, reinterpret_cast<CMetaDataInnerType*>(pMemVar->GetMDType()), pO))
			{
				return false;
			}
			break;
		default:
			return false;
		}
	}

	return true;
}

bool CSerializer::UnserializeInnerType(ISerialEntity *pSEntity, CMetaDataInnerType *pType, void *pObj)
{
	bool ret(true);
	SVariant var;
	CCharArray TypeName(256);

	if (!pType->GetFullName(TypeName.char_array(), 256))
	{
		return false;
	}
	if (strcmp(TypeName.char_array(), pSEntity->GetEntTypeName()) != 0) return false;

	var = pSEntity->GetValue();
	if (pType == TypeTraits<char>::GetMetaDataType())
	{
		*reinterpret_cast<char*>(pObj) = (char)var.value._i;
	}
	else if (pType == TypeTraits<short>::GetMetaDataType())
	{
		*reinterpret_cast<short*>(pObj) = (short)var.value._i;
	}
	else if (pType == TypeTraits<long>::GetMetaDataType())
	{
		*reinterpret_cast<long*>(pObj) = (long)var.value._i;
	}
	else if (pType == TypeTraits<int>::GetMetaDataType())
	{
		*reinterpret_cast<int*>(pObj) = var.value._i;
	}
	else if (pType == TypeTraits<unsigned char>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned char*>(pObj) = (unsigned char)var.value._i;
	}
	else if (pType == TypeTraits<unsigned short>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned short*>(pObj) = (unsigned short)var.value._i;
	}
	else if (pType == TypeTraits<unsigned long>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned long*>(pObj) = (unsigned long)var.value._i;
	}
	else if (pType == TypeTraits<unsigned int>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned int*>(pObj) = (unsigned int)var.value._i;
	}
	else if (pType == TypeTraits<float>::GetMetaDataType())
	{
		*reinterpret_cast<float*>(pObj) = (float)var.value._d;
	}
	else if (pType == TypeTraits<double>::GetMetaDataType())
	{
		*reinterpret_cast<double*>(pObj) = var.value._d;
	}
	else if (pType == TypeTraits<bool>::GetMetaDataType())
	{
		*reinterpret_cast<bool*>(pObj) = var.value._b;
	}
	else ret = false;

	return ret;
}

void *CSerializer::NewObject(CMetaDataType *pType)
{
	if (!pType) return NULL;

	void *pO(pType->NewObject());

	if (!pO)
	{
		if (pType == TypeTraits<char>::GetMetaDataType())
		{
			pO = new char;
		}
		else if (pType == TypeTraits<short>::GetMetaDataType())
		{
			pO = new short;
		}
		else if (pType == TypeTraits<long>::GetMetaDataType())
		{
			pO = new long;
		}
		else if (pType == TypeTraits<int>::GetMetaDataType())
		{
			pO = new int;
		}
		else if (pType == TypeTraits<unsigned char>::GetMetaDataType())
		{
			pO = new unsigned char;
		}
		else if (pType == TypeTraits<unsigned short>::GetMetaDataType())
		{
			pO = new unsigned short;
		}
		else if (pType == TypeTraits<unsigned long>::GetMetaDataType())
		{
			pO = new unsigned long;
		}
		else if (pType == TypeTraits<unsigned int>::GetMetaDataType())
		{
			pO = new unsigned int;
		}
		else if (pType == TypeTraits<float>::GetMetaDataType())
		{
			pO = new float;
		}
		else if (pType == TypeTraits<double>::GetMetaDataType())
		{
			pO = new double;
		}
		else if (pType == TypeTraits<bool>::GetMetaDataType())
		{
			pO = new bool;
		}
		else if (pType == TypeTraits<SimpleString>::GetMetaDataType())
		{
			pO = new SimpleString;
		}
	}

	return pO;
}
