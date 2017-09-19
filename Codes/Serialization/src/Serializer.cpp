#include "stdafx.h"
#include "..\include\Serializer.h"
#include "..\..\MetaData\include\IContainer.h"
#include "..\..\MetaData\include\SimpleString.h"
#include "..\..\include\CharArray.h"

#define D_SERIALIZER_ENTITY_TAG_BASE_TYPE							(0x00000001)
#define D_SERIALIZER_ENTITY_TAG_CONTAINER_OF_MEMBER_VARIABLE		(0x00000002)
#define D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE						(0x00000003)
#define D_SERIALIZER_ENTITY_TAG_PROPERTY							(0x00000004)

#define D_SERIALIZER_ICONTAINER_NAME		"__IContainer__"
#define D_SERIALIZER_ICONTAINER_ELE_NAME	"__Ele_of_IContainer__"

//CSerializer
CSerializer::CSerializer(void)
	:m_pTreeSerial(nullptr)
{
}

CSerializer::~CSerializer(void)
{
}

void CSerializer::SetSerial(ISerial *pSerial)
{
	if (pSerial)
	{
		m_pTreeSerial = pSerial->AsType<ITreeSerial>();
	}
	else
	{
		m_pTreeSerial = nullptr;
	}
}

bool CSerializer::DoSerialize(const CMetaDataType *pType, void *pObj, const char *pName)
{
	if (!pType || !pObj || !m_pTreeSerial || !m_pTreeSerial->Root()) return false;
	CCharArray TypeName(256);
	if (!pType->GetFullName(TypeName.char_array(), 256)) return false;

	ISerialEntity *pEnt;
	pEnt = m_pTreeSerial->Root()->NewChild();
	pEnt->SetName(pName);
	pEnt->SetEntTypeName(TypeName.char_array());
	pEnt->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
	switch(pType->GetTypeID())
	{
	case D_META_DATA_TYPE_ID_CLASS_TYPE:
		return SerializeCustomTypeWrapper(reinterpret_cast<const CMetaDataClassType*>(pType), pObj, pEnt);
	case D_META_DATA_TYPE_ID_INNER_TYPE:
		return SerializeInnerType(reinterpret_cast<const CMetaDataInnerType*>(pType), pObj, pEnt);
	default:
		break;
	}
	return false;
}

bool CSerializer::DoUnserialize(const CMetaDataType *pType, void *pObj, const char *pName)
{
	if (!pType || !pObj || !m_pTreeSerial || !m_pTreeSerial->Root()) return false;
	CCharArray TypeName(256);
	if (!pType->GetFullName(TypeName.char_array(), 256)) return false;
	ISerialEntity *pEnt(m_pTreeSerial->Root()->FindChild(
		pName, TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE));
	if (!pEnt) return false;

	switch(pType->GetTypeID())
	{
	case D_META_DATA_TYPE_ID_CLASS_TYPE:
		return UnserializeCustomTypeWrapper(pEnt, reinterpret_cast<const CMetaDataClassType*>(pType), pObj);
	case D_META_DATA_TYPE_ID_INNER_TYPE:
		return UnserializeInnerType(pEnt, reinterpret_cast<const CMetaDataInnerType*>(pType), pObj);
	default:
		break;
	}
	return false;
}

bool CSerializer::SerializeCustomTypeWrapper(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity)
{
	if (TypeTraits<SimpleString>::GetMetaDataType() != pType)
	{
		return SerializeCustomType(pType, pObj, pSEntity);
	}
	else
	{
		pSEntity->SetValue(reinterpret_cast<SimpleString*>(pObj)->GetValue());
		return true;
	}
}

bool CSerializer::SerializeCustomType(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity)
{
	size_t i;
	const CMetaDataCustomType *pCustomType;
	const CMetaDataCustomTypeMemberVar *pMemVar;
	const CMetaDataCustomTypeProperty *pProp;
	void *pO;
	ISerialEntity *pChild;
	CCharArray TypeName(256);

	//基类数据序列化
	for (i = 0; i < pType->GetBaseTypeCount(); ++i)
	{
		pCustomType = pType->GetBaseType(i);
		if (!pCustomType->GetFullName(TypeName.char_array(), 256)) return false;
		pO = reinterpret_cast<void*>((reinterpret_cast<TDUIntPtr>(pObj) + pType->GetBaseTypeOffset(i)));
		pChild = pSEntity->NewChild();
		pChild->SetName(pCustomType->GetName());
		pChild->SetEntTypeName(TypeName.char_array());
		pChild->SetTag(D_SERIALIZER_ENTITY_TAG_BASE_TYPE);
		if (!SerializeCustomTypeWrapper(pCustomType, pO, pChild))
		{
			pSEntity->DelChild(pChild);
			return false;
		}
	}

	//成员变量序列化
	for (i = 0; i < pType->GetMemberVarCount(); ++i)
	{
		pMemVar = pType->GetMemberVar(i);
		if (!pMemVar->GetMDType()->GetFullName(TypeName.char_array(), 256)) return false;
		if (pMemVar->GetPtrLevel() == 0)
		{
			pO = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
		}
		else if (pMemVar->GetPtrLevel() == 1)
		{
			pO = *reinterpret_cast<void**>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
		}
		else continue;
		pChild = pSEntity->NewChild();
		pChild->SetName(pMemVar->GetName());
		pChild->SetEntTypeName(TypeName.char_array());
		pChild->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
		switch(pMemVar->GetMDType()->GetTypeID())
		{
		case D_META_DATA_TYPE_ID_CLASS_TYPE:
			if (!SerializeCustomTypeWrapper(reinterpret_cast<const CMetaDataClassType*>(pMemVar->GetMDType()),
				pO, pChild))
			{
				pSEntity->DelChild(pChild);
				return false;
			}
			break;
		case D_META_DATA_TYPE_ID_INNER_TYPE:
			if (!SerializeInnerType(reinterpret_cast<const CMetaDataInnerType*>(pMemVar->GetMDType()),
				pO, pChild))
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

	//属性序列化
	CPropertyBase *pProperty;
	for (i = 0; i < pType->GetPropertyCount(); ++i)
	{
		pProp = pType->GetProperty(i);
		if (!pProp->GetMDType()->GetFullName(TypeName.char_array(), 265)) return false;
		if (pProp->IsOffset())
			pProperty = reinterpret_cast<CPropertyBase*>(reinterpret_cast<TDUIntPtr>(pObj) + pProp->GetPropertyLocation().Offset);
		else pProperty = pProp->GetPropertyLocation().pProperty;
		if (pProp->GetPtrLevel() == 0)
		{
		}
		else if (pProp->GetPtrLevel() == 1)
		{
		}
		else continue;
		pChild = pSEntity->NewChild();
		pChild->SetName(pProp->GetName());
		pChild->SetEntTypeName(TypeName.char_array());
		pChild->SetTag(D_SERIALIZER_ENTITY_TAG_PROPERTY);
	}

	//IContainer元素序列化
	IContainer *pContainter(
		reinterpret_cast<IContainer*>(
			pType->AsType(pObj, TypeTraits<IContainer>::GetMetaDataType())
			)
	);
	if (pContainter)
	{
		ISerialEntity *pContainterEntity;
		for (size_t type_index = 0; type_index < pContainter->GetItemTypeCount(); ++type_index)
		{
			if (!pContainter->GetItemType(type_index)
				|| !pContainter->GetItemType(type_index)->GetFullName(TypeName.char_array(), 256))
				return false;

			pContainterEntity = pSEntity->NewChild();
			pContainterEntity->SetName(D_SERIALIZER_ICONTAINER_NAME);
			pContainterEntity->SetEntTypeName(TypeName.char_array());
			pContainterEntity->SetTag(D_SERIALIZER_ENTITY_TAG_CONTAINER_OF_MEMBER_VARIABLE);
			for (i = 0; i < pContainter->Count(type_index); ++i)
			{
				pO = pContainter->GetItem(type_index, i);
				if (!pO) continue;
				pChild = pContainterEntity->NewChild();
				pChild->SetName(D_SERIALIZER_ICONTAINER_ELE_NAME);
				pChild->SetEntTypeName(TypeName.char_array());
				pChild->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
				switch (pContainter->GetItemType(type_index)->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
					if (!SerializeCustomTypeWrapper(
						reinterpret_cast<const CMetaDataClassType*>(pContainter->GetItemType(type_index)),
						pO, pChild))
					{
						pContainterEntity->DelChild(pChild);
						return false;
					}
					break;
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					if (!SerializeInnerType(reinterpret_cast<const CMetaDataInnerType*>(pContainter->GetItemType(type_index)),
						pO, pChild))
					{
						pContainterEntity->DelChild(pChild);
						return false;
					}
					break;
				default:
					pContainterEntity->DelChild(pChild);
					return false;
				}
			}
		}
	}

	return true;
}

bool CSerializer::SerializeInnerType(const CMetaDataInnerType *pType, void *pObj, ISerialEntity *pSEntity)
{
	bool ret(true);
	
	if (pType == TypeTraits<char>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<char*>(pObj));
	}
	else if (pType == TypeTraits<wchar_t>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<wchar_t*>(pObj));
	}
	else if (pType == TypeTraits<short>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<short*>(pObj));
	}
	else if (pType == TypeTraits<int>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<int*>(pObj));
	}
	else if (pType == TypeTraits<long>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<long*>(pObj));
	}
	else if (pType == TypeTraits<long long>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<long long*>(pObj));
	}
	else if (pType == TypeTraits<unsigned char>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<unsigned char*>(pObj));
	}
	else if (pType == TypeTraits<unsigned short>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<unsigned short*>(pObj));
	}
	else if (pType == TypeTraits<unsigned int>::GetMetaDataType())
	{
		pSEntity->SetValue((int)*reinterpret_cast<unsigned int*>(pObj));
	}
	else if (pType == TypeTraits<unsigned long>::GetMetaDataType())
	{
		pSEntity->SetValue((long)*reinterpret_cast<unsigned long*>(pObj));
	}
	else if (pType == TypeTraits<unsigned long long>::GetMetaDataType())
	{
		pSEntity->SetValue((long long)*reinterpret_cast<unsigned long long*>(pObj));
	}
	else if (pType == TypeTraits<float>::GetMetaDataType())
	{
		pSEntity->SetValue((double)*reinterpret_cast<float*>(pObj));
	}
	else if (pType == TypeTraits<double>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<double*>(pObj));
	}
	else if (pType == TypeTraits<bool>::GetMetaDataType())
	{
		pSEntity->SetValue(*reinterpret_cast<bool*>(pObj));
	}
	else ret = false;

	return ret;
}

bool CSerializer::UnserializeCustomTypeWrapper(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj)
{
	if (TypeTraits<SimpleString>::GetMetaDataType() != pType)
	{
		return UnserializeCustomType(pSEntity, pType, pObj);
	}
	else
	{
		if (pSEntity->GetValue().type == vtSTR_PTR)
		{
			reinterpret_cast<SimpleString*>(pObj)->SetValue(pSEntity->GetValue().value._pstr);
			return true;
		}
		else return false;
	}
}

bool CSerializer::UnserializeCustomType(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj)
{
	size_t i;
	const CMetaDataCustomType *pCustomType;
	const CMetaDataCustomTypeMemberVar *pMemVar;
	ISerialEntity *pChild;
	void *pO;
	CCharArray TypeName(256);

	//基类数据反序列化
	for (i = 0; i < pType->GetBaseTypeCount(); ++i)
	{
		pCustomType = pType->GetBaseType(i);
		if (!pCustomType->GetFullName(TypeName.char_array(), 256)) return false;
		pChild = pSEntity->FindChild(pCustomType->GetName(), TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_BASE_TYPE);
		if (pChild)
		{
			pO = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + pType->GetBaseTypeOffset(i));
			if (!UnserializeCustomTypeWrapper(pChild, pCustomType, pO))
			{
				return false;
			}
		}
	}

	//IContainer元素反序列化
	IContainer *pContainter(
		reinterpret_cast<IContainer*>(
			pType->AsType(pObj, TypeTraits<IContainer>::GetMetaDataType())
		)
	);
	if (pContainter)
	{
		ISerialEntity *pContainterEntity;
		for (size_t type_index = 0; type_index < pContainter->GetItemTypeCount(); ++type_index)
		{
			if (!pContainter->GetItemType(type_index)
				|| !pContainter->GetItemType(type_index)->GetFullName(TypeName.char_array(), 256))
				return false;
			pContainterEntity = pSEntity->FindChild(D_SERIALIZER_ICONTAINER_NAME,
				TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_CONTAINER_OF_MEMBER_VARIABLE);
			if (!pContainterEntity) continue;
			for (i = 0; i < pContainterEntity->GetChildrenCount(); ++i)
			{
				pChild = pContainterEntity->GetChildren(i);
				if (strcmp(D_SERIALIZER_ICONTAINER_ELE_NAME, pChild->GetName()) != 0
					|| strcmp(TypeName.char_array(), pChild->GetEntTypeName()) != 0
					|| pChild->GetTag() != D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE)
					continue;

				pO = pContainter->NewItem(type_index);
				if (!pO)
				{
					pO = NewObject(pContainter->GetItemType(type_index));
					if (!pO) return false;
					pContainter->AddItem(type_index, pO);
				}
				
				switch (pContainter->GetItemType(type_index)->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
					if (!UnserializeCustomTypeWrapper(pChild,
						reinterpret_cast<const CMetaDataClassType*>(pContainter->GetItemType(type_index)),
						pO))
					{
						return false;
					}
					break;
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					if (!UnserializeInnerType(pChild,
						reinterpret_cast<const CMetaDataInnerType*>(pContainter->GetItemType(type_index)),
						pO))
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
		if (!pMemVar->GetMDType()
			|| !(pMemVar->GetMDType()->GetFullName(TypeName.char_array(), 256)))
			return false;
		pChild = pSEntity->FindChild(pMemVar->GetName(), TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
		if (pChild)
		{
			if (pMemVar->GetPtrLevel() == 0)
			{
				pO = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
			}
			else if (pMemVar->GetPtrLevel() == 1)
			{
				pO = NewObject(pMemVar->GetMDType());
				if (pO)
				{
					*reinterpret_cast<void**>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset()) = pO;
				}
				else return false;
			}
			else continue;
		}
		else continue;

		switch(pMemVar->GetMDType()->GetTypeID())
		{
		case D_META_DATA_TYPE_ID_CLASS_TYPE:
			if (!UnserializeCustomTypeWrapper(pChild,
				reinterpret_cast<const CMetaDataClassType*>(pMemVar->GetMDType()),
				pO))
			{
				return false;
			}
			break;
		case D_META_DATA_TYPE_ID_INNER_TYPE:
			if (!UnserializeInnerType(pChild,
				reinterpret_cast<const CMetaDataInnerType*>(pMemVar->GetMDType()),
				pO))
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

bool CSerializer::UnserializeInnerType(ISerialEntity *pSEntity, const CMetaDataInnerType *pType, void *pObj)
{
	bool ret(true);
	SVariant var;

	var = pSEntity->GetValue();
	if (pType == TypeTraits<char>::GetMetaDataType())
	{
		*reinterpret_cast<char*>(pObj) = (char)var.value._i;
	}
	else if (pType == TypeTraits<wchar_t>::GetMetaDataType())
	{
		*reinterpret_cast<wchar_t*>(pObj) = (wchar_t)var.value._i;
	}
	else if (pType == TypeTraits<short>::GetMetaDataType())
	{
		*reinterpret_cast<short*>(pObj) = (short)var.value._i;
	}
	else if (pType == TypeTraits<int>::GetMetaDataType())
	{
		*reinterpret_cast<int*>(pObj) = var.value._i;
	}
	else if (pType == TypeTraits<long>::GetMetaDataType())
	{
		*reinterpret_cast<long*>(pObj) = (long)var.value._i;
	}
	else if (pType == TypeTraits<long long>::GetMetaDataType())
	{
		*reinterpret_cast<long long*>(pObj) = var.value._ll;
	}
	else if (pType == TypeTraits<unsigned char>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned char*>(pObj) = (unsigned char)var.value._i;
	}
	else if (pType == TypeTraits<unsigned short>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned short*>(pObj) = (unsigned short)var.value._i;
	}
	else if (pType == TypeTraits<unsigned int>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned int*>(pObj) = (unsigned int)var.value._i;
	}
	else if (pType == TypeTraits<unsigned long>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned long*>(pObj) = (unsigned long)var.value._i;
	}
	else if (pType == TypeTraits<unsigned long long>::GetMetaDataType())
	{
		*reinterpret_cast<unsigned long long*>(pObj) = var.value._ll;
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

void *CSerializer::NewObject(const CMetaDataType *pType)
{
	if (!pType) return nullptr;

	void *pO(pType->NewObject());
	if (pO) return pO;

	if (pType == TypeTraits<char>::GetMetaDataType())
	{
		pO = new char;
	}
	if (pType == TypeTraits<wchar_t>::GetMetaDataType())
	{
		pO = new wchar_t;
	}
	else if (pType == TypeTraits<short>::GetMetaDataType())
	{
		pO = new short;
	}
	else if (pType == TypeTraits<int>::GetMetaDataType())
	{
		pO = new int;
	}
	else if (pType == TypeTraits<long>::GetMetaDataType())
	{
		pO = new long;
	}
	else if (pType == TypeTraits<long long>::GetMetaDataType())
	{
		pO = new long long;
	}
	else if (pType == TypeTraits<unsigned char>::GetMetaDataType())
	{
		pO = new unsigned char;
	}
	else if (pType == TypeTraits<unsigned short>::GetMetaDataType())
	{
		pO = new unsigned short;
	}
	else if (pType == TypeTraits<unsigned int>::GetMetaDataType())
	{
		pO = new unsigned int;
	}
	else if (pType == TypeTraits<unsigned long>::GetMetaDataType())
	{
		pO = new unsigned long;
	}
	else if (pType == TypeTraits<unsigned long long>::GetMetaDataType())
	{
		pO = new unsigned long long;
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

	return pO;
}
