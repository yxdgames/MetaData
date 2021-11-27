#pragma once
#include "../../MetaData/include/IBlob.h"

class CLASS_DESCRIPT IBlobCreater : public IInterface
{
public:
	IBlobCreater() {}
	virtual ~IBlobCreater() = 0;
public:
	virtual IBlob *CreateBlob(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IBlobCreater)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IBlobCreater)
	// { 1575B172-2FF4-459A-8B7D-550620E5C5F5 }
	MD_INTERFACE_GUID_DEF(0x1575b172, 0x2ff4, 0x459a, 0x8b, 0x7d, 0x55, 0x6, 0x20, 0xe5, 0xc5, 0xf5)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IBlobCreater)
};

