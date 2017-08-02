#include "stdafx.h"
#include "..\include\MetaDataCustomTypeMemberVar.h"


CMetaDataCustomTypeMemberVar::CMetaDataCustomTypeMemberVar(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, unsigned int Offset)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_Offset(Offset)
{
}


CMetaDataCustomTypeMemberVar::~CMetaDataCustomTypeMemberVar(void)
{
}
