#include "stdafx.h"
#include "..\include\MetaDataCustomType.h"
#include "..\include\MetaDataInterface.h"
#include "..\..\include\ExceptionID.h"

CMetaDataCustomType::CMetaDataCustomType(char *pName, CMetaData *pParent, unsigned int size,
										 bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar)
	:CMetaDataType(pName, pParent, true, size),
	m_EnableBaseType(EnableBaseType), m_Sealed(bSealed), m_EnableStaticMemberFunc(EnableStaticMemberFunc), m_EnableStaticMemberVar(EnableStaticMemberVar),
	m_pBaseTypeList(NULL), m_pInterfaceList(NULL), m_pConstructorList(NULL), m_pDestructor(NULL),
	m_pMemberFuncList(NULL), m_pMemberVarList(NULL), m_pStaticMemberFuncList(NULL), m_pStaticMemberVarList(NULL),
	m_AsTypeExFunPtr(NULL)
{
}


CMetaDataCustomType::~CMetaDataCustomType(void)
{
	if (m_pBaseTypeList)
	{
		delete m_pBaseTypeList;
		m_pBaseTypeList = NULL;
	}
	if (m_pInterfaceList)
	{
		delete m_pInterfaceList;
		m_pInterfaceList = NULL;
	}
	if (m_pConstructorList)
	{
		delete m_pConstructorList;
		m_pConstructorList = NULL;
	}
	if (m_pMemberFuncList)
	{
		delete m_pMemberFuncList;
		m_pMemberFuncList = NULL;
	}
	if (m_pMemberVarList)
	{
		delete m_pMemberVarList;
		m_pMemberVarList = NULL;
	}
	if (m_pStaticMemberFuncList)
	{
		delete m_pStaticMemberFuncList;
		m_pStaticMemberFuncList = NULL;
	}
	if (m_pStaticMemberVarList)
	{
		delete m_pStaticMemberVarList;
		m_pStaticMemberVarList = NULL;
	}
}

void CMetaDataCustomType::AddBaseType(CMetaDataCustomType *pBaseType, unsigned int Offset)
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

void CMetaDataCustomType::AddInterface(CMetaDataInterface *pIntf, unsigned int Offset)
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

void CMetaDataCustomType::AddConstructor(CMetaDataFunction *pConstructorFunc)
{
	std::vector<CMetaDataFunction*> *pConsList(GetConstructorList());
	if (pConsList)
	{
		pConsList->push_back(pConstructorFunc);
	}
}

void CMetaDataCustomType::SetDestructor(CMetaDataFunction *pDestructor)
{
	m_pDestructor = pDestructor;
}

void CMetaDataCustomType::AddMemberFunc(CMetaDataFunction *pMFunc)
{
	std::vector<CMetaDataFunction*> *pMFuncList(GetMemberFuncList());
	if (pMFuncList)
	{
		pMFuncList->push_back(pMFunc);
	}
}

void CMetaDataCustomType::AddMemberVar(CMetaDataCustomTypeMemberVar *pMVar)
{
	std::vector<CMetaDataCustomTypeMemberVar*> *pMVarList(GetMemberVarList());
	if (pMVarList)
	{
		pMVarList->push_back(pMVar);
	}
}

void CMetaDataCustomType::AddStaticMemberFunc(CMetaDataFunction *pMFunc)
{
	std::vector<CMetaDataFunction*> *pMFuncList(GetStaticMemberFuncList());
	if (pMFuncList)
	{
		pMFuncList->push_back(pMFunc);
	}
}

void CMetaDataCustomType::AddStaticMemberVar(CMetaDataVariable *pMVar)
{
	std::vector<CMetaDataVariable*> *pMVarList(GetStaticMemberVarList());
	if (pMVarList)
	{
		pMVarList->push_back(pMVar);
	}
}

bool CMetaDataCustomType::QueryBaseType(void *pObj, char *pBaseTypeName, void **outObj)
{
	if (!pObj || !pBaseTypeName || !outObj) return false;

	std::vector<SMetaDataCustomTypeBaseType> *pBaseTypeList(GetBaseTypeList());
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

bool CMetaDataCustomType::CallMemberFuction(char * pFunName, int param_count, ...)
{
	if (!m_pMemberFuncList) return false;

	bool ret;
	CMetaDataFunction *pFunc(NULL);
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

bool CMetaDataCustomType::CallStaticMemberFuction(char * pFunName, int param_count, ...)
{
	if (!m_pStaticMemberFuncList) return false;

	bool ret;
	CMetaDataFunction *pFunc(NULL);
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

bool CMetaDataCustomType::IsTypeOf(CMetaDataType *pType)
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

void *CMetaDataCustomType::AsType(void *pObj, CMetaDataType *pType)
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

	return NULL;
}

bool CMetaDataCustomType::QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf)
{
	if (!pObj || !pIntfName || !outIntf) return false;

	std::vector<SMetaDataCustomTypeInterface> *pIntfList(GetInterfaceList());
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

void *CMetaDataCustomType::NewObject(void)
{
	return DoCreateObject();
}

void CMetaDataCustomType::DeleteObject(void *pObj)
{
	if (pObj)
	{
		if (m_pDestructor)
			m_pDestructor->CallFunction(1, pObj);
		else throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "析构函数元数据不存在！");
	}
}

bool CMetaDataCustomType::FindBaseType(CMetaDataType * pType, std::vector<SMetaDataCustomTypeBaseType*> &BaseList)
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

bool CMetaDataCustomType::FindInterface(CMetaDataType * pIntf, std::vector<SMetaDataCustomTypeInterface*> &IntfList)
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

void *CMetaDataCustomType::DoCreateObject(CParamVector *pParamTypes, va_list pList)
{
	void *pReturn(NULL);

	if (!m_pConstructorList || !pList) return pReturn;
	
	std::vector<CMetaDataFunction*>::iterator itr;
	
	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(pParamTypes))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFunction(pParamTypes, pList, &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "构造函数调用失败！");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "错误：构造函数无返回值！");
			}
			break;
		}
	}
	return pReturn;
}

void *CMetaDataCustomType::DoCreateObject(void)
{
	void *pReturn(NULL);

	if (!m_pConstructorList) return pReturn;
	
	std::vector<CMetaDataFunction*>::iterator itr;
	
	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(NULL))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFunction(0, reinterpret_cast<void**>(NULL), &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "构造函数调用失败！");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "错误：构造函数无返回值！！");
			}
			break;
		}
	}
	return pReturn;
}