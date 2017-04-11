#pragma once

#include "MetaData.h"
#include "MetaDataVarBase.h"

#define D_PARAM_VECTOR_ADD_ELE(param_vector, type_name, ptr_level) \
	{ \
		(param_vector).push_back(new CMetaDataVarBase(NULL, NULL, TypeTraits<type_name>::GetMetaDataType(), (ptr_level))); \
	}

class CParamVector : public std::vector<CMetaDataVarBase*>
{
public:
	CParamVector(void)	{}
	~CParamVector(void)
	{
		vector<CMetaDataVarBase*>::iterator itr;
		for (itr = this->begin(); itr != this->end(); ++itr)
		{
			delete (*itr);
		}
	}
};

struct SMetaDataCalledFunctionDataPacket
{
	int ParamCount;
	void **pParam;
	void *pReturn;
};

typedef bool (*TpMDCalledFunction)(SMetaDataCalledFunctionDataPacket &DataPacket);

class CLASS_DESCRIPT CMetaDataFunction : public CMetaData
{
public:
	CMetaDataFunction(char *pName, CMetaData *pParent, void *pFunction);
	virtual ~CMetaDataFunction(void);
public:
	//method
	void AddParamInfo(CMetaDataVarBase *pParam);
	void SetReturnInfo(CMetaDataVarBase *pRet);

	bool FuncParamsCheck(CParamVector *pParamTypes);
	bool CallFuction(int param_count, void **pParam, void *pReturn);
	bool __cdecl CallFuction(int param_count, ...);
	bool CallFuction(CParamVector *pParamTypes, va_list pParamList, void *pReturn);
	bool __cdecl CallFuction(CParamVector *pParamTypes, ...);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_FUNCTION; }
	bool ReturnIsVoid(void) const				{ return m_pReturnInfo == NULL; }
	CMetaDataVarBase *GetReturnInfo(void)		{ return m_pReturnInfo; }
	int GetParamCount(void) const				{ return m_pParamTable ? m_pParamTable->size() : 0; }
	CMetaDataVarBase *GetParam(int index)		{ return m_pParamTable ? m_pParamTable->at(index) : NULL; }
private:
	CParamVector *GetParamTable(void)
	{
		if (!m_pParamTable) m_pParamTable = new CParamVector;
		return m_pParamTable;
	}
private:
	void				*m_pFunction;
	CParamVector		*m_pParamTable;
	CMetaDataVarBase	*m_pReturnInfo;
};

