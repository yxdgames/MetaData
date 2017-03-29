#include "stdafx.h"
#include "..\include\ExceptionMetaData.h"
#include "..\..\include\ExceptionID.h"

ExceptionMetaData::ExceptionMetaData(int ID, const char *pCaption)
	: ExceptionBase((D_E_ID_ERR_MD_END < ID && ID <= D_E_ID_ERR_MD_BEGIN) ? ID : D_E_ID_ERR_MD, pCaption)
{
}


ExceptionMetaData::~ExceptionMetaData(void)
{
}
