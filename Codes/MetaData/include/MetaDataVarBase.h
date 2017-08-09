#pragma once

#include "MetaData.h"
#include "MetaDataType.h"

class CLASS_DESCRIPT CMetaDataVarBase : public CMetaData
{
public:
	CMetaDataVarBase(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel);
	virtual ~CMetaDataVarBase(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_VAR_BASE; }
	size_t GetSize(void) const					{ return m_pMDType ? m_pMDType->GetSize() : 0; }
	const CMetaDataType *GetMDType(void) const	{ return m_pMDType; }
	int GetPtrLevel(void) const					{ return m_PtrLevel; }
private:
	const CMetaDataType		*m_pMDType;
	int						m_PtrLevel;
};