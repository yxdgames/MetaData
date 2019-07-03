#pragma once

#include "MetaData.h"
#include "MetaDataVarBase.h"

#define D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, type_name, ptr_level) \
	{ \
		(param_vector).push_back(new CMetaDataVarBase(nullptr, nullptr, TypeTraits<type_name>::GetMetaDataType(), (ptr_level))); \
	}

class CLASS_DESCRIPT CFuncParamMDVector
{
public:
	typedef std::vector<const CMetaDataVarBase*>::iterator iterator;
public:
	CFuncParamMDVector(void);
	~CFuncParamMDVector(void);
public:
	void push_back(const CMetaDataVarBase *value);
	void clear(void);
	size_t size(void);
	const CMetaDataVarBase* at(size_t index);
	std::vector<const CMetaDataVarBase*>::iterator begin(void);
	std::vector<const CMetaDataVarBase*>::iterator end(void);
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

	bool FuncParamsCheck(CFuncParamMDVector *pParamMDVector) const;
	bool CallFunction(int param_count, void **pParam, void *pReturn) const;
	bool CallFunction(const size_t param_count, va_list pParamList, void *pReturn) const;
	bool __cdecl CallFunction(const size_t param_count, ...) const;
	bool CallFunction(CFuncParamMDVector *pParamMDVector, va_list pParamList, void *pReturn) const;
	bool __cdecl CallFunction(CFuncParamMDVector *pParamMDVector, ...) const;
public:
	//attribute
	virtual unsigned char GetTypeID(void) const			{ return D_META_DATA_TYPE_ID_FUNCTION; }
	bool ReturnIsVoid(void) const						{ return m_pReturnInfo == nullptr; }
	const CMetaDataVarBase *GetReturnInfo(void) const	{ return m_pReturnInfo; }
	size_t GetParamCount(void) const					{ return m_pParamTable ? m_pParamTable->size() : 0; }
	const CMetaDataVarBase *GetParam(int index) const	{ return m_pParamTable ? m_pParamTable->at(index) : nullptr; }
private:
	bool CallFunction(const size_t param_count, CFuncParamMDVector *pParamMDVector, va_list pParamList, void *pReturn) const;
private:
	CFuncParamMDVector *GetParamTable(void)
	{
		if (!m_pParamTable) m_pParamTable = new CFuncParamMDVector;
		return m_pParamTable;
	}
private:
	void					*m_pFunction;
	CFuncParamMDVector		*m_pParamTable;
	const CMetaDataVarBase	*m_pReturnInfo;
};

