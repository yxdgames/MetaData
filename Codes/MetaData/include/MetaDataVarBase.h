#pragma once

#include "MetaData.h"
#include "MetaDataType.h"

class CLASS_DESCRIPT CMetaDataVarBase : public CMetaData
{
public:
	CMetaDataVarBase(char *pName, CMetaData *pParent, CMetaDataType *pType, int PtrLevel);
	virtual ~CMetaDataVarBase(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_VAR_BASE; }
	unsigned int GetSize(void) const			{ return m_pMDType ? m_pMDType->GetSize() : 0; }
	CMetaDataType *GetMDType(void)				{ return m_pMDType; }
	int GetPtrLevel(void)						{ return m_PtrLevel; }
private:
	CMetaDataType	*m_pMDType;
	int				m_PtrLevel;
};