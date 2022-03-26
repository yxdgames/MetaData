#include "stdafx.h"
#include "../include/ExceptionCommon.h"
#include "../include/ExceptionID.h"

ExceptionCommon::ExceptionCommon(const char *pDescription, bool bDirectRefDesc)
	:ExceptionBase(D_E_ID_ERROR, pDescription, bDirectRefDesc)
{
}


ExceptionCommon::~ExceptionCommon(void)
{
}
