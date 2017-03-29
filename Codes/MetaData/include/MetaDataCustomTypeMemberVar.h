#pragma once

#include "MetaDataVarBase.h"

class CMetaDataCustomTypeMemberVar : public CMetaDataVarBase
{
public:
	CMetaDataCustomTypeMemberVar(char *pName, CMetaData *pParent, CMetaDataType *pType, int PtrLevel, unsigned int Offset);
	virtual ~CMetaDataCustomTypeMemberVar(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE_MEMBER_VAR; }
	unsigned int GetOffset(void)				{ return m_Offset; }
private:
	unsigned int	m_Offset;
};

