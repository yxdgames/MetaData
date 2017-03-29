#pragma once

#include "MetaDataCustomType.h"

class CMetaDataInterface : public CMetaDataCustomType
{
public:
	CMetaDataInterface(char *pName, CMetaData *pParent, unsigned int size);
	virtual ~CMetaDataInterface(void);
public:
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_INTERFACE; }
};

