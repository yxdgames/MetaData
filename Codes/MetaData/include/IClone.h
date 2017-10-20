#pragma once

#include "IInterface.h"

class CLASS_DESCRIPT IClone : public IInterface
{
public:
	IClone(void) {}
	virtual ~IClone(void) = 0 {}
public:
	//method
	virtual IInterface *Clone(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IClone)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(Clone, 0)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IClone)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(Clone, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(IInterface, 1)
MD_INTERFACE_DECLARE_END(IClone)
};

