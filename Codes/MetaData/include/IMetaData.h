#pragma once

#include "IInterface.h"

class CLASS_DESCRIPT IMetaData : public IInterface
{
public:
	IMetaData(void) {}
	virtual ~IMetaData(void) = 0 {}
public:
	virtual CMetaDataType *GetActualMetaDataType(void) = 0;
	virtual void *GetActualSelf(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IMetaData)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IMetaData)
MD_INTERFACE_DECLARE_END(IMetaData)
};

