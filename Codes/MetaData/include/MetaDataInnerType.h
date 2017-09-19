#pragma once

#include "MetaDataType.h"

typedef void *(*TpfunNewObject)(void);
typedef void (*TpfunDeleteObject)(void*);

class CLASS_DESCRIPT CMetaDataInnerType : public CMetaDataType
{
public:
	CMetaDataInnerType(const char *pName, const CMetaData *pParent, size_t size,
		TpfunNewObject pfunNewObject, TpfunDeleteObject pfunDeleteObject);
	virtual ~CMetaDataInnerType(void);
public:
	//method
	virtual void *NewObject(void) const			{ return m_pfunNewObject ? m_pfunNewObject() : nullptr; }
	virtual void DeleteObject(void *pObj) const	{ if (m_pfunDeleteObject) m_pfunDeleteObject(pObj); }
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_INNER_TYPE; }
private:
	TpfunNewObject		m_pfunNewObject;
	TpfunDeleteObject	m_pfunDeleteObject;
};

