#include "stdafx.h"
#include "..\include\MetaDataCustomType.h"
#include "..\include\MetaDataInterface.h"
#include "..\include\ExceptionIDMetaData.h"

CMetaDataCustomType::CMetaDataCustomType(const char *pName, const CMetaData *pParent, unsigned int size,
										 bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar)
	:CMetaDataType(pName, pParent, true, size),
	m_EnableBaseType(EnableBaseType), m_Sealed(bSealed), m_EnableStaticMemberFunc(EnableStaticMemberFunc), m_EnableStaticMemberVar(EnableStaticMemberVar),
	m_pBaseTypeList(nullptr), m_pInterfaceList(nullptr), m_pConstructorList(nullptr), m_pDestructor(nullptr),
	m_pMemberFuncList(nullptr), m_pMemberVarList(nullptr), m_pStaticMemberFuncList(nullptr), m_pStaticMemberVarList(nullptr),
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

void CMetaDataCustomType::AddBaseType(const CMetaDataCustomType *pBaseType, unsigned int Offset)
{
	std::vector<SMetaDataCustomTypeBaseType> *pBaseTypeList(GetBaseTypeList());
	if (pBaseTypeList)
	{
		SMetaDataCustomTypeBaseType bt;
		bt.CustomType = pBaseType;
		bt.Offset = Offset;
		pBaseTypeList->push_back(bt);
	}
}

void CMetaDataCustomType::AddInterface(const CMetaDataInterface *pIntf, unsigned int Offset)
{
	std::vector<SMetaDataCustomTypeInterface> *pIntfList(GetInterfaceList());
	if (pIntfList)
	{
		SMetaDataCustomTypeInterface intf;
		intf.Intf = pIntf;
		intf.Offset = Offset;
		pIntfList->push_back(intf);
	}
}

void CMetaDataCustomType::AddConstructor(const CMetaDataFunction *pConstructorFunc)
{
	std::vector<const CMetaDataFunction*> *pConsList(GetConstructorList());
	if (pConsList)
	{
		pConsList->push_back(pConstructorFunc);
	}
}

void CMetaDataCustomType::SetDestructor(const CMetaDataFunction *pDestructor)
{
	m_pDestructor = pDestructor;
}

void CMetaDataCustomType::AddMemberFunc(const CMetaDataFunction *pMFunc)
{
	std::vector<const CMetaDataFunction*> *pMFuncList(GetMemberFuncList());
	if (pMFuncList)
	{
		pMFuncList->push_back(pMFunc);
	}
}

void CMetaDataCustomType::AddMemberVar(const CMetaDataCustomTypeMemberVar *pMVar)
{
	std::vector<const CMetaDataCustomTypeMemberVar*> *pMVarList(GetMemberVarList());
	if (pMVarList)
	{
		pMVarList->push_back(pMVar);
	}
}

void CMetaDataCustomType::AddStaticMemberFunc(const CMetaDataFunction *pMFunc)
{
	std::vector<const CMetaDataFunction*> *pMFuncList(GetStaticMemberFuncList());
	if (pMFuncList)
	{
		pMFuncList->push_back(pMFunc);
	}
}

void CMetaDataCustomType::AddStaticMemberVar(const CMetaDataVariable *pMVar)
{
	std::vector<const CMetaDataVariable*> *pMVarList(GetStaticMemberVarList());
	if (pMVarList)
	{
		pMVarList->push_back(pMVar);
	}
}

bool CMetaDataCustomType::QueryBaseType(void *pObj, char *pBaseTypeName, void **outObj) const
{
	if (!pObj || !pBaseTypeName || !outObj) return false;

	std::vector<SMetaDataCustomTypeBaseType> *pBaseTypeList(m_pBaseTypeList);
	std::vector<SMetaDataCustomTypeBaseType>::iterator itr;
	char FullNameBuffer[256];
	
	if (!pBaseTypeList) return false;

	for (itr = pBaseTypeList->begin(); itr != pBaseTypeList->end(); ++itr)
	{
		if (itr->CustomType->GetFullName(FullNameBuffer, 256) && (strcmp(FullNameBuffer, pBaseTypeName) == 0
			|| strcmp(FullNameBuffer + 2, pBaseTypeName) == 0)) //+2是为了跳过"::"两个字符
		{
			*outObj = reinterpret_cast<void*>((unsigned int)pObj + itr->Offset);
			return true;
		}
	}
	return false;
}

bool CMetaDataCustomType::CallMemberFuction(char * pFunName, int param_count, ...) const
{
	if (!m_pMemberFuncList) return false;

	bool ret;
	const CMetaDataFunction *pFunc(nullptr);
	va_list pList;
	
	for (size_t i = 0; i < m_pMemberFuncList->size(); ++i)
	{
		if (strcmp(m_pMemberFuncList->at(i)->GetName(), pFunName) == 0)
		{
			pFunc = m_pMemberFuncList->at(i);
			break;
		}
	}
	if (!pFunc) return false;

	va_start(pList, param_count);
	try
	{
		ret = pFunc->CallFunction(param_count, pList);
	}
	catch (...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
	return ret;
}

bool CMetaDataCustomType::CallStaticMemberFuction(char * pFunName, int param_count, ...) const
{
	if (!m_pStaticMemberFuncList) return false;

	bool ret;
	const CMetaDataFunction *pFunc(nullptr);
	va_list pList;

	for (size_t i = 0; i < m_pStaticMemberFuncList->size(); ++i)
	{
		if (strcmp(m_pStaticMemberFuncList->at(i)->GetName(), pFunName) == 0)
		{
			pFunc = m_pStaticMemberFuncList->at(i);
			break;
		}
	}
	if (!pFunc) return false;

	va_start(pList, param_count);
	try
	{
		ret = pFunc->CallFunction(param_count, pList);
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
	if (this == pType) return true;

	std::vector<SMetaDataCustomTypeBaseType*> BaseList;
	if (FindBaseType(pType, BaseList))
	{
		return true;
	}

	std::vector<SMetaDataCustomTypeInterface*> IntfList;
	if (FindInterface(pType, IntfList))
	{
		return true;
	}

	return false;
}

void *CMetaDataCustomType::AsType(void *pObj, const CMetaDataType *pType) const
{
	if (this == pType) return pObj;

	unsigned int total_offset(0);
	size_t i;

	std::vector<SMetaDataCustomTypeBaseType*> BaseList;
	if (FindBaseType(pType, BaseList))
	{
		for (i = 0; i < BaseList.size(); ++i)
		{
			total_offset += BaseList[i]->Offset;
		}
		return reinterpret_cast<void*>((unsigned int)pObj + total_offset);
	}

	std::vector<SMetaDataCustomTypeInterface*> IntfList;
	if (FindInterface(pType, IntfList))
	{
		for (i = 0; i < IntfList.size(); ++i)
		{
			total_offset += IntfList[i]->Offset;
		}
		return reinterpret_cast<void*>((unsigned int)pObj + total_offset);
	}

	if (m_AsTypeExFunPtr)
	{
		return m_AsTypeExFunPtr(pObj, pType);
	}

	return nullptr;
}

bool CMetaDataCustomType::QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf) const
{
	if (!pObj || !pIntfName || !outIntf) return false;

	std::vector<SMetaDataCustomTypeInterface> *pIntfList(m_pInterfaceList);
	std::vector<SMetaDataCustomTypeInterface>::iterator itr;
	char FullNameBuffer[256];
	
	if (!pIntfList) return false;

	for (itr = pIntfList->begin(); itr != pIntfList->end(); ++itr)
	{
		if (itr->Intf->GetFullName(FullNameBuffer, 256) && (strcmp(FullNameBuffer, pIntfName) == 0
			|| strcmp(FullNameBuffer + 2, pIntfName) == 0)) //+2是为了跳过"::"两个字符
		{
			*outIntf = reinterpret_cast<IInterface*>((unsigned int)pObj + itr->Offset);
			return true;
		}
	}
	return false;
}

void *CMetaDataCustomType::NewObject(void) const
{
	return DoCreateObject();
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

bool CMetaDataCustomType::FindBaseType(const CMetaDataType * pType, std::vector<SMetaDataCustomTypeBaseType*> &BaseList) const
{
	if (!pType) return false;

	if (m_pBaseTypeList)
	{
		std::vector<SMetaDataCustomTypeBaseType>::iterator base_type_itr;
		for (base_type_itr = m_pBaseTypeList->begin(); base_type_itr != m_pBaseTypeList->end(); ++base_type_itr)
		{
			BaseList.push_back(&(*base_type_itr));
			if (base_type_itr->CustomType == pType)
			{
				return true;
			}
			else
			{
				if (base_type_itr->CustomType->FindBaseType(pType, BaseList))
				{
					return true;
				}
			}
			BaseList.pop_back();
		}
	}

	return false;
}

bool CMetaDataCustomType::FindInterface(const CMetaDataType * pIntf, std::vector<SMetaDataCustomTypeInterface*> &IntfList) const
{
	if (!pIntf) return false;

	if (m_pInterfaceList)
	{
		std::vector<SMetaDataCustomTypeInterface>::iterator intf_itr;
		for (intf_itr = m_pInterfaceList->begin(); intf_itr != m_pInterfaceList->end(); ++intf_itr)
		{
			IntfList.push_back(&(*intf_itr));
			if (intf_itr->Intf == pIntf)
			{
				return true;
			}
			else
			{
				if (intf_itr->Intf->FindInterface(pIntf, IntfList))
				{
					return true;
				}
			}
			IntfList.pop_back();
		}
	}

	return false;
}

void *CMetaDataCustomType::DoCreateObject(CParamVector *pParamTypes, va_list pList) const
{
	void *pReturn(nullptr);

	if (!m_pConstructorList || m_pConstructorList->size() == 0)
		throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "未定义构造函数元数据！");
	
	std::vector<const CMetaDataFunction*>::iterator itr;
	
	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(pParamTypes))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFunction(pParamTypes, pList, &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "构造函数调用失败！");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：构造函数无返回值！");
			}
			break;
		}
	}
	return pReturn;
}

void *CMetaDataCustomType::DoCreateObject(void) const
{
	void *pReturn(nullptr);

	if (!m_pConstructorList || m_pConstructorList->size() == 0)
		throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "未定义构造函数元数据！");
	
	std::vector<const CMetaDataFunction*>::iterator itr;
	
	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(nullptr))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFunction(0, static_cast<void**>(nullptr), &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "构造函数调用失败！");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "错误：构造函数无返回值！！");
			}
			break;
		}
	}
	return pReturn;
}