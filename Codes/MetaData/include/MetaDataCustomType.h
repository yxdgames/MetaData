#pragma once
/*--------------------------------------------------------------------------------------------*/
/*                                                                                            */
/*                                CMetaDataCustomType                                         */
/*                                                                                            */
/*��ǿ����                                                                                    */
/* m_pBaseTypeList: ����Զ������͵Ļ�����Ϣ��                                                */
/* m_pInterfaceList: ����Զ������͵ġ�IInterfaceϵ�ӿڡ��Ľӿ���Ϣ��                         */
/* m_pUnknownInterfaceList: ����Զ������͵�һ�С���IInterfaceϵ�ӿڡ��Ľӿ���Ϣ��            */
/*                                                                                            */
/* ��IInterfaceϵ�ӿڣ�ֻҪ�����ϡ�IInterfaceϵ�ӿ�Ҫ�󡱵ģ����Ƿ�IInterfaceϵ�ӿڡ�         */
/*                                                                                            */
/* ע��m_pUnknownInterfaceList�д�ŵ���Ϣ�ǽӿ���Ϣ��������Щ�ӿ����û��Զ���Ķ����Ľӿڣ�  */
/* �����ϡ�IInterfaceϵ�ӿ�Ҫ�󡱡�                                                           */
/*                                                                                            */
/* ����ϵͳ�ж�����һ��IUnkwn�Ľӿڣ���û���κλ���ӿڣ��������һ������IInterfaceϵ�ӿڡ��� */
/* ��Ȼ���û�Ҳ���԰��Լ���Ҫ�󣬶����Լ������Ľӿڣ�����ӿڿ���������IUnkwn��               */
/* Ҳ������IUnkwn������û���κλ���ӿڣ���ȫ��������...����                                  */
/* ���е���Щ����IInterfaceϵ�ӿڡ����Ǽ��뵽m_pUnknownInterfaceList��ȥ��                    */
/* ��ʹ�ù����У���ʹ�÷�ֱ��ǿת����ȷ�Ľӿ����ͣ�����ʹ�á�                                 */
/*                                                                                            */
/*--------------------------------------------------------------------------------------------*/
#include "MetaDataType.h"
#include "MetaDataFunction.h"
#include "MetaDataCustomTypeMemberVar.h"
#include "MetaDataCustomTypeProperty.h"
#include "MetaDataVariable.h"

class CLASS_DESCRIPT CMetaDataCustomType;

struct STRUCT_DESCRIPT SMDCustomTypeOffsetDescriptInCustomType
{
	const CMetaDataCustomType *CustomType;
	TDUIntPtr Offset;
};

struct STRUCT_DESCRIPT SMDBaseTypeOfCustomType
	: public SMDCustomTypeOffsetDescriptInCustomType
{
};

class CLASS_DESCRIPT CMetaDataInterface;

struct STRUCT_DESCRIPT SMDInterfaceOfCustomType
	: public SMDCustomTypeOffsetDescriptInCustomType
{
	const CMetaDataInterface *Intf(void)
	{
		return reinterpret_cast<const CMetaDataInterface*>(CustomType);
	}
};

struct STRUCT_DESCRIPT SAsTypeExTypeParam
{
	enum EParamKind { pkNone, pkMDType, pkTypeGUID, pkTypeFullNameStr, };
	EParamKind ParamKind;
	union {
		const CMetaDataType *pType;
		const TDGUID *ptype_guid;
		const char *pTypeFullName;
	} Param;
};

typedef void *(*TpfunAsTypeEx)(void *pObj, const SAsTypeExTypeParam &AsTypeExParam);

class CLASS_DESCRIPT CMetaDataCustomType : public CMetaDataType
{
public:
	CMetaDataCustomType(const char *pName, const CMetaData *pParent, size_t size,
		bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar);
	virtual ~CMetaDataCustomType(void);
public:
	//method
	inline void AddBaseType(const CMetaDataCustomType *pBaseType, TDUIntPtr Offset);
	void AddInterface(const CMetaDataInterface *pIntf, TDUIntPtr Offset);
	void AddUnknownInterface(const CMetaDataInterface *pIntf, TDUIntPtr Offset);
	void AddConstructor(const CMetaDataFunction *pConstructorFunc) { GetConstructorList()->push_back(pConstructorFunc); }
	void SetDestructor(const CMetaDataFunction *pDestructor) { m_pDestructor = pDestructor; }
	void AddMemberFunc(const CMetaDataFunction *pMFunc) { GetMemberFuncList()->push_back(pMFunc); }
	void AddMemberVar(const CMetaDataCustomTypeMemberVar *pMVar) { GetMemberVarList()->push_back(pMVar); }
	void AddProperty(const CMetaDataCustomTypeProperty *pProp) { GetPropertyList()->push_back(pProp); }
	inline void AddStaticMemberFunc(const CMetaDataFunction *pMFunc);
	inline void AddStaticMemberVar(const CMetaDataVariable *pMVar);

	//bool OutputMemberVar(char *pVarName, void *pOutputAddr) const;
	bool QueryBaseType(void *pObj, const char *pBaseTypeName, void **outObj) const;
	bool QueryBaseType(void *pObj, const TDGUID &BaseTypeGuid, void **outObj) const;
	bool QueryUnknownInterface(void *pObj, const char *pUnkwnIntfName, void **outUnkwnIntf) const;
	bool QueryUnknownInterface(void *pObj, const TDGUID &UnkwnIntfGuid, void **outUnkwnIntf) const;
	bool __cdecl CallMemberFuction(char *pFunName, CFuncParamMDVector *pParamMDVector, ...) const;
	bool __cdecl CallStaticMemberFuction(char *pFunName, CFuncParamMDVector *pParamMDVector, ...) const;
public:
	//method - override
	virtual bool IsTypeOf(const CMetaDataType *pType) const;
	virtual bool IsTypeOf(const TDGUID &type_guid) const;
	virtual bool IsTypeOf(const char *pTypeFullName) const;
	virtual void *AsType(void *pObj, const CMetaDataType *pType) const;
	virtual void *AsType(void *pObj, const TDGUID &type_guid) const;
	virtual void *AsType(void *pObj, const char *pTypeFullName) const;
	virtual bool QueryInterface(void *pObj, const char *pIntfName, IInterface **outIntf) const;
	virtual bool QueryInterface(void *pObj, const TDGUID &IntfGuid, IInterface **outIntf) const;
	virtual void *NewObject(void) const;
	virtual void DeleteObject(void *pObj) const;
public:
	template<typename T>
	T *CreateObject(CFuncParamMDVector *pParamMDVector, ...) const;
	template<typename T>
	T *CreateObject(void) const;
public:
	//attribute
	virtual unsigned char GetTypeID(void) const									{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE; }
	size_t GetBaseTypeCount(void)  const										{ return (m_pBaseTypeList ? m_pBaseTypeList->size() : 0); }
	const CMetaDataCustomType *GetBaseType(size_t index)  const					{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).CustomType : nullptr); }
	TDUIntPtr GetBaseTypeOffset(size_t index)  const							{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).Offset : 0); }
	size_t GetInterfaceCount(void)  const										{ return (m_pInterfaceList ? m_pInterfaceList->size() : 0); }
	const CMetaDataInterface *GetInterface(size_t index)  const					{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Intf() : nullptr); }
	TDUIntPtr GetInterfaceOffset(size_t index)  const							{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Offset : 0); }
	size_t GetUnknownInterfaceCount(void)  const								{ return (m_pUnknownInterfaceList ? m_pUnknownInterfaceList->size() : 0); }
	const CMetaDataInterface *GetUnknownInterface(size_t index)  const			{ return (m_pUnknownInterfaceList ? m_pUnknownInterfaceList->at(index).Intf() : nullptr); }
	TDUIntPtr GetUnknownInterfaceOffset(size_t index)  const					{ return (m_pUnknownInterfaceList ? m_pUnknownInterfaceList->at(index).Offset : 0); }
	size_t GetConstructorCount(void)  const										{ return (m_pConstructorList ? m_pConstructorList->size() : 0); }
	const CMetaDataFunction *GetConstructor(size_t index)  const				{ return (m_pConstructorList ? m_pConstructorList->at(index) : nullptr); }
	size_t GetMemberFuncCount(void)  const										{ return (m_pMemberFuncList ? m_pMemberFuncList->size() : 0); }
	const CMetaDataFunction *GetMemberFunc(size_t index)  const					{ return (m_pMemberFuncList ? m_pMemberFuncList->at(index) : nullptr); }
	size_t GetMemberVarCount(void)  const										{ return (m_pMemberVarList ? m_pMemberVarList->size() : 0); }
	const CMetaDataCustomTypeMemberVar *GetMemberVar(size_t index)  const		{ return (m_pMemberVarList ? m_pMemberVarList->at(index) : nullptr); }
	size_t GetPropertyCount(void)  const										{ return (m_pPropertyList ? m_pPropertyList->size() : 0); }
	const CMetaDataCustomTypeProperty *GetProperty(size_t index)  const			{ return (m_pPropertyList ? m_pPropertyList->at(index) : nullptr); }
	size_t GetStaticMemberFuncCount(void)  const								{ return (m_pStaticMemberFuncList ? m_pStaticMemberFuncList->size() : 0); }
	const CMetaDataFunction *GetStaticMemberFunc(size_t index)  const			{ return (m_pStaticMemberFuncList ? m_pStaticMemberFuncList->at(index) : nullptr); }
	size_t GetStaticMemberVarCount(void)  const									{ return (m_pStaticMemberVarList ? m_pStaticMemberVarList->size() : 0); }
	const CMetaDataVariable *GetStaticMemberVar(size_t index)  const			{ return (m_pStaticMemberVarList ? m_pStaticMemberVarList->at(index) : nullptr); }
public:
	//attribute
	void SetAsTypeExFunPtr(TpfunAsTypeEx value) { m_AsTypeExFunPtr = value; }
protected:
	inline std::vector<SMDBaseTypeOfCustomType> *GetBaseTypeList(void);
	inline std::vector<SMDInterfaceOfCustomType> *GetInterfaceList(void);
	inline std::vector<SMDInterfaceOfCustomType> *GetUnknownInterfaceList(void);
	inline std::vector<const CMetaDataFunction*> *GetConstructorList(void);
	const CMetaDataFunction *GetDestructor(void) { return m_pDestructor; }
	inline std::vector<const CMetaDataFunction*> *GetMemberFuncList(void);
	inline std::vector<const CMetaDataCustomTypeMemberVar*> *GetMemberVarList(void);
	inline std::vector<const CMetaDataCustomTypeProperty*> *GetPropertyList(void);
	inline std::vector<const CMetaDataFunction*> *GetStaticMemberFuncList(void);
	inline std::vector<const CMetaDataVariable*> *GetStaticMemberVarList(void);
private:
	void *DoCreateObject(CFuncParamMDVector *pParamMDVector, va_list pParamList) const;
private:
	template<typename _CompareType>
	bool FindBaseType(_CompareType ct_var, std::vector<SMDCustomTypeOffsetDescriptInCustomType*> &BaseList) const;
	template<typename _CompareType>
	bool FindInterface(_CompareType ct_var, std::vector<SMDCustomTypeOffsetDescriptInCustomType*> &IntfList) const;
	template<typename _CompareType>
	bool FindUnknownInterface(_CompareType ct_var, std::vector<SMDCustomTypeOffsetDescriptInCustomType*> &IntfList) const;
	template<typename _CompareType>
	bool DoIsTypeOf(_CompareType ct_var) const;
	template<typename _CompareType, SAsTypeExTypeParam::EParamKind param_kind>
	void *DoAsType(void *pObj, _CompareType ct_var) const;
	template<typename _CompareType, SAsTypeExTypeParam::EParamKind param_kind>
	inline void *CallAsTypeExFun(void *pObj, _CompareType ct_var) const;
private:
	bool												m_EnableBaseType;			//�Ƿ������л���
	bool												m_Sealed;					//�Ƿ������̳�
	bool												m_EnableStaticMemberFunc;	//�Ƿ������о�̬��Ա����
	bool												m_EnableStaticMemberVar;	//�Ƿ������о�̬��Ա����
	std::vector<SMDBaseTypeOfCustomType>				*m_pBaseTypeList;			//����
	std::vector<SMDInterfaceOfCustomType>				*m_pInterfaceList;			//�ӿ�(IInterfaceϵ�ӿڱ�)
	std::vector<SMDInterfaceOfCustomType>				*m_pUnknownInterfaceList;	//δ֪�ӿ�(��IInterfaceϵ�ӿ�ϵ��)
	std::vector<const CMetaDataFunction*>				*m_pConstructorList;		//���캯��
	const CMetaDataFunction								*m_pDestructor;				//��������
	std::vector<const CMetaDataFunction*>				*m_pMemberFuncList;			//��Ա����
	std::vector<const CMetaDataCustomTypeMemberVar*>	*m_pMemberVarList;			//��Ա����
	std::vector<const CMetaDataCustomTypeProperty*>		*m_pPropertyList;			//����
	std::vector<const CMetaDataFunction*>				*m_pStaticMemberFuncList;	//��̬��Ա����
	std::vector<const CMetaDataVariable*>				*m_pStaticMemberVarList;	//��̬��Ա����
private:
	TpfunAsTypeEx										m_AsTypeExFunPtr;
};

/*--------------------------------*/
/*   Inline Function Definition   */
/*--------------------------------*/
inline void CMetaDataCustomType::AddBaseType(const CMetaDataCustomType *pBaseType, TDUIntPtr Offset)
{
	std::vector<SMDBaseTypeOfCustomType> *pBaseTypeList(GetBaseTypeList());
	if (pBaseTypeList)
	{
		SMDBaseTypeOfCustomType bt;
		bt.CustomType = pBaseType;
		bt.Offset = Offset;
		pBaseTypeList->push_back(bt);
	}
}

inline void CMetaDataCustomType::AddStaticMemberFunc(const CMetaDataFunction *pMFunc)
{
	std::vector<const CMetaDataFunction*> *pSMFuncList(GetStaticMemberFuncList());
	if (pSMFuncList)
	{
		pSMFuncList->push_back(pMFunc);
	}
}

inline void CMetaDataCustomType::AddStaticMemberVar(const CMetaDataVariable *pMVar)
{
	std::vector<const CMetaDataVariable*> *pSMVarList(GetStaticMemberVarList());
	if (pSMVarList)
	{
		pSMVarList->push_back(pMVar);
	}
}

inline std::vector<SMDBaseTypeOfCustomType> *CMetaDataCustomType::GetBaseTypeList(void)
{
	if (!m_pBaseTypeList && m_EnableBaseType)
	{
		m_pBaseTypeList = new std::vector<SMDBaseTypeOfCustomType>;
	}
	return m_pBaseTypeList;
}

inline std::vector<SMDInterfaceOfCustomType> *CMetaDataCustomType::GetInterfaceList(void)
{
	if (!m_pInterfaceList)
	{
		m_pInterfaceList = new std::vector<SMDInterfaceOfCustomType>;
	}
	return m_pInterfaceList;
}

inline std::vector<SMDInterfaceOfCustomType> *CMetaDataCustomType::GetUnknownInterfaceList(void)
{
	if (!m_pUnknownInterfaceList)
	{
		m_pUnknownInterfaceList = new std::vector<SMDInterfaceOfCustomType>;
	}
	return m_pUnknownInterfaceList;
}

inline std::vector<const CMetaDataFunction*> *CMetaDataCustomType::GetConstructorList(void)
{
	if (!m_pConstructorList)
	{
		m_pConstructorList = new std::vector<const CMetaDataFunction*>;
	}
	return m_pConstructorList;
}

inline std::vector<const CMetaDataFunction*> *CMetaDataCustomType::GetMemberFuncList(void)
{
	if (!m_pMemberFuncList)
	{
		m_pMemberFuncList = new std::vector<const CMetaDataFunction*>;
	}
	return m_pMemberFuncList;
}

inline std::vector<const CMetaDataCustomTypeMemberVar*> *CMetaDataCustomType::GetMemberVarList(void)
{
	if (!m_pMemberVarList)
	{
		m_pMemberVarList = new std::vector<const CMetaDataCustomTypeMemberVar*>;
	}
	return m_pMemberVarList;
}

inline std::vector<const CMetaDataCustomTypeProperty*> *CMetaDataCustomType::GetPropertyList(void)
{
	if (!m_pPropertyList)
	{
		m_pPropertyList = new std::vector<const CMetaDataCustomTypeProperty*>;
	}
	return m_pPropertyList;
}

inline std::vector<const CMetaDataFunction*> *CMetaDataCustomType::GetStaticMemberFuncList(void)
{
	if (!m_pStaticMemberFuncList && m_EnableStaticMemberFunc)
	{
		m_pStaticMemberFuncList = new std::vector<const CMetaDataFunction*>;
	}
	return m_pStaticMemberFuncList;
}

inline std::vector<const CMetaDataVariable*> *CMetaDataCustomType::GetStaticMemberVarList(void)
{
	if (!m_pStaticMemberVarList && m_EnableStaticMemberVar)
	{
		m_pStaticMemberVarList = new std::vector<const CMetaDataVariable*>;
	}
	return m_pStaticMemberVarList;
}

/*--------------*/
/*   Template   */
/*--------------*/
#include <stdarg.h>

template<typename T>
T *CMetaDataCustomType::CreateObject(CFuncParamMDVector *pParamMDVector, ...) const
{
	void *pReturn;
	void *pObj;
	va_list pList;
	va_start(pList, pParamMDVector);
	try
	{
		pObj = DoCreateObject(pParamMDVector, pList);
		if (pObj)
		{
			pReturn = this->AsType(pObj, TypeTraits<T>::GetMetaDataType());
			if (!pReturn)
			{
				this->DeleteObject(pObj);
			}
		}
		else pReturn = nullptr;
	}
	catch(...)
	{
		va_end(pList);
		throw;
	}
	va_end(pList);

	return reinterpret_cast<T*>(pReturn);
}

template<typename T>
inline T *CMetaDataCustomType::CreateObject(void) const
{
	void *pReturn;
	void *pObj(DoCreateObject(nullptr, nullptr));
	if (pObj)
	{
		pReturn = this->AsType(pObj, TypeTraits<T>::GetMetaDataType());
		if (!pReturn)
		{
			this->DeleteObject(pObj);
		}
	}
	else pReturn = nullptr;

	return reinterpret_cast<T*>(pReturn);
}
