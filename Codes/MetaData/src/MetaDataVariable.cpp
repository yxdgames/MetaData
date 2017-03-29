#include "stdafx.h"
#include "..\include\MetaDataVariable.h"
#include "..\include\IClone.h"


CMetaDataVariable::CMetaDataVariable(char *pName, CMetaData *pParent, CMetaDataType *pType, int PtrLevel, void *pVar)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_pVar(pVar)
{
}


CMetaDataVariable::~CMetaDataVariable(void)
{
}

void CMetaDataVariable::Output(void *pOutputAddr)
{
	if (!pOutputAddr || !m_pVar || !GetMDType())
	{
		return;
	}
	IInterface *Intf;
	IClone *IntfClone;
	if (GetMDType()->QueryInterface(pOutputAddr, "IClone", &Intf))
	{
		IntfClone = reinterpret_cast<IClone*>(Intf);
		IntfClone->Clone(m_pVar);
	}
	else memcpy(pOutputAddr, m_pVar, this->GetSize());
}