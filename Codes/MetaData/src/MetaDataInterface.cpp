#include "stdafx.h"
#include "..\include\MetaDataInterface.h"


CMetaDataInterface::CMetaDataInterface(const char *pName, const CMetaData *pParent, size_t size)
	:CMetaDataCustomType(pName, pParent, size, false, false, true, true)
{
}


CMetaDataInterface::~CMetaDataInterface(void)
{
}
