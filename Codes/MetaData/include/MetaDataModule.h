#pragma once

#include "MetaDataNameSpace.h"

class CMetaDataModule : public CMetaDataNameSpace
{
public:
	CMetaDataModule(char *pName);
	virtual ~CMetaDataModule(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_MODULE; }
};

