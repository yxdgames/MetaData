#pragma once

#include "MetaDataVarBase.h"
#include "TProperty.h"

class CLASS_DESCRIPT CMetaDataCustomTypeProperty : public CMetaDataVarBase
{
public:
	CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, TDUIntPtr Offset);
	CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, CPropertyBase *pProperty);
	virtual ~CMetaDataCustomTypeProperty(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE_PROPERTY; }
	TDUIntPtr GetOffset(void) const				{ return m_Offset; }
	bool IsOffset(void) const					{ return m_IsOffset; }
private:
	TDUIntPtr	m_Offset;
	bool		m_IsOffset;
};

