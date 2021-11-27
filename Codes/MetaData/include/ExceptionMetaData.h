#pragma once
#include "../../include/ExceptionBase.h"

class CLASS_DESCRIPT ExceptionMetaData : public ExceptionBase
{
public:
	ExceptionMetaData(int ID, const char *pCaption);
	virtual ~ExceptionMetaData(void);
};