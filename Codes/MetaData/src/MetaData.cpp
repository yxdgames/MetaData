#include "stdafx.h"
#include "..\include\MetaData.h"

#include "..\include\ExceptionMetaData.h"
#include "..\..\include\ExceptionID.h"

static const char *gMetaDataTypeCaption[] = {
	"None",
	"MetaData",
	"NameSpace",
	"Module",
	"Type",
	"InnerType",
	"CustomType",
	"CustomTypeMemberVar",
	"Class",
	"Interface",
	"Var Base",
	"Variable",
	"Function",
};

CMetaData::CMetaData(char *pName, CMetaData *pParent, bool bChildren)
	:m_pName(pName), m_pParent(pParent), m_pChildren(bChildren ? (new std::vector<CMetaData*>) : NULL)
{
	if (m_pParent && m_pParent->m_pChildren)
	{
		m_pParent->m_pChildren->push_back(this);
	}
	else m_pParent = NULL;
}


CMetaData::~CMetaData(void)
{
	if (m_pChildren)
	{
		delete m_pChildren;
		m_pChildren = NULL;
	}
}

const CMetaData *CMetaData::FindChildMetaData(unsigned char MetaDataTypeID, char *pFullName) const
{
	if (!m_pChildren) return NULL;
	static char FullNameBuffer[256];
	const CMetaData *pMD;
	std::vector<CMetaData*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if ((*itr)->GetFullName(FullNameBuffer, 256))
		{
			if ((*itr)->GetTypeID() == MetaDataTypeID && strcmp(FullNameBuffer, pFullName) == 0)
				return (*itr);
		}
		pMD = (*itr)->FindChildMetaData(MetaDataTypeID, pFullName);
		if (pMD) return pMD;
	}
	return NULL;
}

bool CMetaData::GetFullName(char *pFullNameBuffer, unsigned int BufferSize) const
{
	if (pFullNameBuffer == NULL)
	{
		return false;
	}

	unsigned int Char_BufferSize(BufferSize - 1 * sizeof(char));
	char *pReBuffer((char*)((unsigned int)pFullNameBuffer + Char_BufferSize));

	CMetaData *pParent(m_pParent);
	const char *pName;
	unsigned int total_size;
	unsigned int cur_len;

	pName = this->GetName();
	
	if (!pName) throw new ExceptionMetaData(D_E_ID_ERR_MD, "元数据未命名！");

	cur_len = strlen(pName);
	total_size = cur_len * sizeof(char);
	if (total_size > Char_BufferSize)
	{
		return false;
	}
	memcpy((void*)((unsigned int)pReBuffer - total_size), pName, cur_len * sizeof(char));

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