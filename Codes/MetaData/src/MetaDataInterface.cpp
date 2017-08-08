#include "stdafx.h"
#include "..\include\MetaDataInterface.h"


CMetaDataInterface::CMetaDataInterface(const char *pName, const CMetaData *pParent, TDUIntPtr size)
	:CMetaDataCustomType(pName, pParent, size, true, false, true, true)
{
}


CMetaDataInterface::~CMetaDataInterface(void)
{
}
