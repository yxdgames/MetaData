#pragma once

#include "..\..\include\Typedef.h"
#include "..\..\include\CommonDefine.h"
#include "GuidOfMetaData.h"

#include <vector>

/* 元数据类型ID，标识是哪种元数据。 */
#define D_META_DATA_TYPE_ID_META_DATA				((unsigned char)(1))
#define D_META_DATA_TYPE_ID_GLOBAL_SPACE			((unsigned char)(2))
#define D_META_DATA_TYPE_ID_NAME_SPACE				((unsigned char)(3))
#define D_META_DATA_TYPE_ID_TYPE					((unsigned char)(4))
#define D_META_DATA_TYPE_ID_INNER_TYPE				((unsigned char)(5))
#define D_META_DATA_TYPE_ID_CUSTOM_TYPE				((unsigned char)(6))
#define D_META_DATA_TYPE_ID_CUSTOM_TYPE_MEMBER_VAR	((unsigned char)(7))
#define D_META_DATA_TYPE_ID_CUSTOM_TYPE_PROPERTY	((unsigned char)(8))
#define D_META_DATA_TYPE_ID_CLASS_TYPE				((unsigned char)(9))
#define D_META_DATA_TYPE_ID_INTERFACE				((unsigned char)(10))
#define D_META_DATA_TYPE_ID_VAR_BASE				((unsigned char)(11))
#define D_META_DATA_TYPE_ID_VARIABLE				((unsigned char)(12))
#define D_META_DATA_TYPE_ID_FUNCTION				((unsigned char)(13))

class CLASS_DESCRIPT CMetaData
{
public:
	CMetaData(const char *pName, const CMetaData *pParent, bool bChildren);
	virtual ~CMetaData(void);
public:
	//method
	const CMetaData *FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName) const;
	bool FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName, std::vector<const CMetaData*> &Children) const;
	bool Compare(const CMetaData *pMetaData) const { return (this == pMetaData) || (pMetaData && pMetaData->m_GUID == this->m_GUID); }
	bool Compare(const TDGUID &guid) const { return this->m_GUID == guid; }
public:
	//attribute
	const char *GetName(void) const							{ return m_pName; }
	bool GetFullName(char *pFullNameBuffer, size_t BufferSize) const;
	virtual unsigned char GetTypeID(void) const				{ return D_META_DATA_TYPE_ID_META_DATA; }
	const char *GetTypeCaption(void) const;
	size_t GetChildrenCount(void) const					{ return (m_pChildren ? m_pChildren->size() : 0); }
	const CMetaData *GetChild(size_t index) const		{ return (m_pChildren ? m_pChildren->at(index) : nullptr); }
public:
	//GUID
	void SetGUID(const TDGUID &guid) { this->m_GUID = guid; }
	void SetGUID(const void *pData) { this->m_GUID = pData; }
private:
	void InsertSelfToParent(void);
	void RemoveSelfFromParent(void);
	const bool FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName, std::vector<const CMetaData*> &Children, bool bClear) const;
private:
	TDGUID							m_GUID;
	const char						*m_pName;
	const CMetaData					*m_pParent;
	std::vector<const CMetaData*>	*m_pChildren;
};

extern FUNC_DESCRIPT const CMetaData *AssertMetaData(const CMetaData *pMetaData, unsigned char TypeID);