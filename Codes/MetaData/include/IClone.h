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
	// { DA57010E-371F-483E-9E9F-0894B5F7F6D0 }
	MD_INTERFACE_GUID_DEF(0xda57010e, 0x371f, 0x483e, 0x9e, 0x9f, 0x8, 0x94, 0xb5, 0xf7, 0xf6, 0xd0)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(Clone, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(IInterface, 1)
MD_INTERFACE_DECLARE_END(IClone)
};

