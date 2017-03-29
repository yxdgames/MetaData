#pragma once

#include "MetaDataType.h"

#define D_META_DATA_TYPE_ID_ALLOC_TYPE_ID_NONE			(0)

class CMetaDataTypeIDAlloc
{
public:
	CMetaDataTypeIDAlloc(void);
	virtual ~CMetaDataTypeIDAlloc(void);
public:
	unsigned int GetTypeID(CMetaDataType *pType);
private:
	void Init(CMetaData *pMD);
private:
	struct STypeID
	{
		CMetaDataType *pType;
		unsigned int ID;
	};
private:
	unsigned int			m_NextID;
	std::vector<STypeID>	m_TypeID;
};

