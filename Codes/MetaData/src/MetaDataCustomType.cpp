#include "stdafx.h"
#include "..\include\MetaDataCustomType.h"
#include "..\include\MetaDataInterface.h"
#include "..\include\ExceptionIDMetaData.h"

//Template Member Function of CMetaDataCustomType
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

template<typename _CompareType>
bool CMetaDataCustomType::FindUnknownInterface(_CompareType ct_var, std::vector<SMDCustomTypeOffsetDescriptInCustomType*> &IntfList) const
{
	if (m_pUnknownInterfaceList)
	{
		std::vector<SMDInterfaceOfCustomType>::iterator intf_itr;
		for (intf_itr = m_pUnknownInterfaceList->begin(); intf_itr != m_pUnknownInterfaceList->end(); ++intf_itr)
		{
			IntfList.push_back(&(*intf_itr));
			if (intf_itr->Intf()->Compare(ct_var))
			{
				return true;
			}
			else
			{
				if (intf_itr->Intf()->FindUnknownInterface<_CompareType>(ct_var, IntfList))
				{
					return true;
				}
			}
			IntfList.pop_back();
		}
	}
	//查找基类支持的未知接口
	if (m_pBaseTypeList)
	{
		std::vector<SMDBaseTypeOfCustomType>::iterator base_type_itr;
		for (base_type_itr = m_pBaseTypeList->begin(); base_type_itr != m_pBaseTypeList->end(); ++base_type_itr)
		{
			IntfList.push_back(&(*base_type_itr));
			if (base_type_itr->CustomType->FindUnknownInterface<_CompareType>(ct_var, IntfList))
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

	if (this->Compare(pBaseTypeName))
	{
		*outObj = pObj;
		return true;
	}

	TDUIntPtr total_offset(0);

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindBaseType<const char*>(pBaseTypeName, CTODescriptList))
	{
		for (size_t i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		*outObj = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
		return true;
	}

	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr;
		AsTypeExTypeParam.Param.pTypeFullName = pBaseTypeName;
		*outObj = m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
		return true;
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

	if (FindUnknownInterface<const CMetaDataType*>(pType, CTODescriptList))
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

	if (FindUnknownInterface<const TDGUID&>(type_guid, CTODescriptList))
	{
		return true;
	}

	return false;
}

bool CMetaDataCustomType::IsTypeOf(const char * pTypeFullName) const
{
	if (this->Compare(pTypeFullName)) return true;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;

	if (FindBaseType<const char*>(pTypeFullName, CTODescriptList))
	{
		return true;
	}

	if (FindInterface<const char*>(pTypeFullName, CTODescriptList))
	{
		return true;
	}

	if (FindUnknownInterface<const char*>(pTypeFullName, CTODescriptList))
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

	if (FindUnknownInterface<const CMetaDataType*>(pType, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkMDType;
		AsTypeExTypeParam.Param.pType = pType;
		return m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
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

	if (FindUnknownInterface<const TDGUID&>(type_guid, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkTypeGUID;
		AsTypeExTypeParam.Param.ptype_guid = &type_guid;
		return m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
	}

	return nullptr;
}

void * CMetaDataCustomType::AsType(void * pObj, const char * pTypeFullName) const
{
	if (this->Compare(pTypeFullName)) return pObj;

	TDUIntPtr total_offset(0);
	size_t i;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindBaseType<const char*>(pTypeFullName, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (FindInterface<const char*>(pTypeFullName, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (FindUnknownInterface<const char*>(pTypeFullName, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr;
		AsTypeExTypeParam.Param.pTypeFullName = pTypeFullName;
		return m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
	}

	return nullptr;
}

bool CMetaDataCustomType::QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf) const
{
	if (!pObj || !pIntfName || !outIntf) return false;

	if (this->Compare(pIntfName))
	{
		*outIntf = reinterpret_cast<IInterface*>(pObj);
		return true;
	}

	TDUIntPtr total_offset(0);

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindInterface<const char*>(pIntfName, CTODescriptList))
	{
		for (size_t i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		*outIntf = reinterpret_cast<IInterface*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
		return true;
	}

	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr;
		AsTypeExTypeParam.Param.pTypeFullName = pIntfName;
		*outIntf = reinterpret_cast<IInterface*>(m_AsTypeExFunPtr(pObj, AsTypeExTypeParam));
		return true;
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
