#pragma once

#include "..\..\MetaData\include\IBlob.h"

class IBlobCreater : public IInterface
{
public:
	IBlobCreater() {}
	virtual ~IBlobCreater() = 0 {}
public:
	virtual IBlob *CreateBlob(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IBlobCreater)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IBlobCreater)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IBlobCreater)
};

