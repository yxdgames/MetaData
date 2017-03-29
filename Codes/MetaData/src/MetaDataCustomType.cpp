#include "stdafx.h"
#include "..\include\MetaDataCustomType.h"
#include "..\include\MetaDataInterface.h"
#include "..\..\include\ExceptionID.h"

CMetaDataCustomType::CMetaDataCustomType(char *pName, CMetaData *pParent, unsigned int size,
										 bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar)
	:CMetaDataType(pName, pParent, true, size),
	m_EnableBaseType(EnableBaseType), m_Sealed(bSealed), m_EnableStaticMemberFunc(EnableStaticMemberFunc), m_EnableStaticMemberVar(EnableStaticMemberVar),
	m_pBaseTypeList(NULL), m_pInterfaceList(NULL), m_pConstructorList(NULL), m_pMemberFuncList(NULL), m_pMemberVarList(NULL), m_pStaticMemberFuncList(NULL), m_pStaticMemberVarList(NULL)
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
		if (itr->CustomType->GetFullName(FullNameBuffer, 256) && strcmp(FullNameBuffer, pBaseTypeName) == 0)
		{
			*outObj = reinterpret_cast<void*>((unsigned int)pObj + itr->Offset);
			return true;
		}
	}
	return false;
}

bool CMetaDataCustomType::IsTypeOf(CMetaDataType *pType)
{
	if (this == pType) return true;

	std::vector<SMetaDataCustomTypeBaseType> *pBaseTypeList(m_pBaseTypeList);
	if (pBaseTypeList)
	{
		std::vector<SMetaDataCustomTypeBaseType>::iterator base_type_itr;
		for (base_type_itr = pBaseTypeList->begin(); base_type_itr != pBaseTypeList->end(); ++base_type_itr)
		{
			if (base_type_itr->CustomType == pType)
				return true;
		}
	}

	std::vector<SMetaDataCustomTypeInterface> *pIntfList(m_pInterfaceList);
	if (pIntfList)
	{
		std::vector<SMetaDataCustomTypeInterface>::iterator intf_itr;
		for (intf_itr = pIntfList->begin(); intf_itr != pIntfList->end(); ++intf_itr)
		{
			if (intf_itr->Intf == pType)
				return true;
		}
	}

	return false;
}

void *CMetaDataCustomType::AsType(void *pObj, CMetaDataType *pType)
{
	if (this == pType) return pObj;

	std::vector<SMetaDataCustomTypeBaseType> *pBaseTypeList(m_pBaseTypeList);
	if (pBaseTypeList)
	{
		std::vector<SMetaDataCustomTypeBaseType>::iterator base_type_itr;
		for (base_type_itr = pBaseTypeList->begin(); base_type_itr != pBaseTypeList->end(); ++base_type_itr)
		{
			if (base_type_itr->CustomType == pType)
				return reinterpret_cast<void*>((unsigned int)pObj + base_type_itr->Offset);
		}
	}

	std::vector<SMetaDataCustomTypeInterface> *pIntfList(m_pInterfaceList);
	if (pIntfList)
	{
		std::vector<SMetaDataCustomTypeInterface>::iterator intf_itr;
		for (intf_itr = pIntfList->begin(); intf_itr != pIntfList->end(); ++intf_itr)
		{
			if (intf_itr->Intf == pType)
				return reinterpret_cast<void*>((unsigned int)pObj + intf_itr->Offset);
		}
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
	void *pReturn(NULL);

	if (!m_pConstructorList) return pReturn;
	
	std::vector<CMetaDataFunction*>::iterator itr;
	

	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(NULL))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFuction(NULL, NULL, &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "构造函数调用失败！");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "错误：构造函数无返回值！！");
			}
		}
	}
	return pReturn;
}