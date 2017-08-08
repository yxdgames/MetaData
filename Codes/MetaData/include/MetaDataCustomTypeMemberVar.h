#pragma once

#include "MetaDataVarBase.h"

class CLASS_DESCRIPT CMetaDataCustomTypeMemberVar : public CMetaDataVarBase
{
public:
	CMetaDataCustomTypeMemberVar(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, TDUIntPtr Offset);
	virtual ~CMetaDataCustomTypeMemberVar(void);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE_MEMBER_VAR; }
	TDUIntPtr GetOffset(void) const				{ return m_Offset; }
private:
	TDUIntPtr	m_Offset;
};

