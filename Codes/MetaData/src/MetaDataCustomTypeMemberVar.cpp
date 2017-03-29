#include "stdafx.h"
#include "..\include\MetaDataCustomTypeMemberVar.h"


CMetaDataCustomTypeMemberVar::CMetaDataCustomTypeMemberVar(char *pName, CMetaData *pParent, CMetaDataType *pType, int PtrLevel, unsigned int Offset)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_Offset(Offset)
{
}


CMetaDataCustomTypeMemberVar::~CMetaDataCustomTypeMemberVar(void)
{
}
