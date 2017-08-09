#pragma once

#include "MetaDataType.h"

class CLASS_DESCRIPT CMetaDataInnerType : public CMetaDataType
{
public:
	CMetaDataInnerType(const char *pName, const CMetaData *pParent, size_t size);
	virtual ~CMetaDataInnerType(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_INNER_TYPE; }
};

