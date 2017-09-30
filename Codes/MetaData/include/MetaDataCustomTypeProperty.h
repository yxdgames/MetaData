#pragma once

#include "MetaDataVarBase.h"
#include "Property.h"

class CLASS_DESCRIPT CMetaDataCustomTypeProperty : public CMetaDataVarBase
{
public:
	CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, TDUIntPtr Offset);
	CMetaDataCustomTypeProperty(const char *pName, const CMetaData *pParent, const CMetaDataType *pType, int PtrLevel, CPropertyBase *pProperty);
	virtual ~CMetaDataCustomTypeProperty(void);
public:
	union UPropertyLocation
	{
		TDUIntPtr Offset;
		CPropertyBase *pProperty;
	};
public:
	//attribute
	virtual unsigned char GetTypeID(void) const			{ return D_META_DATA_TYPE_ID_CUSTOM_TYPE_PROPERTY; }
	UPropertyLocation GetPropertyLocation(void) const	{ return m_PropertyLocation; }
	bool PropertyLocationIsOffset(void) const			{ return m_PropertyLocationIsOffset; }
private:
	UPropertyLocation	m_PropertyLocation;
	bool				m_PropertyLocationIsOffset;
};

