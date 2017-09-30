#include "stdafx.h"
#include "..\include\MetaDataCustomTypeProperty.h"


CMetaDataCustomTypeProperty::CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, TDUIntPtr Offset)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_PropertyLocationIsOffset(true)
{
	m_PropertyLocation.Offset = Offset;
}

CMetaDataCustomTypeProperty::CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, CPropertyBase *pProperty)
	:CMetaDataVarBase(pName, pParent, pType, PtrLevel), m_PropertyLocationIsOffset(false)
{
	m_PropertyLocation.pProperty = pProperty;
}

CMetaDataCustomTypeProperty::~CMetaDataCustomTypeProperty(void)
{
}
