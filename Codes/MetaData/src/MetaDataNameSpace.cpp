#include "stdafx.h"
#include "..\include\MetaDataNameSpace.h"


CMetaDataNameSpace::CMetaDataNameSpace(const char *pName, const CMetaData *pParent)
	:CMetaData(pName, pParent, true)
{
}


CMetaDataNameSpace::~CMetaDataNameSpace(void)
{
}
