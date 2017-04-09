#pragma once

#include "IInterface.h"

class CLASS_DESCRIPT IClone : public IInterface
{
public:
	IClone(void);
	virtual ~IClone(void) = 0 {}
public:
	//method
	virtual bool Clone(void *pObj) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IClone)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(Clone, 0)
MD_INTERFACE_DECLARE_DETAIL(IClone)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(Clone, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pObj, void*, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(bool, 0)
MD_INTERFACE_DECLARE_END(IClone)
};

