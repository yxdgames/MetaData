#include "stdafx.h"
#include "..\include\MetaDataClassType.h"


CMetaDataClassType::CMetaDataClassType(const char *pName, const CMetaData *pParent, TDUIntPtr size)
	:CMetaDataCustomType(pName, pParent, size, true, false, true, true)
{
}


CMetaDataClassType::~CMetaDataClassType(void)
{
}
