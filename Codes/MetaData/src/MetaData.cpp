#include "stdafx.h"
#include "../include/MetaData.h"
#include "../include/ExceptionMetaData.h"
#include "../include/ExceptionIDMetaData.h"

static const char *gMetaDataTypeCaption[] = {
	"None",
	"MetaData",
	"GlobalSpace",
	"NameSpace",
	"Type",
	"InnerType",
	"CustomType",
	"CustomTypeMemberVar",
	"CustomTypeProperty",
	"Class",
	"Interface",
	"Var Base",
	"Variable",
	"Function",
};

CMetaData::CMetaData(const char *pName, const CMetaData *pParent, bool bChildren)
	:m_pName(pName), m_pParent(pParent), m_pChildren(bChildren ? (new std::vector<const CMetaData*>) : nullptr)
{
	InsertSelfToParent();
}


CMetaData::~CMetaData(void)
{
	RemoveSelfFromParent();
	if (m_pChildren)
	{
		delete m_pChildren;
		m_pChildren = nullptr;
	}
}

const CMetaData * CMetaData::FindChildMetaData(const TDGUID & guid) const
{
	if (!m_pChildren) return nullptr;
	const CMetaData *pMD;
	std::vector<const CMetaData*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if ((*itr)->Compare(guid))
			return (*itr);
		pMD = (*itr)->FindChildMetaData(guid);
		if (pMD) return pMD;
	}
	return nullptr;
}

const CMetaData *CMetaData::FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName) const
{
	if (!m_pChildren) return nullptr;
	TDCharArray FullName(256);
	const CMetaData *pMD;
	std::vector<const CMetaData*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if ((*itr)->GetFullName(FullName.array(), 256))
		{
			if ((*itr)->GetTypeID() == MetaDataTypeID && (strcmp(FullName.array(), pFullName) == 0
				|| strcmp(FullName.array() + 2, pFullName) == 0)) //+2是为了跳过"::"两个字符
				return (*itr);
		}
		pMD = (*itr)->FindChildMetaData(MetaDataTypeID, pFullName);
		if (pMD) return pMD;
	}
	return nullptr;
}

bool CMetaData::FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName, std::vector<const CMetaData*> &Children) const
{
	return FindChildMetaData(MetaDataTypeID, pFullName, Children, true);
}

bool CMetaData::GetFullName(char *pFullNameBuffer, size_t BufferSize) const
{
	if (pFullNameBuffer == nullptr)
	{
		return false;
	}

	size_t Char_BufferSize(BufferSize - 1 * sizeof(char));
	char *pReBuffer((char*)((size_t)pFullNameBuffer + Char_BufferSize));

	const CMetaData *pParent(m_pParent);
	const char *pName;
	size_t total_size;
	size_t cur_len;

	pName = this->GetName();
	
	if (!pName) throw new ExceptionMetaData(D_E_ID_MD_ERROR, "元数据未命名！");

	cur_len = strlen(pName);
	total_size = cur_len * sizeof(char);
	if (total_size > Char_BufferSize)
	{
		return false;
	}
	memcpy((void*)((size_t)pReBuffer - total_size), pName, cur_len * sizeof(char));

	while (pParent)
	{
		total_size += 2 * sizeof(char);
		if (total_size > Char_BufferSize)
		{
			return false;
		}
		memcpy((void*)((pReBuffer) - total_size), "::", 2 * sizeof(char));

		pName = pParent->GetName();
		cur_len = strlen(pName);
		total_size += cur_len * sizeof(char);
		if (total_size > Char_BufferSize)
		{
			return false;
		}
		memcpy((void*)((pReBuffer) - total_size), pName, cur_len * sizeof(char));
		pParent = pParent->m_pParent;
	}
	memcpy(pFullNameBuffer, (void*)((pReBuffer) - total_size), total_size);
	pFullNameBuffer[total_size] = '\0';
	return true;
}

const char *CMetaData::GetTypeCaption(void) const
{
	return gMetaDataTypeCaption[this->GetTypeID()];
}

void CMetaData::InsertSelfToParent(void)
{
	if (m_pParent && m_pParent->m_pChildren)
	{
		m_pParent->m_pChildren->push_back(this);
	}
	else m_pParent = nullptr;
}

void CMetaData::RemoveSelfFromParent(void)
{
	if (m_pParent && m_pParent->m_pChildren)
	{
		std::vector<const CMetaData*>::iterator itr;
		for (itr = m_pParent->m_pChildren->begin(); itr != m_pParent->m_pChildren->end(); ++itr)
		{
			if ((*itr) == this)
			{
				m_pParent->m_pChildren->erase(itr);
				break;
			}
		}
	}
}

const bool CMetaData::FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName, std::vector<const CMetaData*> &Children, bool bClear) const
{
	if (bClear) Children.clear();
	if (!m_pChildren) return false;
	TDCharArray FullName(256);
	std::vector<const CMetaData*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if ((*itr)->GetFullName(FullName.array(), 256))
		{
			if ((*itr)->GetTypeID() == MetaDataTypeID && (strcmp(FullName.array(), pFullName) == 0
				|| strcmp(FullName.array() + 2, pFullName) == 0)) //+2是为了跳过"::"两个字符
				Children.push_back(*itr);
		}
		(void)(*itr)->FindChildMetaData(MetaDataTypeID, pFullName, Children, false);
	}
	return true;
}

const CMetaData *AssertMetaData(const CMetaData *pMetaData, unsigned char TypeID)
{
	if (pMetaData && pMetaData->GetTypeID() == TypeID)
		return pMetaData;
	else throw ExceptionMetaData(D_E_ID_MD_ERROR, "元数据的TypeID与指定的TypeID不符！");
}