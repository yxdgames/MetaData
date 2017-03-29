#include "stdafx.h"
#include "..\include\MetaDataType.h"


CMetaDataType::CMetaDataType(char *pName, CMetaData *pParent, bool bChildren, unsigned int size)
	:CMetaData(pName, pParent, bChildren), m_Size(size)
{
}


CMetaDataType::~CMetaDataType(void)
{
}
