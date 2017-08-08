#include "stdafx.h"
#include "..\include\MetaDataInnerType.h"


CMetaDataInnerType::CMetaDataInnerType(const char *pName, const CMetaData *pParent, TDUIntPtr size)
	:CMetaDataType(pName, pParent, false, size)
{
}


CMetaDataInnerType::~CMetaDataInnerType(void)
{
}
