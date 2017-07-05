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

typedef void *(*TpfunAsTypeEx)(void *pObj, CMetaDataType *pType);

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
	virtual bool IsTypeOf(CMetaDataType *pType);
	virtual void *AsType(void *pObj, CMetaDataType *pType);
	virtual bool QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf);
	virtual void *NewObject(void);
	virtual void DeleteObject(void *pObj);
	
	template<typename T>
	T *CreateObject(CParamVector *pParamTypes, ...);
	template<typename T>
	T *CreateObject(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const						{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE; }
	unsigned int GetBaseTypeCount(void)								{ return (m_pBaseTypeList ? m_pBaseTypeList->size() : 0); }
	CMetaDataCustomType *GetBaseType(unsigned int index)			{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).CustomType : NULL); }
	unsigned int GetBaseTypeOffset(unsigned int index)				{ return (m_pBaseTypeList ? m_pBaseTypeList->at(index).Offset : 0); }
	unsigned int GetInterfaceCount(void)							{ return (m_pInterfaceList ? m_pInterfaceList->size() : 0); }
	CMetaDataInterface *GetInterface(unsigned int index)			{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Intf : NULL); }
	unsigned int GetInterfaceOffset(unsigned int index)				{ return (m_pInterfaceList ? m_pInterfaceList->at(index).Offset : 0); }
	unsigned int GetConstructorCount(void)							{ return (m_pConstructorList ? m_pConstructorList->size() : 0); }
	CMetaDataFunction *GetConstructor(unsigned int index)			{ return (m_pConstructorList ? m_pConstructorList->at(index) : NULL); }
	unsigned int GetMemberFuncCount(void)							{ return (m_pMemberFuncList ? m_pMemberFuncList->size() : 0); }
	CMetaDataFunction *GetMemberFunc(unsigned int index)			{ return (m_pMemberFuncList ? m_pMemberFuncList->at(index) : NULL); }
	unsigned int GetMemberVarCount(void)							{ return (m_pMemberVarList ? m_pMemberVarList->size() : 0); }
	CMetaDataCustomTypeMemberVar *GetMemberVar(unsigned int index)	{ return (m_pMemberVarList ? m_pMemberVarList->at(index) : NULL); }
	unsigned int GetStaticMemberFuncCount(void)						{ return (m_pStaticMemberFuncList ? m_pStaticMemberFuncList->size() : 0); }
	CMetaDataFunction *GetStaticMemberFunc(unsigned int index)		{ return (m_pStaticMemberFuncList ? m_pStaticMemberFuncList->at(index) : NULL); }
	unsigned int GetStaticMemberVarCount(void)						{ return (m_pStaticMemberVarList ? m_pStaticMemberVarList->size() : 0); }
	CMetaDataVariable *GetStaticMemberVar(unsigned int index)		{ return (m_pStaticMemberVarList ? m_pStaticMemberVarList->at(index) : NULL); }
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
	bool											m_EnableBaseType;			//是否允许有基类
	bool											m_Sealed;					//是否允许被继承
	bool											m_EnableStaticMemberFunc;	//是否允许有静态成员函数
	bool											m_EnableStaticMemberVar;	//是否允许有静态成员变量
	std::vector<SMetaDataCustomTypeBaseType>		*m_pBaseTypeList;			//基类
	std::vector<SMetaDataCustomTypeInterface>		*m_pInterfaceList;			//接口
	std::vector<CMetaDataFunction*>					*m_pConstructorList;		//构造函数
	CMetaDataFunction								*m_pDestructor;				//析构函数
	std::vector<CMetaDataFunction*>					*m_pMemberFuncList;			//成员函数
	std::vector<CMetaDataCustomTypeMemberVar*>		*m_pMemberVarList;			//成员变量
	std::vector<CMetaDataFunction*>					*m_pStaticMemberFuncList;	//静态成员函数
	std::vector<CMetaDataVariable*>					*m_pStaticMemberVarList;	//静态成员变量
private:
	TpfunAsTypeEx									m_AsTypeExFunPtr;
};

#include "ExceptionMetaData.h"
#include "..\..\include\ExceptionID.h"
#include <stdarg.h>

//Template
template<typename T>
T *CMetaDataCustomType::CreateObject(CParamVector *pParamTypes, ...)
{
	void *pReturn(NULL);

	if (!m_pConstructorList) return reinterpret_cast<T*>(pReturn);
	
	std::vector<CMetaDataFunction*>::iterator itr;
	va_list pList;
	

	for (itr = m_pConstructorList->begin(); itr != m_pConstructorList->end(); ++itr)
	{
		if ((*itr)->FuncParamsCheck(pParamTypes))
		{
			va_start(pList, pParamTypes);
			try
			{
				if (!(*itr)->ReturnIsVoid())
				{
					if (!(*itr)->CallFuction(pParamTypes, pList, &pReturn))
					{
						throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "构造函数调用失败！");
					}
				}
				else
				{
					throw new ExceptionMetaData(D_E_ID_ERR_MD_CALL_META_DATA_OF_FUNC, "错误：构造函数无返回值！");
				}
			}
			catch(...)
			{
				va_end(pList);
				throw;
			}
			va_end(pList);
		}
	}
	return reinterpret_cast<T*>(pReturn);
}

template<typename T>
T *CMetaDataCustomType::CreateObject(void)
{
	void *pReturn(NULL);

	if (!m_pConstructorList) return reinterpret_cast<T*>(pReturn);
	
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
	return reinterpret_cast<T*>(pReturn);
}