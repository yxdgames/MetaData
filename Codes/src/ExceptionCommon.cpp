#include "stdafx.h"
#include "..\include\ExceptionCommon.h"
#include "..\include\ExceptionID.h"

ExceptionCommon::ExceptionCommon(const char *pCaption)
	:ExceptionBase(D_E_ID_ERROR, pCaption)
{
}


ExceptionCommon::~ExceptionCommon(void)
{
}
