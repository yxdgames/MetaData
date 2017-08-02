#include "stdafx.h"
#include "..\include\MetaDataVarBase.h"


CMetaDataVarBase::CMetaDataVarBase(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel)
	:CMetaData(pName, pParent, false), m_pMDType(pType), m_PtrLevel(PtrLevel)
{
}


CMetaDataVarBase::~CMetaDataVarBase(void)
{
}
