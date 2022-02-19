#include "stdafx.h"
#include "../include/ExceptionCommon.h"
#include "../include/ExceptionID.h"

ExceptionCommon::ExceptionCommon(const char *pDescription, bool InConstantStringTable)
	:ExceptionBase(D_E_ID_ERROR, pDescription, InConstantStringTable)
{
}


ExceptionCommon::~ExceptionCommon(void)
{
}
