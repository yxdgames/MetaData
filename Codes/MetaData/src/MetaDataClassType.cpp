#include "stdafx.h"
#include "..\include\MetaDataClassType.h"


CMetaDataClassType::CMetaDataClassType(char *pName, CMetaData *pParent, unsigned int size)
	:CMetaDataCustomType(pName, pParent, size, true, false, true, true)
{
}


CMetaDataClassType::~CMetaDataClassType(void)
{
}
