#pragma once

#include "IInterface.h"

class CLASS_DESCRIPT IBlob : public IInterface
{
public:
	IBlob(void) {}
	virtual ~IBlob(void) = 0 {}
public:
	//virtual void Get

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IBlob)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IBlob)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IBlob)
};