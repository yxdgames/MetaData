#pragma once

#include "..\..\include\Typedef.h"
#include "..\..\include\CommonDefine.h"

#include <vector>

/* Ԫ��������ID����ʶ������Ԫ���ݡ� */
#define D_META_DATA_TYPE_ID_META_DATA				((unsigned char)(1))
#define D_META_DATA_TYPE_ID_GLOBAL_SPACE			((unsigned char)(2))
#define D_META_DATA_TYPE_ID_NAME_SPACE				((unsigned char)(3))
#define D_META_DATA_TYPE_ID_TYPE					((unsigned char)(4))
#define D_META_DATA_TYPE_ID_INNER_TYPE				((unsigned char)(5))
#define D_META_DATA_TYPE_ID_CUSTOM_TYPE				((unsigned char)(6))
#define D_META_DATA_TYPE_ID_CUSTOM_TYPE_MEMBER_VAR	((unsigned char)(7))
#define D_META_DATA_TYPE_ID_CLASS_TYPE				((unsigned char)(8))
#define D_META_DATA_TYPE_ID_INTERFACE				((unsigned char)(9))
#define D_META_DATA_TYPE_ID_VAR_BASE				((unsigned char)(10))
#define D_META_DATA_TYPE_ID_VARIABLE				((unsigned char)(11))
#define D_META_DATA_TYPE_ID_FUNCTION				((unsigned char)(12))

class CLASS_DESCRIPT CMetaData
{
public:
	CMetaData(const char *pName, const CMetaData *pParent, bool bChildren);
	virtual ~CMetaData(void);
public:
	//method
	const CMetaData *FindChildMetaData(unsigned char MetaDataTypeID, char *pFullName) const;
	bool FindChildMetaData(unsigned char MetaDataTypeID, char *pFullName, std::vector<const CMetaData*> &Children) const;
public:
	//attribute
	const char *GetName(void) const							{ return m_pName; }
	bool GetFullName(char *pFullNameBuffer, size_t BufferSize) const;
	virtual unsigned char GetTypeID(void) const				{ return D_META_DATA_TYPE_ID_META_DATA; }
	const char *GetTypeCaption(void) const;
	size_t GetChildrenCount(void) const					{ return (m_pChildren ? m_pChildren->size() : 0); }
	const CMetaData *GetChild(size_t index) const		{ return (m_pChildren ? m_pChildren->at(index) : nullptr); }
private:
	void InsertSelfToParent(void);
	void RemoveSelfFromParent(void);
	const bool FindChildMetaData(unsigned char MetaDataTypeID, char *pFullName, std::vector<const CMetaData*> &Children, bool bClear) const;
private:
	const char						*m_pName;
	const CMetaData					*m_pParent;
	std::vector<const CMetaData*>	*m_pChildren;
};

extern FUNC_DESCRIPT const CMetaData *AssertMetaData(const CMetaData *pMetaData, unsigned char TypeID);