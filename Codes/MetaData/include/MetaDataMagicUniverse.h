#pragma once

#include "MetaData.h"

class CMetaDataMagicUniverse : public CMetaData
{
public:
	CMetaDataMagicUniverse(void);
	virtual ~CMetaDataMagicUniverse(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_MAGIC_UNIVERSE; }
};

