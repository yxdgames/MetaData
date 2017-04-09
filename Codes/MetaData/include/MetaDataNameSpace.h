#pragma once

#include "MetaData.h"

class CLASS_DESCRIPT CMetaDataNameSpace : public CMetaData
{
public:
	CMetaDataNameSpace(char *pName, CMetaData *pParent);
	virtual ~CMetaDataNameSpace(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_NAME_SPACE; }
};

