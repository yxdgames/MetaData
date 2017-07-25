#pragma once

#include "MetaData.h"
#include "MetaDataVarBase.h"

#define D_PARAM_VECTOR_ADD_ELE(param_vector, type_name, ptr_level) \
	{ \
		(param_vector).push_back(new CMetaDataVarBase(nullptr, nullptr, TypeTraits<type_name>::GetMetaDataType(), (ptr_level))); \
	}

class CLASS_DESCRIPT CParamVector
{
public:
	typedef std::vector<CMetaDataVarBase*>::iterator iterator;
public:
	CParamVector(void) : m_pMDVarBaseVector(new std::vector<CMetaDataVarBase*>) {}
	~CParamVector(void)
	{
		std::vector<CMetaDataVarBase*>::iterator itr;
		for (itr = this->m_pMDVarBaseVector->begin(); itr != this->m_pMDVarBaseVector->end(); ++itr)
		{
			delete (*itr);
		}
		delete m_pMDVarBaseVector;
	}
public:
	size_t size(void) { return m_pMDVarBaseVector->size(); }
	CMetaDataVarBase* at(size_t index) { return m_pMDVarBaseVector->at(index); }
	void push_back(CMetaDataVarBase *value) { m_pMDVarBaseVector->push_back(value); }
	std::vector<CMetaDataVarBase*>::iterator begin(void) { return m_pMDVarBaseVector->begin(); }
	std::vector<CMetaDataVarBase*>::iterator end(void) { return m_pMDVarBaseVector->end(); }
private:
	std::vector<CMetaDataVarBase*> *m_pMDVarBaseVector;
};

struct STRUCT_DESCRIPT SMetaDataCalledFunctionDataPacket
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
	bool CallFunction(int param_count, void **pParam, void *pReturn);
	bool CallFunction(int param_count, va_list pParamList);
	bool __cdecl CallFunction(int param_count, ...);
	bool CallFunction(CParamVector *pParamTypes, va_list pParamList, void *pReturn);
	bool __cdecl CallFunction(CParamVector *pParamTypes, ...);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_FUNCTION; }
	bool ReturnIsVoid(void) const				{ return m_pReturnInfo == nullptr; }
	CMetaDataVarBase *GetReturnInfo(void)		{ return m_pReturnInfo; }
	int GetParamCount(void) const				{ return m_pParamTable ? m_pParamTable->size() : 0; }
	CMetaDataVarBase *GetParam(int index)		{ return m_pParamTable ? m_pParamTable->at(index) : nullptr; }
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

