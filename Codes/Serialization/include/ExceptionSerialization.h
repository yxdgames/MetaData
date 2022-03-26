#pragma once
#include "../../include/ExceptionBase.h"

class CLASS_DESCRIPT ExceptionSerialization : public ExceptionBase
{
public:
	ExceptionSerialization(int ID, const char *pDescription, bool bDirectRefDesc);
	virtual ~ExceptionSerialization(void);
};

