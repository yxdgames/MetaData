#pragma once

#include "..\..\include\ExceptionBase.h"

class ExceptionSerialization : public ExceptionBase
{
public:
	ExceptionSerialization(int ID, const char *pCaption);
	virtual ~ExceptionSerialization(void);
};

