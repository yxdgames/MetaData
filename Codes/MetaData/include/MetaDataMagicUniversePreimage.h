#pragma once

#include "MetaDataMagicUniverse.h"

class CMetaDataMagicUniversePreimage : public CMetaDataMagicUniverse
{
public:
	CMetaDataMagicUniversePreimage(void);
	virtual ~CMetaDataMagicUniversePreimage(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_MAGIC_UNIVERSE_PREIMAGE; }
};

