#include "stdafx.h"
#include "..\include\MetaDataCustomTypeProperty.h"


CMetaDataCustomTypeProperty::CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, TDUIntPtr Offset)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_Offset(Offset), m_IsOffset(true)
{
}

CMetaDataCustomTypeProperty::CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, CPropertyBase *pProperty)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_Offset(reinterpret_cast<TDUIntPtr>(pProperty)), m_IsOffset(false)
{
}

CMetaDataCustomTypeProperty::~CMetaDataCustomTypeProperty(void)
{
}
