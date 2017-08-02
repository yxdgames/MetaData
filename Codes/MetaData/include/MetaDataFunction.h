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
	typedef std::vector<const CMetaDataVarBase*>::iterator iterator;
public:
	CParamVector(void) : m_pMDVarBaseVector(new std::vector<const CMetaDataVarBase*>) {}
	~CParamVector(void)
	{
		std::vector<const CMetaDataVarBase*>::iterator itr;
		for (itr = this->m_pMDVarBaseVector->begin(); itr != this->m_pMDVarBaseVector->end(); ++itr)
		{
			delete (*itr);
		}
		delete m_pMDVarBaseVector;
	}
public:
	size_t size(void)											{ return m_pMDVarBaseVector->size(); }
	const CMetaDataVarBase* at(size_t index)					{ return m_pMDVarBaseVector->at(index); }
	void push_back(const CMetaDataVarBase *value)				{ m_pMDVarBaseVector->push_back(value); }
	std::vector<const CMetaDataVarBase*>::iterator begin(void)	{ return m_pMDVarBaseVector->begin(); }
	std::vector<const CMetaDataVarBase*>::iterator end(void)	{ return m_pMDVarBaseVector->end(); }
private:
	std::vector<const CMetaDataVarBase*> *m_pMDVarBaseVector;
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
	CMetaDataFunction(const char *pName, const CMetaData *pParent, void *pFunction);
	virtual ~CMetaDataFunction(void);
public:
	//method
	void AddParamInfo(const CMetaDataVarBase *pParam);
	void SetReturnInfo(const CMetaDataVarBase *pRet);

	bool FuncParamsCheck(CParamVector *pParamTypes) const;
	bool CallFunction(int param_count, void **pParam, void *pReturn) const;
	bool CallFunction(int param_count, va_list pParamList) const;
	bool __cdecl CallFunction(int param_count, ...) const;
	bool CallFunction(CParamVector *pParamTypes, va_list pParamList, void *pReturn) const;
	bool __cdecl CallFunction(CParamVector *pParamTypes, ...) const;
public:
	//attribute
	virtual unsigned char GetTypeID(void) const			{ return D_META_DATA_TYPE_ID_FUNCTION; }
	bool ReturnIsVoid(void) const						{ return m_pReturnInfo == nullptr; }
	const CMetaDataVarBase *GetReturnInfo(void) const	{ return m_pReturnInfo; }
	int GetParamCount(void) const						{ return m_pParamTable ? m_pParamTable->size() : 0; }
	const CMetaDataVarBase *GetParam(int index) const	{ return m_pParamTable ? m_pParamTable->at(index) : nullptr; }
private:
	CParamVector *GetParamTable(void)
	{
		if (!m_pParamTable) m_pParamTable = new CParamVector;
		return m_pParamTable;
	}
private:
	void					*m_pFunction;
	CParamVector			*m_pParamTable;
	const CMetaDataVarBase	*m_pReturnInfo;
};

