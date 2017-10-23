#include "stdafx.h"
#include "..\include\GuidOfMetaData.h"

static TDUIntPtr gGuidInvalidData[MD_GUID_DATA_MAX] = { 0x00 };

//GuidOfMetaData
const GuidOfMetaData *GuidOfMetaData::m_pInvalid = nullptr;

//Only for static member GuidOfMetaData object
const GuidOfMetaData &GuidOfMetaData::Invalid(void)
{
	if (!m_pInvalid)
	{
		m_pInvalid = new GuidOfMetaData;
		memcpy(const_cast<GuidOfMetaData*>(m_pInvalid)->Data, gGuidInvalidData, sizeof(m_pInvalid->Data));
	}
	return *m_pInvalid;
}


//CGuidOfMetaDataInitUninit

class CGuidOfMetaDataInitUninit
{
private:
	CGuidOfMetaDataInitUninit(void)
	{
	}
	~CGuidOfMetaDataInitUninit(void)
	{
		if (GuidOfMetaData::m_pInvalid)
		{
			delete GuidOfMetaData::m_pInvalid;
			GuidOfMetaData::m_pInvalid = nullptr;
		}
	}
private:
	static CGuidOfMetaDataInitUninit m_SingleInstance;
};

CGuidOfMetaDataInitUninit CGuidOfMetaDataInitUninit::m_SingleInstance;