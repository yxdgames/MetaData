#pragma once

#include "MetaData.h"

class IInterface;

class CLASS_DESCRIPT CMetaDataType : public CMetaData
{
public:
	CMetaDataType(char *pName, CMetaData *pParent, bool bChildren, unsigned int size);
	virtual ~CMetaDataType(void);
public:
	//method
	virtual bool IsTypeOf(CMetaDataType *pType)										{ return this == pType; }
	virtual void *AsType(void *pObj, CMetaDataType *pType)							{ return (this == pType ? pObj : NULL); }
	virtual bool QueryInterface(void *pObj, char *pIntfName, IInterface **outIntf)	{ return false; }
	virtual void *NewObject(void)													{ return NULL; }
	virtual void DeleteObject(void *pObj)											{ /*do nothing.*/ }
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_TYPE; }
	unsigned int GetSize(void) const			{ return m_Size; }
private:
	unsigned int			m_Size;
};

