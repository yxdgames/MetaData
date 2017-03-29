#include "stdafx.h"
#include "..\include\MetaDataVarBase.h"


CMetaDataVarBase::CMetaDataVarBase(char *pName, CMetaData *pParent, CMetaDataType *pType, int PtrLevel)
	:CMetaData(pName, pParent, false), m_pMDType(pType), m_PtrLevel(PtrLevel)
{
}


CMetaDataVarBase::~CMetaDataVarBase(void)
{
}
