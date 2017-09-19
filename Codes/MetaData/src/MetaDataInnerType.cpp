#include "stdafx.h"
#include "..\include\MetaDataInnerType.h"


CMetaDataInnerType::CMetaDataInnerType(const char *pName, const CMetaData *pParent, size_t size,
	TpfunNewObject pfunNewObject, TpfunDeleteObject pfunDeleteObject)
	:CMetaDataType(pName, pParent, false, size),
	m_pfunNewObject(pfunNewObject), m_pfunDeleteObject(pfunDeleteObject)
{
}

CMetaDataInnerType::~CMetaDataInnerType(void)
{
}
