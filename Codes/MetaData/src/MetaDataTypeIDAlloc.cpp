#include "stdafx.h"
#include "..\include\MetaDataTypeIDAlloc.h"

#include "..\include\MetaDataObjects.h"
#include "..\include\MetaDataSupport.h"

CMetaDataTypeIDAlloc::CMetaDataTypeIDAlloc(void)
	:m_NextID(1)
{
	Init(&META_DATA_GLOBALSPACE());
}


CMetaDataTypeIDAlloc::~CMetaDataTypeIDAlloc(void)
{
}

unsigned int CMetaDataTypeIDAlloc::GetTypeID(CMetaDataType *pType)
{
	for (size_t i = 0; i < m_TypeID.size(); ++i)
	{
		if (m_TypeID[i].pType == pType)
			return m_TypeID[i].ID;
	}
	return D_META_DATA_TYPE_ID_ALLOC_TYPE_ID_NONE;
}

void CMetaDataTypeIDAlloc::Init(CMetaData *pMD)
{
	STypeID Item;
	if (pMD && (pMD->GetTypeID() == D_META_DATA_TYPE_ID_INNER_TYPE || pMD->GetTypeID() == D_META_DATA_TYPE_ID_CLASS_TYPE))
	{
		Item.ID = m_NextID++;
		Item.pType = reinterpret_cast<CMetaDataType*>(pMD);

		m_TypeID.push_back(Item);
	}

	for (unsigned int i = 0; i < pMD->GetChildrenCount(); ++i)
	{
		Init(const_cast<CMetaData*>(pMD->GetChild(i)));
	}
}