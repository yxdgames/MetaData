#include "stdafx.h"
#include "..\include\ExceptionSerialization.h"
#include "..\..\include\ExceptionID.h"

ExceptionSerialization::ExceptionSerialization(int ID, const char *pCaption)
	: ExceptionBase((D_E_ID_ERR_SERIAL_END < ID && ID <= D_E_ID_ERR_SERIAL_BEGIN) ? ID : D_E_ID_ERR_SERIAL, pCaption)
{
}


ExceptionSerialization::~ExceptionSerialization(void)
{
}
