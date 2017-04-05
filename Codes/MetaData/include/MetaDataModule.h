#pragma once

#include "MetaData.h"

class CMetaDataModule : public CMetaData
{
public:
	CMetaDataModule(char *pName, CMetaData *pParent);
	virtual ~CMetaDataModule(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_MODULE; }
};

