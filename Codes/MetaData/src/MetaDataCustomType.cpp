#include "stdafx.h"
#include "..\include\MetaDataCustomType.h"
#include "..\include\MetaDataInterface.h"
#include "..\include\ExceptionIDMetaData.h"

template<typename _CompareType>
bool CMetaDataCustomType::FindBaseType(_CompareType ct_var, std::vector<SMDCustomTypeOffsetDescriptInCustomType*> &BaseList) const
{
	if (m_pBaseTypeList)
	{
		std::vector<SMDBaseTypeOfCustomType>::iterator base_type_itr;
		for (base_type_itr = m_pBaseTypeList->begin(); base_type_itr != m_pBaseTypeList->end(); ++base_type_itr)
		{
			BaseList.push_back(&(*base_type_itr));
			if (base_type_itr->CustomType->Compare(ct_var))
			{
				return true;
			}
			else
			{
				if (base_type_itr->CustomType->FindBaseType<_CompareType>(ct_var, BaseList))
				{
					return true;
				}
			}
			BaseList.pop_back();
		}
	}

	return false;
}

template<typename _CompareType>
bool CMetaDataCustomType::FindInterface(_CompareType ct_var, std::vector<SMDCustomTypeOffsetDescriptInCustomType*> &IntfList) const
{
	if (m_pInterfaceList)
	{
		std::vector<SMDInterfaceOfCustomType>::iterator intf_itr;
		for (intf_itr = m_pInterfaceList->begin(); intf_itr != m_pInterfaceList->end(); ++intf_itr)
		{
			IntfList.push_back(&(*intf_itr));
			if (intf_itr->Intf()->Compare(ct_var))
			{
				return true;
			}
			else
			{
				if (intf_itr->Intf()->FindInterface<_CompareType>(ct_var, IntfList))
				{
					return true;
				}
			}
			IntfList.pop_back();
		}
	}
	//查找基类支持的接口
	if (m_pBaseTypeList)
	{
		std::vector<SMDBaseTypeOfCustomType>::iterator base_type_itr;
		for (base_type_itr = m_pBaseTypeList->begin(); base_type_itr != m_pBaseTypeList->end(); ++base_type_itr)
		{
			IntfList.push_back(&(*base_type_itr));
			if (base_type_itr->CustomType->FindInterface<_CompareType>(ct_var, IntfList))
			{
				return true;
			}
			IntfList.pop_back();
		}
	}

	return false;
}

//CMetaDataCustomType
CMetaDataCustomType::CMetaDataCustomType(const char *pName, const CMetaData *pParent, size_t size,
										 bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar)
	:CMetaDataType(pName, pParent, true, size),
	m_EnableBaseType(EnableBaseType), m_Sealed(bSealed), m_EnableStaticMemberFunc(EnableStaticMemberFunc), m_EnableStaticMemberVar(EnableStaticMemberVar),
	m_pBaseTypeList(nullptr), m_pInterfaceList(nullptr), m_pUnknownInterfaceList(nullptr),
	m_pConstructorList(nullptr), m_pDestructor(nullptr),
	m_pMemberFuncList(nullptr), m_pMemberVarList(nullptr), m_pPropertyList(nullptr),
	m_pStaticMemberFuncList(nullptr), m_pStaticMemberVarList(nullptr),
	m_AsTypeExFunPtr(nullptr)
{
}


CMetaDataCustomType::~CMetaDataCustomType(void)
{
	if (m_pBaseTypeList)
	{
		delete m_pBaseTypeList;
		m_pBaseTypeList = nullptr;
	}
	if (m_pInterfaceList)
	{
		delete m_pInterfaceList;
		m_pInterfaceList = nullptr;
	}
	if (m_pUnknownInterfaceList)
	{
		delete m_pUnknownInterfaceList;
		m_pUnknownInterfaceList = nullptr;
	}
	if (m_pConstructorList)
	{
		delete m_pConstructorList;
		m_pConstructorList = nullptr;
	}
	if (m_pMemberFuncList)
	{
		delete m_pMemberFuncList;
		m_pMemberFuncList = nullptr;
	}
	if (m_pMemberVarList)
	{
		delete m_pMemberVarList;
		m_pMemberVarList = nullptr;
	}
	if (m_pPropertyList)
	{
		delete m_pPropertyList;
		m_pPropertyList = nullptr;
	}
	if (m_pStaticMemberFuncList)
	{
		delete m_pStaticMemberFuncList;
		m_pStaticMemberFuncList = nullptr;
	}
	if (m_pStaticMemberVarList)
	{
		delete m_pStaticMemberVarList;
		m_pStaticMemberVarList = nullptr;
	}
}

void CMetaDataCustomType::AddInterface(const CMetaDataInterface *pIntf, TDUIntPtr Offset)
{
	SMDInterfaceOfCustomType intf;
	intf.CustomType = pIntf;
	intf.Offset = Offset;
	GetInterfaceList()->push_back(intf);
}

void CMetaDataCustomType::AddUnknownInterface(const CMetaDataInterface *pIntf, TDUIntPtr Offset)
{
	SMDInterfaceOfCustomType intf;
	intf.CustomType = pIntf;
	intf.Offset = Offset;
	GetUnknownInterfaceList()->push_back(intf);
}

bool CMetaDataCustomType::QueryBaseType(void *pObj, char *pBaseTypeName, void **outObj) const
{
	if (!pObj || !pBaseTypeName || !outObj) return false;

	std::vector<SMDBaseTypeOfCustomType> *pBaseTypeList(m_pBaseTypeList);
	std::vector<SMDBaseTypeOfCustomType>::iterator itr;
	char FullNameBuffer[256];
	
	if (!pBaseTypeList) return false;

	for (itr = pBaseTypeList->begin(); itr != pBaseTypeList->end(); ++itr)
	{
		if (itr->CustomType->GetFullName(FullNameBuffer, 256) && (strcmp(FullNameBuffer, pBaseTypeName) == 0
			|| strcmp(FullNameBuffer + 2, pBaseTypeName) == 0)) //+2是为了跳过"::"两个字符
		{
			*outObj = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + itr->Offset);
			return true;
		}
	}
	return false;
}

bool CMetaDataCustomType::CallMemberFuction(char * pFunName, CParamVector *pParamTypes, ...) const
{
	if (!m_pMemberFuncList) return false;

	bool ret;
	const CMetaDataFunction *pFunc(nullptr);
	va_list pList;
	
	for (size_t i = 0; i < m_pMemberFuncList->size(); ++i)
	{
		if (strcmp(m_pMemberFuncList->at(i)->GetName(), pFunName) == 0
			&& m_pMemberFuncList->at(i)->FuncParamsCheck(pParamTypes))
		{
			pFunc = m_pMemberFuncList->at(i);
			break;
		}
	}
	if (!pFunc) return false;

	va_start(pList, pParamTypes);
	try
	{
		ret = pFunc->CallFunction(pParamTypes, pList, nullptr);
	}
	catch (...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
	return ret;
}

bool CMetaDataCustomType::CallStaticMemberFuction(char * pFunName, CParamVector *pParamTypes, ...) const
{
	if (!m_pStaticMemberFuncList) return false;

	bool ret;
	const CMetaDataFunction *pFunc(nullptr);
	va_list pList;

	for (size_t i = 0; i < m_pStaticMemberFuncList->size(); ++i)
	{
		if (strcmp(m_pStaticMemberFuncList->at(i)->GetName(), pFunName) == 0
			&& m_pStaticMemberFuncList->at(i)->FuncParamsCheck(pParamTypes))
		{
			pFunc = m_pStaticMemberFuncList->at(i);
			break;
		}
	}
	if (!pFunc) return false;

	va_start(pList, pParamTypes);
	try
	{
		ret = pFunc->CallFunction(pParamTypes, pList, nullptr);
	}
	catch (...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
	return ret;
}

bool CMetaDataCustomType::IsTypeOf(const CMetaDataType *pType) const
{
	if (this->Compare(pType)) return true;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;

	if (FindBaseType<const CMetaDataType*>(pType, CTODescriptList))
	{
		return true;
	}

	if (FindInterface<const CMetaDataType*>(pType, CTODescriptList))
	{
		return true;
	}

	return false;
}

bool CMetaDataCustomType::IsTypeOf(const TDGUID &type_guid) const
{
	if (this->Compare(type_guid)) return true;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;

	if (FindBaseType<const TDGUID&>(type_guid, CTODescriptList))
	{
		return true;
	}

	if (FindInterface<const TDGUID&>(type_guid, CTODescriptList))
	{
		return true;
	}

	return false;
}

void *CMetaDataCustomType::AsType(void *pObj, const CMetaDataType *pType) const
{
	if (this->Compare(pType)) return pObj;

	TDUIntPtr total_offset(0);
	size_t i;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindBaseType<const CMetaDataType*>(pType, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (FindInterface<const CMetaDataType*>(pType, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (m_AsTypeExFunPtr)
	{
		return m_AsTypeExFunPtr(pObj, pType, pType->GetGUID());
	}

	return nullptr;
}

void *CMetaDataCustomType::AsType(void *pObj, const TDGUID &type_guid) const
{
	if (this->Compare(type_guid)) return pObj;

	TDUIntPtr total_offset(0);
	size_t i;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindBaseType<const TDGUID&>(type_guid, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (FindInterface<const TDGUID&>(type_guid, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (m_AsTypeExFunPtr)
	{
		return m_AsTypeExFunPtr(pObj, nullptr, type_guid);
	}

	return nullptr;
}

bool CMetaDataCustomType::QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf) const
{
	if (!pObj || !pIntfName || !outIntf) return false;

	std::vector<SMDInterfaceOfCustomType> *pIntfList(m_pInterfaceList);
	std::vector<SMDInterfaceOfCustomType>::iterator itr;
	char FullNameBuffer[256];
	
	if (!pIntfList) return false;

	for (itr = pIntfList->begin(); itr != pIntfList->end(); ++itr)
	{
		if (itr->Intf()->GetFullName(FullNameBuffer, 256) && (strcmp(FullNameBuffer, pIntfName) == 0
			|| strcmp(FullNameBuffer + 2, pIntfName) == 0)) //+2是为了跳过"::"两个字符
		{
			*outIntf = reinterpret_cast<IInterface*>(reinterpret_cast<TDUIntPtr>(pObj) + itr->Offset);
			return true;
		}
	}
	return false;
}

void *CMetaDataCustomType::NewObject(void) const
{
	return DoCreateObject(nullptr, nullptr);
}

void CMetaDataCustomType::DeleteObject(void *pObj) const
{
	if (pObj)
	{
		if (m_pDestructor)
			m_pDestructor->CallFunction(1, pObj);
		else throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "析构函数元数据不存在！");
	}
}

void *CMetaDataCustomType::DoCreateObject(CParamVector *pParamTypes, va_list pParamList) const
{
	void *pReturn(nullptr);

	if (!m_pConstructorList || m_pConstructorList->size() == 0)
		throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：未定义构造函数元数据！");
	
	std::vector<const CMetaDataFunction*>::iterator itr;
	
	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(pParamTypes))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFunction(pParamTypes, pParamList, &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：构造函数调用失败！");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：构造函数无返回值！");
			}
			break;
		}
	}
	if (!pReturn) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：无匹配的构造函数！");
	return pReturn;
}
