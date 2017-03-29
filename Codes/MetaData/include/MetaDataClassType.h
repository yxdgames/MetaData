#pragma once

#include "MetaDataCustomType.h"

class CMetaDataClassType : public CMetaDataCustomType
{
public:
	CMetaDataClassType(char *pName, CMetaData *pParent, unsigned int size);
	virtual ~CMetaDataClassType(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const		{ return D_META_DATA_TYPE_ID_CLASS_TYPE; }
};

