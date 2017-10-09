#pragma once

#include "IBlobCreater.h"

class CLASS_DESCRIPT ISetBlobCreater : public IInterface
{
public:
	ISetBlobCreater() {}
	virtual ~ISetBlobCreater() = 0 {}
public:
	virtual void SetBlobCreater(IBlobCreater *pBlobCreater) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(ISetBlobCreater)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(ISetBlobCreater)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(ISetBlobCreater)
};

