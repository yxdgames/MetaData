#pragma once

#include "MetaData.h"

class IInterface;

class CLASS_DESCRIPT CMetaDataType : public CMetaData
{
public:
	CMetaDataType(const char *pName, const CMetaData *pParent, bool bChildren, unsigned int size);
	virtual ~CMetaDataType(void);
public:
	//method
	virtual bool IsTypeOf(const CMetaDataType *pType) const									{ return this == pType; }
	virtual void *AsType(void *pObj, const CMetaDataType *pType) const						{ return (this == pType ? pObj : nullptr); }
	virtual bool QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf) const	{ return false; }
	virtual void *NewObject(void) const														{ return nullptr; }
	virtual void DeleteObject(void *pObj) const												{ /*do nothing.*/ }
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_TYPE; }
	unsigned int GetSize(void) const			{ return m_Size; }
private:
	unsigned int			m_Size;
};

