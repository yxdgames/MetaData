#include "stdafx.h"
#include "..\include\MetaDataInnerType.h"


CMetaDataInnerType::CMetaDataInnerType(const char *pName, const CMetaData *pParent, unsigned int size)
	:CMetaDataType(pName, pParent, false, size)
{
}


CMetaDataInnerType::~CMetaDataInnerType(void)
{
}
