#include "stdafx.h"
#include "..\include\MetaDataNameSpace.h"


CMetaDataNameSpace::CMetaDataNameSpace(char *pName, CMetaData *pParent)
	:CMetaData(pName, pParent, true)
{
}


CMetaDataNameSpace::~CMetaDataNameSpace(void)
{
}
