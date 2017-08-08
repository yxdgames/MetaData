#include "stdafx.h"
#include "..\include\MetaDataType.h"


CMetaDataType::CMetaDataType(const char *pName, const CMetaData *pParent, bool bChildren, TDUIntPtr size)
	:CMetaData(pName, pParent, bChildren), m_Size(size)
{
}


CMetaDataType::~CMetaDataType(void)
{
}
