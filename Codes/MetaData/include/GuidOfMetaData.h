#pragma once
#include "../../include/CommonDefine.h"
#include "../../include/Typedef.h"
#include <string>
#include <string.h>

#define MD_GUID_DATA_MAX			(16)

/*GUID*/
struct STRUCT_DESCRIPT GuidOfMetaData
{
	TDByte		Data[MD_GUID_DATA_MAX];

public:
	GuidOfMetaData(void) :m_Valid(false) {}
	GuidOfMetaData(GuidOfMetaData &src) :m_Valid(src.m_Valid){ memcpy(this->Data, src.Data, sizeof(this->Data)); }
	inline GuidOfMetaData(const void *pData);
	~GuidOfMetaData(void) {}
public:
	bool IsValid(void) const { return m_Valid; }
public:
	inline GuidOfMetaData &operator =(const GuidOfMetaData &src);
	inline GuidOfMetaData &operator =(const void *pData);
	inline bool operator ==(const GuidOfMetaData &guid) const;
	inline bool operator ==(const void *pData) const;
private:
	void UpdateValidFlag(void) { m_Valid = !(GuidOfMetaData::Invalid() == *this); }
private:
	bool		m_Valid;

public:
	//Enumeration of GuidOfMetaData value
	static const GuidOfMetaData &Invalid(void);
private:
	static const GuidOfMetaData *m_pInvalid;
	friend class CGuidOfMetaDataInitUninit;
};

typedef GuidOfMetaData		TDGUID;

/*--------------------------------*/
/*   Inline Function Definition   */
/*--------------------------------*/
inline GuidOfMetaData::GuidOfMetaData(const void *pData)
	:m_Valid(false)
{
	if (pData)
	{
		memcpy(this->Data, pData, sizeof(this->Data));
		UpdateValidFlag();
	}
}

inline GuidOfMetaData &GuidOfMetaData::operator =(const GuidOfMetaData &src)
{
	memcpy(this->Data, src.Data, sizeof(this->Data));
	this->m_Valid = src.m_Valid;
	return *this;
}

inline GuidOfMetaData &GuidOfMetaData::operator =(const void *pData)
{
	if (pData)
	{
		memcpy(this->Data, pData, sizeof(this->Data));
		UpdateValidFlag();
	}
	return *this;
}

inline bool GuidOfMetaData::operator ==(const GuidOfMetaData &guid) const
{
	return !memcmp(this->Data, guid.Data, sizeof(this->Data));
}

inline bool GuidOfMetaData::operator ==(const void *pData) const
{
	if (pData)
		return !memcmp(this->Data, pData, sizeof(this->Data));
	else return false;
}
