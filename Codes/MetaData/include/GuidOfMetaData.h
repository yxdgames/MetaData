#pragma once

#include "..\..\include\CommonDefine.h"
#include "..\..\include\Typedef.h"
#include <string>

#define MD_GUID_DATA_MAX			(16)

/*GUID*/
struct STRUCT_DESCRIPT GuidOfMetaData
{
	TDUIntPtr Data[MD_GUID_DATA_MAX];
public:
	GuidOfMetaData(void) { memset(Data, 0x00, sizeof(Data)); }
	GuidOfMetaData(GuidOfMetaData &src) { memcpy(this->Data, src.Data, sizeof(this->Data)); }
	inline GuidOfMetaData(const void *pData);
	~GuidOfMetaData(void) {}
public:
	inline GuidOfMetaData &operator =(const GuidOfMetaData &src);
	inline GuidOfMetaData &operator =(const void *pData);
	inline bool operator ==(const GuidOfMetaData &guid) const;
	inline bool operator ==(const void *pData) const;
};

typedef GuidOfMetaData		TDGUID;

/*--------------------------------*/
/*   Inline Function Definition   */
/*--------------------------------*/
inline GuidOfMetaData::GuidOfMetaData(const void *pData)
{
	if (pData)
		memcpy(this->Data, pData, sizeof(this->Data));
	else memset(this->Data, 0x00, sizeof(this->Data));
}

inline GuidOfMetaData &GuidOfMetaData::operator =(const GuidOfMetaData &src)
{
	memcpy(this->Data, src.Data, sizeof(this->Data));
	return *this;
}

inline GuidOfMetaData &GuidOfMetaData::operator =(const void *pData)
{
	if (pData)
		memcpy(this->Data, pData, sizeof(this->Data));
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
