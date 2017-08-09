#pragma once

#include "MetaDataCustomType.h"

class CLASS_DESCRIPT CMetaDataClassType : public CMetaDataCustomType
{
public:
	CMetaDataClassType(const char *pName, const CMetaData *pParent, size_t size);
	virtual ~CMetaDataClassType(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const		{ return D_META_DATA_TYPE_ID_CLASS_TYPE; }
};

