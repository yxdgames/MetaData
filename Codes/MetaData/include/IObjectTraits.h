#pragma once

#include "IInterface.h"

class CLASS_DESCRIPT IObjectTraits : public IInterface
{
public:
	IObjectTraits(void) {}
	virtual ~IObjectTraits(void) = 0 {}
public:
	virtual const CMetaDataType *GetActualMetaDataType(void) = 0;
	virtual void *GetActualSelf(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IObjectTraits)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IObjectTraits)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IObjectTraits)
};

