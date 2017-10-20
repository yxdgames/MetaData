#pragma once
#include "IInterface.h"

class CLASS_DESCRIPT IPropertyNotify : public IInterface
{
public:
	IPropertyNotify() {}
	virtual ~IPropertyNotify() = 0 {}
public:
	virtual void BeginSet(void *pObj, void *value) = 0;
	virtual void EndSet(void *pObj, void *value) = 0;
	virtual void BeginGet(void *pObj) = 0;
	virtual void EndGet(void *pObj, void *value) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IPropertyNotify)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IPropertyNotify)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IPropertyNotify)
};

