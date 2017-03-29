#pragma once

#include "MetaDataType.h"

class CMetaDataInnerType : public CMetaDataType
{
public:
	CMetaDataInnerType(char *pName, CMetaData *pParent, unsigned int size);
	virtual ~CMetaDataInnerType(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_INNER_TYPE; }
};

