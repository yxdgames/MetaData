#pragma once

#include "MetaData.h"

class IInterface;

class CLASS_DESCRIPT CMetaDataType : public CMetaData
{
public:
	CMetaDataType(const char *pName, const CMetaData *pParent, bool bChildren, size_t size);
	virtual ~CMetaDataType(void);
public:
	//method
	virtual bool IsTypeOf(const CMetaDataType *pType) const									{ return this == pType; }
	virtual bool IsTypeOf(const TDGUID &type_guid) const									{ return this->Compare(type_guid); }
	virtual void *AsType(void *pObj, const CMetaDataType *pType) const						{ return (this == pType ? pObj : nullptr); }
	virtual void *AsType(void *pObj, const TDGUID &type_guid) const							{ return (this->Compare(type_guid) ? pObj : nullptr); }
	virtual bool QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf) const	{ return false; }
	virtual void *NewObject(void) const														{ return nullptr; }
	virtual void DeleteObject(void *pObj) const												{ /*do nothing.*/ }
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_TYPE; }
	size_t GetSize(void) const					{ return m_Size; }
private:
	size_t			m_Size;
};

