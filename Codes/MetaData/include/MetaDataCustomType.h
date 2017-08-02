#pragma once

#include "MetaDataType.h"
#include "MetaDataFunction.h"
#include "MetaDataCustomTypeMemberVar.h"
#include "MetaDataVariable.h"

class CMetaDataInterface;
class CMetaDataCustomType;

struct STRUCT_DESCRIPT SMetaDataCustomTypeBaseType
{
	CMetaDataCustomType *CustomType;
	unsigned int Offset;
};

struct STRUCT_DESCRIPT SMetaDataCustomTypeInterface
{
	CMetaDataInterface *Intf;
	unsigned int Offset;
};

typedef void *(*TpfunAsTypeEx)(void *pObj, const CMetaDataType *pType);

class CLASS_DESCRIPT CMetaDataCustomType : public CMetaDataType
{
public:
	CMetaDataCustomType(char *pName, CMetaData *pParent, unsigned int size,
		bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar);
	virtual ~CMetaDataCustomType(void);
public:
	//method
	void AddBaseType(CMetaDataCustomType *pBaseType, unsigned int Offset);
	void AddInterface(CMetaDataInterface *pIntf, unsigned int Offset);
	void AddConstructor(CMetaDataFunction *pConstructorFunc);
	void SetDestructor(CMetaDataFunction *pDestructor);
	void AddMemberFunc(CMetaDataFunction *pMFunc);
	void AddMemberVar(CMetaDataCustomTypeMemberVar *pMVar);
	void AddStaticMemberFunc(CMetaDataFunction *pMFunc);
	void AddStaticMemberVar(CMetaDataVariable *pMVar);

	//bool OutputMemberVar(char *pVarName, void *pOutputAddr);
	bool QueryBaseType(void *pObj, char *pBaseTypeName, void **outObj);
	bool __cdecl CallMemberFuction(char *pFunName, int param_count, ...);
	bool __cdecl CallStaticMemberFuction(char *pFunName, int param_count, ...);

	//override
	virtual bool IsTypeOf(const CMetaDataType *pType) const;
	virtual void *AsType(void *pObj, const CMetaDataType *pType) const;
	virtual bool QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf) const;
	virtual void *NewObject(void) const;
	virtual void DeleteObject(void *pObj) const;
	
	template<typename T>
	T *CreateObject(CParamVector *pParamTypes, ...) const;
	template<typename T>
	T *CreateObject(void) const;
public:
	//attribute
	virtual unsigned char GetTypeID(void) const						{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE; }
	unsigned int GetBaseTypeCount(void)								{ return (m_pBaseTypeList ? m_pBaseTypeList->size() : 0); }
	CMetaDataCustomType *GetBaseType(unsigned int index)			{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).CustomType : nullptr); }
	unsigned int GetBaseTypeOffset(unsigned int index)				{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).Offset : 0); }
	unsigned int GetInterfaceCount(void)							{ return (m_pInterfaceList ? m_pInterfaceList->size() : 0); }
	CMetaDataInterface *GetInterface(unsigned int index)			{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Intf : nullptr); }
	unsigned int GetInterfaceOffset(unsigned int index)				{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Offset : 0); }
	unsigned int GetConstructorCount(void)							{ return (m_pConstructorList ? m_pConstructorList->size() : 0); }
	CMetaDataFunction *GetConstructor(unsigned int index)			{ return (m_pConstructorList ? m_pConstructorList->at(index) : nullptr); }
	unsigned int GetMemberFuncCount(void)							{ return (m_pMemberFuncList ? m_pMemberFuncList->size() : 0); }
	CMetaDataFunction *GetMemberFunc(unsigned int index)			{ return (m_pMemberFuncList ? m_pMemberFuncList->at(index) : nullptr); }
	unsigned int GetMemberVarCount(void)							{ return (m_pMemberVarList ? m_pMemberVarList->size() : 0); }
	CMetaDataCustomTypeMemberVar *GetMemberVar(unsigned int index)	{ return (m_pMemberVarList ? m_pMemberVarList->at(index) : nullptr); }
	unsigned int GetStaticMemberFuncCount(void)						{ return (m_pStaticMemberFuncList ? m_pStaticMemberFuncList->size() : 0); }
	CMetaDataFunction *GetStaticMemberFunc(unsigned int index)		{ return (m_pStaticMemberFuncList ? m_pStaticMemberFuncList->at(index) : nullptr); }
	unsigned int GetStaticMemberVarCount(void)						{ return (m_pStaticMemberVarList ? m_pStaticMemberVarList->size() : 0); }
	CMetaDataVariable *GetStaticMemberVar(unsigned int index)		{ return (m_pStaticMemberVarList ? m_pStaticMemberVarList->at(index) : nullptr); }
public:
	//attribute
	void SetAsTypeExFunPtr(TpfunAsTypeEx value) { m_AsTypeExFunPtr = value; }
protected:
	std::vector<SMetaDataCustomTypeBaseType> *GetBaseTypeList(void)
	{
		if (!m_pBaseTypeList && m_EnableBaseType)
		{
			m_pBaseTypeList = new std::vector<SMetaDataCustomTypeBaseType>;
		}
		return m_pBaseTypeList;
	}
	std::vector<SMetaDataCustomTypeInterface> *GetInterfaceList(void)
	{
		if (!m_pInterfaceList)
		{
			m_pInterfaceList = new std::vector<SMetaDataCustomTypeInterface>;
		}
		return m_pInterfaceList;
	}
	std::vector<CMetaDataFunction*> *GetConstructorList(void)
	{
		if (!m_pConstructorList)
		{
			m_pConstructorList = new std::vector<CMetaDataFunction*>;
		}
		return m_pConstructorList;
	}
	CMetaDataFunction *GetDestructor(void)
	{
		return m_pDestructor;
	}
	std::vector<CMetaDataFunction*> *GetMemberFuncList(void)
	{
		if (!m_pMemberFuncList)
		{
			m_pMemberFuncList = new std::vector<CMetaDataFunction*>;
		}
		return m_pMemberFuncList;
	}
	std::vector<CMetaDataCustomTypeMemberVar*> *GetMemberVarList(void)
	{
		if (!m_pMemberVarList)
		{
			m_pMemberVarList = new std::vector<CMetaDataCustomTypeMemberVar*>;
		}
		return m_pMemberVarList;
	}
	std::vector<CMetaDataFunction*> *GetStaticMemberFuncList(void)
	{
		if (!m_pStaticMemberFuncList && m_EnableStaticMemberFunc)
		{
			m_pStaticMemberFuncList = new std::vector<CMetaDataFunction*>;
		}
		return m_pStaticMemberFuncList;
	}
	std::vector<CMetaDataVariable*> *GetStaticMemberVarList(void)
	{
		if (!m_pStaticMemberVarList && m_EnableStaticMemberVar)
		{
			m_pStaticMemberVarList = new std::vector<CMetaDataVariable*>;
		}
		return m_pStaticMemberVarList;
	}
private:
	bool FindBaseType(const CMetaDataType *pType, std::vector<SMetaDataCustomTypeBaseType*> &BaseList) const;
	bool FindInterface(const CMetaDataType *pIntf, std::vector<SMetaDataCustomTypeInterface*> &IntfList) const;
	void *DoCreateObject(CParamVector *pParamTypes, va_list pList) const;
	void *DoCreateObject(void) const;
private:
	bool											m_EnableBaseType;			//�Ƿ������л���
	bool											m_Sealed;					//�Ƿ������̳�
	bool											m_EnableStaticMemberFunc;	//�Ƿ������о�̬��Ա����
	bool											m_EnableStaticMemberVar;	//�Ƿ������о�̬��Ա����
	std::vector<SMetaDataCustomTypeBaseType>		*m_pBaseTypeList;			//����
	std::vector<SMetaDataCustomTypeInterface>		*m_pInterfaceList;			//�ӿ�
	std::vector<CMetaDataFunction*>					*m_pConstructorList;		//���캯��
	CMetaDataFunction								*m_pDestructor;				//��������
	std::vector<CMetaDataFunction*>					*m_pMemberFuncList;			//��Ա����
	std::vector<CMetaDataCustomTypeMemberVar*>		*m_pMemberVarList;			//��Ա����
	std::vector<CMetaDataFunction*>					*m_pStaticMemberFuncList;	//��̬��Ա����
	std::vector<CMetaDataVariable*>					*m_pStaticMemberVarList;	//��̬��Ա����
private:
	TpfunAsTypeEx									m_AsTypeExFunPtr;
};

#include "ExceptionMetaData.h"
#include "..\..\include\ExceptionID.h"
#include <stdarg.h>

//Template
template<typename T>
T *CMetaDataCustomType::CreateObject(CParamVector *pParamTypes, ...) const
{
	void *pReturn;
	void *pObj;
	va_list pList;
	va_start(pList, pParamTypes);
	try
	{
		pObj = DoCreateObject(pParamTypes, pList);
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
	void *pObj(DoCreateObject());
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