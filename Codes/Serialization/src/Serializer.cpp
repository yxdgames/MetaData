#include "stdafx.h"
#include "..\include\Serializer.h"
#include "..\..\MetaData\include\IObjectTraits.h"
#include "..\..\MetaData\include\IContainer.h"
#include "..\..\MetaData\include\SimpleString.h"
#include "..\..\include\CharArray.h"
#include "..\include\ExceptionSerialization.h"
#include "..\include\ExceptionIDSerialization.h"

#define D_SERIALIZER_ENTITY_TAG_BASE_TYPE							(0x00000001)
#define D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE						(0x00000002)
#define D_SERIALIZER_ENTITY_TAG_PROPERTY							(0x00000003)
#define D_SERIALIZER_ENTITY_TAG_CONTAINER_OF_MEMBER_VARIABLE		(0x00000004)

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
	CCharArray TypeName(D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX);
	if (!pType->GetFullName(TypeName.char_array(), D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;

	ISerialEntity *pEnt;
	pEnt = m_pTreeSerial->Root()->NewChild();
	pEnt->SetName(pName);
	pEnt->SetEntTypeName(TypeName.char_array());
	pEnt->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
	switch(pType->GetTypeID())
	{
	case D_META_DATA_TYPE_ID_CLASS_TYPE:
	case D_META_DATA_TYPE_ID_INTERFACE:
		return SerializeCustomTypeWrapper(reinterpret_cast<const CMetaDataCustomType*>(pType), pObj, pEnt, TypeName.char_array());
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
	CCharArray TypeName(D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX);
	if (!pType->GetFullName(TypeName.char_array(), D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
	ISerialEntity *pEnt(m_pTreeSerial->Root()->FindChild(
		pName, TypeName.char_array(), D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE));
	if (!pEnt) return false;

	switch(pType->GetTypeID())
	{
	case D_META_DATA_TYPE_ID_CLASS_TYPE:
	case D_META_DATA_TYPE_ID_INTERFACE:
		return UnserializeCustomTypeWrapper(pEnt, reinterpret_cast<const CMetaDataCustomType*>(pType), pObj, TypeName.char_array());
	case D_META_DATA_TYPE_ID_INNER_TYPE:
		return UnserializeInnerType(pEnt, reinterpret_cast<const CMetaDataInnerType*>(pType), pObj);
	default:
		break;
	}
	return false;
}

bool CSerializer::SerializeCustomTypeWrapper(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	if (TypeTraits<SimpleString>::GetMetaDataType() != pType)
	{
		return SerializeCustomType(pType, pObj, pSEntity, strBuffer);
	}
	else
	{
		pSEntity->SetValue(reinterpret_cast<SimpleString*>(pObj)->GetValue());
		return true;
	}
}

bool CSerializer::SerializeCustomType(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	//基类数据序列化
	if (!SerializeCustomTypeBaseType(pType, pObj, pSEntity, strBuffer)) return false;

	//成员变量序列化
	if (!SerializeCustomTypeMemVar(pType, pObj, pSEntity, strBuffer)) return false;

	//属性序列化
	if (!SerializeCustomTypeProperty(pType, pObj, pSEntity, strBuffer)) return false;

	//IContainer元素序列化
	if (!SerializeCustomTypeContainer(reinterpret_cast<IContainer*>(
		pType->AsType(pObj, TypeTraits<IContainer>::GetMetaDataType())),
		pSEntity, strBuffer)) return false;

	return true;
}

bool CSerializer::SerializeCustomTypeBaseType(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity,
								 char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	const CMetaDataCustomType *pCustomType;
	void *pO;
	ISerialEntity *pChild;
	for (size_t i = 0; i < pType->GetBaseTypeCount(); ++i)
	{
		pCustomType = pType->GetBaseType(i);
		if (!pCustomType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
		pO = reinterpret_cast<void*>((reinterpret_cast<TDUIntPtr>(pObj) + pType->GetBaseTypeOffset(i)));
		pChild = pSEntity->NewChild();
		pChild->SetName(pCustomType->GetName());
		pChild->SetEntTypeName(strBuffer);
		pChild->SetTag(D_SERIALIZER_ENTITY_TAG_BASE_TYPE);
		if (!SerializeCustomTypeWrapper(pCustomType, pO, pChild, strBuffer))
		{
			pSEntity->DelChild(pChild);
			return false;
		}
	}
	return true;
}

bool CSerializer::SerializeCustomTypeMemVar(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity,
											char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	const CMetaDataCustomTypeMemberVar *pMemVar;
	const CMetaDataType *tmpType;
	void *pO;
	IObjectTraits *pObjectTraits;
	ISerialEntity *pParent;
	ISerialEntity *pChild;
	for (size_t i = 0; i < pType->GetMemberVarCount(); ++i)
	{
		pMemVar = pType->GetMemberVar(i);
		tmpType = pMemVar->GetMDType();
		if (pMemVar->GetPtrLevel() == 0)
		{
			pO = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
			pParent = pSEntity;
		}
		else if (pMemVar->GetPtrLevel() == 1)
		{
			pO = *reinterpret_cast<void**>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
			if (!pO) continue;
			pObjectTraits = reinterpret_cast<IObjectTraits*>(tmpType->AsType(pO, TypeTraits<IObjectTraits>::GetMetaDataType()));
			if (pObjectTraits && tmpType != pObjectTraits->GetActualMetaDataType())
			{
				if (!tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
				pParent = pSEntity->NewChild();
				pParent->SetName(pMemVar->GetName());
				pParent->SetEntTypeName(strBuffer);
				pParent->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
				tmpType = pObjectTraits->GetActualMetaDataType();
				pO = pObjectTraits->GetActualSelf();
			}
			else pParent = pSEntity;
		}
		else continue;
		if (!tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
		pChild = pParent->NewChild();
		pChild->SetName(pMemVar->GetName());
		pChild->SetEntTypeName(strBuffer);
		pChild->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
		switch(tmpType->GetTypeID())
		{
		case D_META_DATA_TYPE_ID_CLASS_TYPE:
		case D_META_DATA_TYPE_ID_INTERFACE:
			if (!SerializeCustomTypeWrapper(reinterpret_cast<const CMetaDataCustomType*>(tmpType),
				pO, pChild, strBuffer))
			{
				pParent->DelChild(pChild);
				return false;
			}
			break;
		case D_META_DATA_TYPE_ID_INNER_TYPE:
			if (!SerializeInnerType(reinterpret_cast<const CMetaDataInnerType*>(tmpType),
				pO, pChild))
			{
				pParent->DelChild(pChild);
				return false;
			}
			break;
		default:
			pParent->DelChild(pChild);
			return false;
		}
	}
	return true;
}

bool CSerializer::SerializeCustomTypeProperty(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity,
											  char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	const CMetaDataCustomTypeProperty *pProp;
	const CMetaDataType *tmpType;
	CPropertyBase *pProperty;
	void *pO;
	IObjectTraits *pObjectTraits;
	ISerialEntity *pParent;
	ISerialEntity *pChild;
	bool error_flag(false);
	for (size_t i = 0; i < pType->GetPropertyCount(); ++i)
	{
		pProp = pType->GetProperty(i);
		tmpType = pProp->GetMDType();
		if (pProp->PropertyLocationIsOffset())
			pProperty = reinterpret_cast<CPropertyBase*>(reinterpret_cast<TDUIntPtr>(pObj) + pProp->GetPropertyLocation().Offset);
		else pProperty = pProp->GetPropertyLocation().pProperty;
		if (pProp->GetPtrLevel() == 0)
		{
			pO = tmpType->NewObject();
			if (!pO) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：创建对象失败（串化过程）！");
			pProperty->CallGet(pObj, pO);
			pParent = pSEntity;
		}
		else if (pProp->GetPtrLevel() == 1)
		{
			pProperty->CallGet(pObj, &pO);
			if (!pO) continue;
			pObjectTraits = reinterpret_cast<IObjectTraits*>(tmpType->AsType(pO, TypeTraits<IObjectTraits>::GetMetaDataType()));
			if (pObjectTraits && tmpType != pObjectTraits->GetActualMetaDataType())
			{
				if (!tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
				pParent = pSEntity->NewChild();
				pParent->SetName(pProp->GetName());
				pParent->SetEntTypeName(strBuffer);
				pParent->SetTag(D_SERIALIZER_ENTITY_TAG_PROPERTY);
				tmpType = pObjectTraits->GetActualMetaDataType();
				pO = pObjectTraits->GetActualSelf();
			}
			else pParent = pSEntity;
		}
		else continue;
		try
		{
			while (true)
			{
				if (!tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX))
				{
					error_flag = true;
					break;
				}
				pChild = pParent->NewChild();
				pChild->SetName(pProp->GetName());
				pChild->SetEntTypeName(strBuffer);
				pChild->SetTag(D_SERIALIZER_ENTITY_TAG_PROPERTY);
				switch (tmpType->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
				case D_META_DATA_TYPE_ID_INTERFACE:
					if (!SerializeCustomTypeWrapper(reinterpret_cast<const CMetaDataCustomType*>(tmpType),
						pO, pChild, strBuffer))
					{
						pParent->DelChild(pChild);
						error_flag = true;
					}
					break;
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					if (!SerializeInnerType(reinterpret_cast<const CMetaDataInnerType*>(tmpType),
						pO, pChild))
					{
						pParent->DelChild(pChild);
						error_flag = true;
					}
					break;
				default:
					pParent->DelChild(pChild);
					error_flag = true;
					break;
				}
				break;
			}
		}
		catch (...)
		{
			if (pProp->GetPtrLevel() == 0) tmpType->DeleteObject(pO);
			throw;
		}
		if (pProp->GetPtrLevel() == 0) tmpType->DeleteObject(pO);

		if (error_flag) return false;
	}
	return true;
}

bool CSerializer::SerializeCustomTypeContainer(IContainer *pContainter, ISerialEntity *pSEntity,
											   char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	if (!pContainter) return true;

	size_t type_index, index;
	const CMetaDataType *tmpType;
	const CMetaDataType *tmpType2;
	void *pO;
	IObjectTraits *pObjectTraits;
	ISerialEntity *pContainterEntity;
	ISerialEntity *pChild;

	for (type_index = 0; type_index < pContainter->GetItemTypeCount(); ++type_index)
	{
		tmpType = pContainter->GetItemType(type_index);
		if (!tmpType || !tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX))
			return false;

		pContainterEntity = pSEntity->NewChild();
		pContainterEntity->SetName(D_SERIALIZER_ICONTAINER_NAME);
		pContainterEntity->SetEntTypeName(strBuffer);
		pContainterEntity->SetTag(D_SERIALIZER_ENTITY_TAG_CONTAINER_OF_MEMBER_VARIABLE);
		for (index = 0; index < pContainter->Count(type_index); ++index)
		{
			pO = pContainter->GetItem(type_index, index);
			if (!pO) continue;
			pObjectTraits = reinterpret_cast<IObjectTraits*>(tmpType->AsType(pO, TypeTraits<IObjectTraits>::GetMetaDataType()));
			if (pObjectTraits && tmpType != pObjectTraits->GetActualMetaDataType())
			{
				tmpType2 = pObjectTraits->GetActualMetaDataType();
				pO = pObjectTraits->GetActualSelf();
			}
			else tmpType2 = tmpType;
			if (!tmpType2->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX))
				return false;
			pChild = pContainterEntity->NewChild();
			pChild->SetName(D_SERIALIZER_ICONTAINER_ELE_NAME);
			pChild->SetEntTypeName(strBuffer);
			pChild->SetTag(D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
			switch (tmpType2->GetTypeID())
			{
			case D_META_DATA_TYPE_ID_CLASS_TYPE:
			case D_META_DATA_TYPE_ID_INTERFACE:
				if (!SerializeCustomTypeWrapper(
					reinterpret_cast<const CMetaDataCustomType*>(tmpType2),
					pO, pChild, strBuffer))
				{
					pContainterEntity->DelChild(pChild);
					return false;
				}
				break;
			case D_META_DATA_TYPE_ID_INNER_TYPE:
				if (!SerializeInnerType(reinterpret_cast<const CMetaDataInnerType*>(tmpType2),
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

bool CSerializer::UnserializeCustomTypeWrapper(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	if (TypeTraits<SimpleString>::GetMetaDataType() != pType)
	{
		return UnserializeCustomType(pSEntity, pType, pObj, strBuffer);
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

bool CSerializer::UnserializeCustomType(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	//基类数据反序列化
	if (!UnserializeCustomTypeBaseType(pSEntity, pType, pObj, strBuffer)) return false;

	//成员变量反序列化
	if (!UnserializeCustomTypeMemVar(pSEntity, pType, pObj, strBuffer)) return false;

	//属性反序列化
	if (!UnserializeCustomTypeProperty(pSEntity, pType, pObj, strBuffer)) return false;

	//IContainer元素反序列化
	if (!UnserializeCustomTypeContainer(pSEntity,
		reinterpret_cast<IContainer*>(pType->AsType(pObj, TypeTraits<IContainer>::GetMetaDataType())),
		strBuffer)) return false;

	return true;
}

bool CSerializer::UnserializeCustomTypeBaseType(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj,
												char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	const CMetaDataCustomType *pCustomType;
	void *pO;
	ISerialEntity *pChild;
	for (size_t i = 0; i < pType->GetBaseTypeCount(); ++i)
	{
		pCustomType = pType->GetBaseType(i);
		if (!pCustomType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
		pChild = pSEntity->FindChild(pCustomType->GetName(), strBuffer, D_SERIALIZER_ENTITY_TAG_BASE_TYPE);
		if (pChild)
		{
			pO = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + pType->GetBaseTypeOffset(i));
			if (!UnserializeCustomTypeWrapper(pChild, pCustomType, pO, strBuffer))
			{
				return false;
			}
		}
	}
	return true;
}

bool CSerializer::UnserializeCustomTypeMemVar(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj,
											  char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	const CMetaDataCustomTypeMemberVar *pMemVar;
	const CMetaDataType *tmpType;
	const CMetaDataType *tmpType2;
	void *pO;
	void *tmpO;
	IObjectTraits *pObjectTraits;
	ISerialEntity *pChild;
	for (size_t i = 0; i < pType->GetMemberVarCount(); ++i)
	{
		pMemVar = pType->GetMemberVar(i);
		tmpType = pMemVar->GetMDType();
		if (!(tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)))
			return false;
		pChild = pSEntity->FindChild(pMemVar->GetName(), strBuffer, D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE);
		if (!pChild) continue;
		
		if (pMemVar->GetPtrLevel() == 0)
		{
			pO = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
		}
		else if (pMemVar->GetPtrLevel() == 1)
		{
			pO = *reinterpret_cast<void**>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset());
			if (pChild->GetChildrenCount() == 1)
			{
				tmpType2 = FindMetaDataType(pChild->GetChildren(0)->GetEntTypeName(), true);
				pChild = pChild->GetChildren(0);
			}
			else tmpType2 = nullptr;
			if (pO)
			{
				pObjectTraits = reinterpret_cast<IObjectTraits*>(tmpType->AsType(pO, TypeTraits<IObjectTraits>::GetMetaDataType()));
				if (pObjectTraits && tmpType != pObjectTraits->GetActualMetaDataType())
				{
					if (tmpType2 && tmpType2 == pObjectTraits->GetActualMetaDataType())
					{
						tmpType = tmpType2;
						pO = pObjectTraits->GetActualSelf();
					}
					else throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：异常类型（反串化过程）！");
				}
				else if (tmpType2) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：串化数据异常（反串化过程）！");
			}
			else
			{
				if (tmpType2)
				{
					if (tmpType2->IsTypeOf(tmpType))
						pO = tmpType2->NewObject();
					else throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：异常类型（反串化过程）！");
					tmpO = tmpType2->AsType(pO, tmpType);
					tmpType = tmpType2;
				}
				else
				{
					pO = tmpType->NewObject();
					tmpO = pO;
				}
				if (!pO) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：创建对象失败（反串化过程）！");
				*reinterpret_cast<void**>(reinterpret_cast<TDUIntPtr>(pObj) + pMemVar->GetOffset()) = tmpO;
			}
		}
		else continue;

		switch(tmpType->GetTypeID())
		{
		case D_META_DATA_TYPE_ID_CLASS_TYPE:
		case D_META_DATA_TYPE_ID_INTERFACE:
			if (!UnserializeCustomTypeWrapper(pChild,
				reinterpret_cast<const CMetaDataCustomType*>(tmpType),
				pO, strBuffer))
			{
				return false;
			}
			break;
		case D_META_DATA_TYPE_ID_INNER_TYPE:
			if (!UnserializeInnerType(pChild,
				reinterpret_cast<const CMetaDataInnerType*>(tmpType),
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

bool CSerializer::UnserializeCustomTypeProperty(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	const CMetaDataCustomTypeProperty *pProp;
	const CMetaDataType *tmpType;
	const CMetaDataType *tmpType2;
	CPropertyBase *pProperty;
	void *pO;
	void *tmpO;
	IObjectTraits *pObjectTraits;
	ISerialEntity *pChild;
	bool error_flag(false);
	bool set_pO;
	for (size_t i = 0; i < pType->GetPropertyCount(); ++i)
	{
		pProp = pType->GetProperty(i);
		tmpType = pProp->GetMDType();
		if (!tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX)) return false;
		pChild = pSEntity->FindChild(pProp->GetName(), strBuffer, D_SERIALIZER_ENTITY_TAG_PROPERTY);
		if (!pChild) continue;

		if (pProp->PropertyLocationIsOffset())
			pProperty = reinterpret_cast<CPropertyBase*>(reinterpret_cast<TDUIntPtr>(pObj)
				+ pProp->GetPropertyLocation().Offset);
		else pProperty = pProp->GetPropertyLocation().pProperty;
		if (pProp->GetPtrLevel() == 0)
		{
			pO = tmpType->NewObject();
			tmpO = pO;
			set_pO = true;
		}
		else if (pProp->GetPtrLevel() == 1)
		{
			pProperty->CallGet(pObj, &pO);
			if (pChild->GetChildrenCount() == 1)
			{
				tmpType2 = FindMetaDataType(pChild->GetChildren(0)->GetEntTypeName(), true);
				pChild = pChild->GetChildren(0);
			}
			else tmpType2 = nullptr;
			if (pO)
			{
				tmpO = pO;
				pObjectTraits = reinterpret_cast<IObjectTraits*>(tmpType->AsType(pO, TypeTraits<IObjectTraits>::GetMetaDataType()));
				if (pObjectTraits && tmpType != pObjectTraits->GetActualMetaDataType())
				{
					if (tmpType2 && tmpType2 == pObjectTraits->GetActualMetaDataType())
					{
						tmpType = tmpType2;
						pO = pObjectTraits->GetActualSelf();
					}
					else throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：异常类型（反串化过程）！");
				}
				else if (tmpType2) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：串化数据异常（反串化过程）！");
				set_pO = false;
			}
			else
			{
				if (tmpType2)
				{
					if (tmpType2->IsTypeOf(tmpType))
						pO = tmpType2->NewObject();
					else throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：异常类型（反串化过程）！");
					tmpO = tmpType2->AsType(pO, tmpType);
					tmpType = tmpType2;
				}
				else
				{
					pO = tmpType->NewObject();
					tmpO = pO;
				}
				set_pO = true;
			}
		}
		else continue;
		if (!pO) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：创建对象失败（反串化过程）！");
		try
		{
			while (true)
			{
				switch(tmpType->GetTypeID())
				{
				case D_META_DATA_TYPE_ID_CLASS_TYPE:
				case D_META_DATA_TYPE_ID_INTERFACE:
					if (!UnserializeCustomTypeWrapper(pChild,
						reinterpret_cast<const CMetaDataCustomType*>(tmpType),
						pO, strBuffer))
					{
						error_flag = true;
					}
					break;
				case D_META_DATA_TYPE_ID_INNER_TYPE:
					if (!UnserializeInnerType(pChild,
						reinterpret_cast<const CMetaDataInnerType*>(tmpType),
						pO))
					{
						error_flag = true;
					}
					break;
				default:
					error_flag = true;
					break;
				}
				break;
			}
			if (!error_flag && set_pO)
			{
				if (pProp->GetPtrLevel() == 0)
					pProperty->CallSet(pObj, tmpO);
				else pProperty->CallSet(pObj, &tmpO); //pProp->GetPtrLevel() == 1
			}
		}
		catch (...)
		{
			if (pProp->GetPtrLevel() == 0) tmpType->DeleteObject(pO);
			throw;
		}
		if (pProp->GetPtrLevel() == 0) tmpType->DeleteObject(pO);

		if (error_flag) return false;
	}
	return true;
}

bool CSerializer::UnserializeCustomTypeContainer(ISerialEntity *pSEntity, IContainer *pContainter, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX])
{
	if (!pContainter) return true;

	size_t type_index, index;
	const CMetaDataType *tmpType;
	const CMetaDataType *tmpType2;
	void *pO;
	IObjectTraits *pObjectTraits;
	ISerialEntity *pContainterEntity;
	ISerialEntity *pChild;
	for (type_index = 0; type_index < pContainter->GetItemTypeCount(); ++type_index)
	{
		tmpType = pContainter->GetItemType(type_index);
		if (!tmpType || !tmpType->GetFullName(strBuffer, D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX))
			return false;
		pContainterEntity = pSEntity->FindChild(D_SERIALIZER_ICONTAINER_NAME,
			strBuffer, D_SERIALIZER_ENTITY_TAG_CONTAINER_OF_MEMBER_VARIABLE);
		if (!pContainterEntity) continue;
		pContainter->ClearItems(type_index);
		for (index = 0; index < pContainterEntity->GetChildrenCount(); ++index)
		{
			pChild = pContainterEntity->GetChildren(index);
			if (strcmp(D_SERIALIZER_ICONTAINER_ELE_NAME, pChild->GetName()) != 0
				|| pChild->GetTag() != D_SERIALIZER_ENTITY_TAG_MEMBER_VARIABLE)
				continue;
			tmpType2 = FindMetaDataType(pChild->GetEntTypeName(), true);
			pO = pContainter->NewItem(type_index);
			if (!pO)
			{
				if (!tmpType2->IsTypeOf(tmpType))
					throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：异常类型（反串化过程）！");
				pO = tmpType2->NewObject();
				if (!pO) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：创建对象失败（反串化过程）！");
				pContainter->AddItem(type_index, tmpType2->AsType(pO, tmpType));
			}
			else
			{
				pObjectTraits = reinterpret_cast<IObjectTraits*>(tmpType->AsType(pO, TypeTraits<IObjectTraits>::GetMetaDataType()));
				if (pObjectTraits && tmpType2 != pObjectTraits->GetActualMetaDataType())
				{
					throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：异常类型（反串化过程）！");
				}
			}
				
			switch (tmpType2->GetTypeID())
			{
			case D_META_DATA_TYPE_ID_CLASS_TYPE:
			case D_META_DATA_TYPE_ID_INTERFACE:
				if (!UnserializeCustomTypeWrapper(pChild,
					reinterpret_cast<const CMetaDataCustomType*>(tmpType2),
					pO, strBuffer))
				{
					return false;
				}
				break;
			case D_META_DATA_TYPE_ID_INNER_TYPE:
				if (!UnserializeInnerType(pChild,
					reinterpret_cast<const CMetaDataInnerType*>(tmpType2),
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

inline const CMetaDataType *CSerializer::FindMetaDataType(const char *pTypeName, bool throwException)
{
	const CMetaData *pType;
	pType = META_DATA_GLOBALSPACE().FindChildMetaData(D_META_DATA_TYPE_ID_CLASS_TYPE, pTypeName);
	if (pType) return reinterpret_cast<const CMetaDataType*>(pType);
	pType = META_DATA_GLOBALSPACE().FindChildMetaData(D_META_DATA_TYPE_ID_INTERFACE, pTypeName);
	if (pType) return reinterpret_cast<const CMetaDataType*>(pType);
	pType = META_DATA_GLOBALSPACE().FindChildMetaData(D_META_DATA_TYPE_ID_INNER_TYPE, pTypeName);
	if (pType) reinterpret_cast<const CMetaDataType*>(pType);
	if (throwException)
		throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：未找到类型（反串化过程）！");
	else return nullptr;
}