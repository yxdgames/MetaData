#include "stdafx.h"
#include "..\include\MetaDataInnerType.h"


CMetaDataInnerType::CMetaDataInnerType(char *pName, CMetaData *pParent, unsigned int size)
	:CMetaDataType(pName, pParent, false, size)
{
}


CMetaDataInnerType::~CMetaDataInnerType(void)
{
}
