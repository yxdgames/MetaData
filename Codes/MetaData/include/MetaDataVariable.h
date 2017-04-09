#pragma once

#include "MetaDataVarBase.h"

class CLASS_DESCRIPT CMetaDataVariable : public CMetaDataVarBase
{
public:
	CMetaDataVariable(char *pName, CMetaData *pParent, CMetaDataType *pType, int PtrLevel, void *pVar);
	virtual ~CMetaDataVariable(void);
public:
	//method
	virtual void Output(void *pOutputAddr);
public:
	//attribute
	virtual unsigned char GetTypeID(void) const	{ return D_META_DATA_TYPE_ID_VARIABLE; }
private:
	void			*m_pVar;
};

