#include "stdafx.h"
#include "../include/ExceptionMetaData.h"
#include "../include/ExceptionIDMetaData.h"

ExceptionMetaData::ExceptionMetaData(int ID, const char *pDescription, bool InConstantStringTable)
	: ExceptionBase((D_E_ID_MD_END < ID && ID <= D_E_ID_MD_BEGIN) ? ID : D_E_ID_MD_ERROR, pDescription, InConstantStringTable)
{
}


ExceptionMetaData::~ExceptionMetaData(void)
{
}
