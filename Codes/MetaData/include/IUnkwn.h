#pragma once

#include "MetaDataSupport.h"

#define IUNKWN_CALLCONVENTION				__stdcall
#define IUNKWN_MEMFUN_DESCRIPT				IUNKWN_CALLCONVENTION

#define IUNKWN_CONSTRAINT(unkwn_name) \
	protected: \
		unkwn_name(void) {} \
		~unkwn_name(void) {}

struct STRUCT_DESCRIPT IUnkwn
{

IUNKWN_CONSTRAINT(IUnkwn)
/*Meta Data Definition*/
MD_UNKWN_INTERFACE_DECLARE_BEGIN(IUnkwn)
MD_UNKWN_INTERFACE_DECLARE_DETAIL_KERNEL(IUnkwn)
MD_UNKWN_INTERFACE_DECLARE_END(IUnkwn)
};