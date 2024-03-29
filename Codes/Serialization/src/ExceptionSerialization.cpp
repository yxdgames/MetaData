#include "stdafx.h"
#include "../include/ExceptionSerialization.h"
#include "../include/ExceptionIDSerialization.h"

ExceptionSerialization::ExceptionSerialization(int ID, const char *pDescription, bool bDirectRefDesc)
	: ExceptionBase((D_E_ID_SERIAL_END < ID && ID <= D_E_ID_SERIAL_BEGIN) ? ID : D_E_ID_SERIAL_ERROR, pDescription, bDirectRefDesc)
{
}


ExceptionSerialization::~ExceptionSerialization(void)
{
}
