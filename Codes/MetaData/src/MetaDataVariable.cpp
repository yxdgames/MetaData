#include "stdafx.h"
#include "../include/MetaDataVariable.h"


CMetaDataVariable::CMetaDataVariable(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, void *pVar)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_pVar(pVar)
{
}

CMetaDataVariable::~CMetaDataVariable(void)
{
}

void CMetaDataVariable::Output(void *pOutputAddr) const
{
	if (!pOutputAddr || !m_pVar || !GetMDType())
	{
		return;
	}

	memcpy(pOutputAddr, m_pVar, this->GetSize());
}