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
	// { BF21BAF5-F8C3-4B68-AB60-38C2D343FC3E }
	MD_INTERFACE_GUID_DEF(0xbf21baf5, 0xf8c3, 0x4b68, 0xab, 0x60, 0x38, 0xc2, 0xd3, 0x43, 0xfc, 0x3e)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(ISetBlobCreater)
};

