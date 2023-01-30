#pragma once
#include "../../include/Typedef.h"
#include "../../include/CommonDefine.h"
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
	inline bool Compare(const CMetaData *pMetaData) const;
	inline bool Compare(const TDGUID &guid) const;
	inline bool Compare(const char *pFullName) const;
	const CMetaData *FindChildMetaData(const TDGUID &guid) const;
	const CMetaData *FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName) const;
	bool FindChildMetaData(unsigned char MetaDataTypeID, const char *pFullName, std::vector<const CMetaData*> &Children) const;
public:
	//attribute
	void SetName(const char *pName)							{ m_pName = pName; }
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
	const TDGUID &GetGUID(void) const { return m_GUID; }
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

/*--------------------------------*/
/*   Inline Function Definition   */
/*--------------------------------*/
#include "../../include/TArray.h"
#include "../../include/MDAssert.h"

inline bool CMetaData::Compare(const CMetaData * pMetaData) const
{
	_MD_ASSERT_(nullptr != pMetaData);
	return (this == pMetaData) || (pMetaData->m_GUID.IsValid() && this->m_GUID == pMetaData->m_GUID);
}

inline bool CMetaData::Compare(const TDGUID &guid) const
{
	return this->m_GUID.IsValid() && this->m_GUID == guid;
}

inline bool CMetaData::Compare(const char *pFullName) const
{
	TDCharArray char_array(1024);
	return pFullName && this->GetFullName(char_array.array(), char_array.array_size())
		&& (strcmp(char_array.array(), pFullName) == 0 || strcmp(char_array.array() + 2, pFullName) == 0); //+2是为了跳过"::"两个字符
}