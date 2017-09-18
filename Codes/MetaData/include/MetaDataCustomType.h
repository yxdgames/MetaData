#pragma once

#include "MetaDataType.h"
#include "MetaDataFunction.h"
#include "MetaDataCustomTypeMemberVar.h"
#include "MetaDataCustomTypeProperty.h"
#include "MetaDataVariable.h"

class CMetaDataCustomType;

struct STRUCT_DESCRIPT SMDCustomTypeOffsetDescript
{
	const CMetaDataCustomType *CustomType;
	TDUIntPtr Offset;
};

struct STRUCT_DESCRIPT SMDBaseTypeOfCustomType
	: public SMDCustomTypeOffsetDescript
{
};

class CMetaDataInterface;

struct STRUCT_DESCRIPT SMDInterfaceOfCustomType
	: public SMDCustomTypeOffsetDescript
{
	const CMetaDataInterface *Intf(void)
	{
		return reinterpret_cast<const CMetaDataInterface*>(CustomType);
	}
};

typedef void *(*TpfunAsTypeEx)(void *pObj, const CMetaDataType *pType);

class CLASS_DESCRIPT CMetaDataCustomType : public CMetaDataType
{
public:
	CMetaDataCustomType(const char *pName, const CMetaData *pParent, size_t size,
		bool EnableBaseType, bool bSealed, bool EnableStaticMemberFunc, bool EnableStaticMemberVar);
	virtual ~CMetaDataCustomType(void);
public:
	//method
	void AddBaseType(const CMetaDataCustomType *pBaseType, TDUIntPtr Offset);
	void AddInterface(const CMetaDataInterface *pIntf, TDUIntPtr Offset);
	void AddConstructor(const CMetaDataFunction *pConstructorFunc);
	void SetDestructor(const CMetaDataFunction *pDestructor);
	void AddMemberFunc(const CMetaDataFunction *pMFunc);
	void AddMemberVar(const CMetaDataCustomTypeMemberVar *pMVar);
	void AddProperty(const CMetaDataCustomTypeProperty *pProp);
	void AddStaticMemberFunc(const CMetaDataFunction *pMFunc);
	void AddStaticMemberVar(const CMetaDataVariable *pMVar);

	//bool OutputMemberVar(char *pVarName, void *pOutputAddr);
	bool QueryBaseType(void *pObj, char *pBaseTypeName, void **outObj) const;
	bool __cdecl CallMemberFuction(char *pFunName, CParamVector *pParamTypes, ...) const;
	bool __cdecl CallStaticMemberFuction(char *pFunName, CParamVector *pParamTypes, ...) const;

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
	virtual unsigned char GetTypeID(void) const									{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE; }
	size_t GetBaseTypeCount(void)  const										{ return (m_pBaseTypeList ? m_pBaseTypeList->size() : 0); }
	const CMetaDataCustomType *GetBaseType(size_t index)  const					{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).CustomType : nullptr); }
	TDUIntPtr GetBaseTypeOffset(size_t index)  const							{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).Offset : 0); }
	size_t GetInterfaceCount(void)  const										{ return (m_pInterfaceList ? m_pInterfaceList->size() : 0); }
	const CMetaDataInterface *GetInterface(size_t index)  const					{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Intf() : nullptr); }
	TDUIntPtr GetInterfaceOffset(size_t index)  const							{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Offset : 0); }
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
	std::vector<SMDBaseTypeOfCustomType> *GetBaseTypeList(void)
	{
		if (!m_pBaseTypeList && m_EnableBaseType)
		{
			m_pBaseTypeList = new std::vector<SMDBaseTypeOfCustomType>;
		}
		return m_pBaseTypeList;
	}
	std::vector<SMDInterfaceOfCustomType> *GetInterfaceList(void)
	{
		if (!m_pInterfaceList)
		{
			m_pInterfaceList = new std::vector<SMDInterfaceOfCustomType>;
		}
		return m_pInterfaceList;
	}
	std::vector<const CMetaDataFunction*> *GetConstructorList(void)
	{
		if (!m_pConstructorList)
		{
			m_pConstructorList = new std::vector<const CMetaDataFunction*>;
		}
		return m_pConstructorList;
	}
	const CMetaDataFunction *GetDestructor(void)
	{
		return m_pDestructor;
	}
	std::vector<const CMetaDataFunction*> *GetMemberFuncList(void)
	{
		if (!m_pMemberFuncList)
		{
			m_pMemberFuncList = new std::vector<const CMetaDataFunction*>;
		}
		return m_pMemberFuncList;
	}
	std::vector<const CMetaDataCustomTypeMemberVar*> *GetMemberVarList(void)
	{
		if (!m_pMemberVarList)
		{
			m_pMemberVarList = new std::vector<const CMetaDataCustomTypeMemberVar*>;
		}
		return m_pMemberVarList;
	}
	std::vector<const CMetaDataCustomTypeProperty*> *GetPropertyList(void)
	{
		if (!m_pPropertyList)
		{
			m_pPropertyList = new std::vector<const CMetaDataCustomTypeProperty*>;
		}
		return m_pPropertyList;
	}
	std::vector<const CMetaDataFunction*> *GetStaticMemberFuncList(void)
	{
		if (!m_pStaticMemberFuncList && m_EnableStaticMemberFunc)
		{
			m_pStaticMemberFuncList = new std::vector<const CMetaDataFunction*>;
		}
		return m_pStaticMemberFuncList;
	}
	std::vector<const CMetaDataVariable*> *GetStaticMemberVarList(void)
	{
		if (!m_pStaticMemberVarList && m_EnableStaticMemberVar)
		{
			m_pStaticMemberVarList = new std::vector<const CMetaDataVariable*>;
		}
		return m_pStaticMemberVarList;
	}
private:
	bool FindBaseType(const CMetaDataType *pType, std::vector<SMDCustomTypeOffsetDescript*> &BaseList) const;
	bool FindInterface(const CMetaDataType *pIntf, std::vector<SMDCustomTypeOffsetDescript*> &IntfList) const;
	void *DoCreateObject(CParamVector *pParamTypes, va_list pParamList) const;
private:
	bool												m_EnableBaseType;			//是否允许有基类
	bool												m_Sealed;					//是否允许被继承
	bool												m_EnableStaticMemberFunc;	//是否允许有静态成员函数
	bool												m_EnableStaticMemberVar;	//是否允许有静态成员变量
	std::vector<SMDBaseTypeOfCustomType>				*m_pBaseTypeList;			//基类
	std::vector<SMDInterfaceOfCustomType>				*m_pInterfaceList;			//接口
	std::vector<const CMetaDataFunction*>				*m_pConstructorList;		//构造函数
	const CMetaDataFunction								*m_pDestructor;				//析构函数
	std::vector<const CMetaDataFunction*>				*m_pMemberFuncList;			//成员函数
	std::vector<const CMetaDataCustomTypeMemberVar*>	*m_pMemberVarList;			//成员变量
	std::vector<const CMetaDataCustomTypeProperty*>		*m_pPropertyList;			//成员属性
	std::vector<const CMetaDataFunction*>				*m_pStaticMemberFuncList;	//静态成员函数
	std::vector<const CMetaDataVariable*>				*m_pStaticMemberVarList;	//静态成员变量
private:
	TpfunAsTypeEx										m_AsTypeExFunPtr;
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