#pragma once

#include "..\..\Codes\MetaData\include\MetaDataSupport.h"

class CTest
{
public:
	CTest(void);
private:
	static CTest Intance;
MD_CLASS_TYPE_DECLARE_BEGIN(CTest)
MD_CLASS_TYPE_DECLARE_DETAIL(CTest)
MD_CLASS_TYPE_DECLARE_END(CTest)
};

