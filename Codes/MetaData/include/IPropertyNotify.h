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
	// { 51B41212-AF3F-4C5E-847A-B104359D6E79 }
	MD_INTERFACE_GUID_DEF(0x51b41212, 0xaf3f, 0x4c5e, 0x84, 0x7a, 0xb1, 0x4, 0x35, 0x9d, 0x6e, 0x79)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IPropertyNotify)
};

