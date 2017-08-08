#pragma once

#include "MetaDataCustomType.h"

class CLASS_DESCRIPT CMetaDataInterface : public CMetaDataCustomType
{
public:
	CMetaDataInterface(const char *pName, const CMetaData *pParent, TDUIntPtr size);
	virtual ~CMetaDataInterface(void);
public:
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_INTERFACE; }
};

