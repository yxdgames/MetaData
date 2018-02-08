#include "stdafx.h"
#include "..\include\MetaDataCustomType.h"
#include "..\include\MetaDataInterface.h"
#include "..\include\ExceptionMetaData.h"
#include "..\include\ExceptionIDMetaData.h"

/*----------------------------------------*/
/*                                        */
/*                Template                */
/*                                        */
/*----------------------------------------*/
//Member Function of CMetaDataCustomType
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
	//���һ���֧�ֵĽӿ�
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
	//���һ���֧�ֵ�δ֪�ӿ�
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

template<typename _CompareType>
bool CMetaDataCustomType::DoIsTypeOf(_CompareType ct_var) const
{
	if (this->Compare(ct_var)) return true;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;

	if (FindBaseType<_CompareType>(ct_var, CTODescriptList))
	{
		return true;
	}

	if (FindInterface<_CompareType>(ct_var, CTODescriptList))
	{
		return true;
	}

	if (FindUnknownInterface<_CompareType>(ct_var, CTODescriptList))
	{
		return true;
	}

	return false;
}

template<typename _CompareType, SAsTypeExTypeParam::EParamKind param_kind>
void *CMetaDataCustomType::DoAsType(void *pObj, _CompareType ct_var) const
{
	if (this->Compare(ct_var)) return pObj;

	TDUIntPtr total_offset(0);
	size_t i;

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindBaseType<_CompareType>(ct_var, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (FindInterface<_CompareType>(ct_var, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	if (FindUnknownInterface<_CompareType>(ct_var, CTODescriptList))
	{
		for (i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		return reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
	}

	return CallAsTypeExFun<_CompareType, param_kind>(pObj, ct_var);
}

template<typename _CompareType, SAsTypeExTypeParam::EParamKind param_kind>
inline void *CMetaDataCustomType::CallAsTypeExFun(void *pObj, _CompareType ct_var) const
{
	return nullptr;
}

template<>
inline void *CMetaDataCustomType::CallAsTypeExFun<const CMetaDataType*, SAsTypeExTypeParam::EParamKind::pkMDType>(void *pObj, const CMetaDataType *ct_var) const
{
	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkMDType;
		AsTypeExTypeParam.Param.pType = ct_var;
		return m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
	}
	else return nullptr;
}

template<>
inline void *CMetaDataCustomType::CallAsTypeExFun<const TDGUID&, SAsTypeExTypeParam::EParamKind::pkTypeGUID>(void *pObj, const TDGUID &ct_var) const
{
	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkTypeGUID;
		AsTypeExTypeParam.Param.ptype_guid = &ct_var;
		return m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
	}
	else return nullptr;
}

template<>
inline void *CMetaDataCustomType::CallAsTypeExFun<const char*, SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr>(void *pObj, const char *ct_var) const
{
	if (m_AsTypeExFunPtr)
	{
		SAsTypeExTypeParam AsTypeExTypeParam;
		AsTypeExTypeParam.ParamKind = SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr;
		AsTypeExTypeParam.Param.pTypeFullName = ct_var;
		return m_AsTypeExFunPtr(pObj, AsTypeExTypeParam);
	}
	else return nullptr;
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

bool CMetaDataCustomType::QueryBaseType(void *pObj, const char *pBaseTypeName, void **outObj) const
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

	*outObj = CallAsTypeExFun<const char*, SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr>(pObj, pBaseTypeName);
	return *outObj != nullptr;
}

bool CMetaDataCustomType::QueryBaseType(void * pObj, const TDGUID & BaseTypeGuid, void ** outObj) const
{
	if (!pObj || !outObj) return false;

	if (this->Compare(BaseTypeGuid))
	{
		*outObj = pObj;
		return true;
	}

	TDUIntPtr total_offset(0);

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindBaseType<const TDGUID&>(BaseTypeGuid, CTODescriptList))
	{
		for (size_t i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		*outObj = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
		return true;
	}

	*outObj = CallAsTypeExFun<const TDGUID&, SAsTypeExTypeParam::EParamKind::pkTypeGUID>(pObj, BaseTypeGuid);
	return *outObj != nullptr;
}

bool CMetaDataCustomType::QueryUnknownInterface(void * pObj, const char * pUnkwnIntfName, void ** outUnkwnIntf) const
{
	if (!pObj || !pUnkwnIntfName || !outUnkwnIntf) return false;

	if (this->Compare(pUnkwnIntfName))
	{
		*outUnkwnIntf = pObj;
		return true;
	}

	TDUIntPtr total_offset(0);

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindUnknownInterface<const char*>(pUnkwnIntfName, CTODescriptList))
	{
		for (size_t i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		*outUnkwnIntf = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
		return true;
	}

	*outUnkwnIntf = CallAsTypeExFun<const char*, SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr>(pObj, pUnkwnIntfName);
	return *outUnkwnIntf != nullptr;
}

bool CMetaDataCustomType::QueryUnknownInterface(void * pObj, const TDGUID & UnkwnIntfGuid, void ** outUnkwnIntf) const
{
	if (!pObj || !outUnkwnIntf) return false;

	if (this->Compare(UnkwnIntfGuid))
	{
		*outUnkwnIntf = pObj;
		return true;
	}

	TDUIntPtr total_offset(0);

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindUnknownInterface<const TDGUID&>(UnkwnIntfGuid, CTODescriptList))
	{
		for (size_t i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		*outUnkwnIntf = reinterpret_cast<void*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
		return true;
	}

	*outUnkwnIntf = CallAsTypeExFun<const TDGUID&, SAsTypeExTypeParam::EParamKind::pkTypeGUID>(pObj, UnkwnIntfGuid);
	return *outUnkwnIntf != nullptr;
}

bool CMetaDataCustomType::CallMemberFuction(char * pFunName, CFuncParamMDVector *pParamMDVector, ...) const
{
	if (!m_pMemberFuncList) return false;

	bool ret;
	const CMetaDataFunction *pFunc(nullptr);
	va_list pList;
	
	for (size_t i = 0; i < m_pMemberFuncList->size(); ++i)
	{
		if (strcmp(m_pMemberFuncList->at(i)->GetName(), pFunName) == 0
			&& m_pMemberFuncList->at(i)->FuncParamsCheck(pParamMDVector))
		{
			pFunc = m_pMemberFuncList->at(i);
			break;
		}
	}
	if (!pFunc) return false;

	va_start(pList, pParamMDVector);
	try
	{
		ret = pFunc->CallFunction(pParamMDVector, pList, nullptr);
	}
	catch (...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);
	return ret;
}

bool CMetaDataCustomType::CallStaticMemberFuction(char * pFunName, CFuncParamMDVector *pParamMDVector, ...) const
{
	if (!m_pStaticMemberFuncList) return false;

	bool ret;
	const CMetaDataFunction *pFunc(nullptr);
	va_list pList;

	for (size_t i = 0; i < m_pStaticMemberFuncList->size(); ++i)
	{
		if (strcmp(m_pStaticMemberFuncList->at(i)->GetName(), pFunName) == 0
			&& m_pStaticMemberFuncList->at(i)->FuncParamsCheck(pParamMDVector))
		{
			pFunc = m_pStaticMemberFuncList->at(i);
			break;
		}
	}
	if (!pFunc) return false;

	va_start(pList, pParamMDVector);
	try
	{
		ret = pFunc->CallFunction(pParamMDVector, pList, nullptr);
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
	return DoIsTypeOf<const CMetaDataType*>(pType);
}

bool CMetaDataCustomType::IsTypeOf(const TDGUID &type_guid) const
{
	return DoIsTypeOf<const TDGUID&>(type_guid);
}

bool CMetaDataCustomType::IsTypeOf(const char * pTypeFullName) const
{
	return DoIsTypeOf<const char*>(pTypeFullName);
}

void *CMetaDataCustomType::AsType(void *pObj, const CMetaDataType *pType) const
{
	return DoAsType<const CMetaDataType*, SAsTypeExTypeParam::EParamKind::pkMDType>(pObj, pType);
}

void *CMetaDataCustomType::AsType(void *pObj, const TDGUID &type_guid) const
{
	return DoAsType<const TDGUID&, SAsTypeExTypeParam::EParamKind::pkTypeGUID>(pObj, type_guid);
}

void * CMetaDataCustomType::AsType(void * pObj, const char * pTypeFullName) const
{
	return DoAsType<const char*, SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr>(pObj, pTypeFullName);
}

bool CMetaDataCustomType::QueryInterface(void *pObj, const char *pIntfName, IInterface **outIntf) const
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

	*outIntf = reinterpret_cast<IInterface*>(CallAsTypeExFun<const char*, SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr>(pObj, pIntfName));
	return *outIntf != nullptr;
}

bool CMetaDataCustomType::QueryInterface(void * pObj, const TDGUID & IntfGuid, IInterface ** outIntf) const
{
	if (!pObj || !outIntf) return false;

	if (this->Compare(IntfGuid))
	{
		*outIntf = reinterpret_cast<IInterface*>(pObj);
		return true;
	}

	TDUIntPtr total_offset(0);

	std::vector<SMDCustomTypeOffsetDescriptInCustomType*> CTODescriptList;
	if (FindInterface<const TDGUID&>(IntfGuid, CTODescriptList))
	{
		for (size_t i = 0; i < CTODescriptList.size(); ++i)
		{
			total_offset += CTODescriptList[i]->Offset;
		}
		*outIntf = reinterpret_cast<IInterface*>(reinterpret_cast<TDUIntPtr>(pObj) + total_offset);
		return true;
	}

	*outIntf = reinterpret_cast<IInterface*>(CallAsTypeExFun<const TDGUID&, SAsTypeExTypeParam::EParamKind::pkTypeGUID>(pObj, IntfGuid));
	return *outIntf != nullptr;
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
		else throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "��������Ԫ���ݲ����ڣ�");
	}
}

void *CMetaDataCustomType::DoCreateObject(CFuncParamMDVector *pParamMDVector, va_list pParamList) const
{
	void *pReturn(nullptr);

	if (!m_pConstructorList || m_pConstructorList->size() == 0)
		throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "����δ���幹�캯��Ԫ���ݣ�");
	
	std::vector<const CMetaDataFunction*>::iterator itr;
	
	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(pParamMDVector))
		{
			if (!(*itr)->ReturnIsVoid())
			{
				if (!(*itr)->CallFunction(pParamMDVector, pParamList, &pReturn))
				{
					throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "���󣺹��캯������ʧ�ܣ�");
				}
			}
			else
			{
				throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "���󣺹��캯���޷���ֵ��");
			}
			break;
		}
	}
	if (!pReturn) throw new ExceptionMetaData(D_E_ID_MD_META_DATA_OF_FUNC_CALL, "������ƥ��Ĺ��캯����");
	return pReturn;
}
