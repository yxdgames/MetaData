#pragma once
#include "ExceptionBase.h"

class CLASS_DESCRIPT ExceptionCommon : public ExceptionBase
{
public:
	ExceptionCommon(const char *pDescription, bool InConstantStringTable);
	virtual ~ExceptionCommon(void);
};

