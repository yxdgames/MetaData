#pragma once

#include "MetaData.h"

class CMetaDataGlobalSpace : public CMetaData
{
public:
	CMetaDataGlobalSpace(void);
	virtual ~CMetaDataGlobalSpace(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_GLOBAL_SPACE; }
};

