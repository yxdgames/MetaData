#pragma once

#include "..\..\Codes\MetaData\include\MetaDataSupport.h"
#include "..\..\Codes\MetaData\include\IPropertyNotify.h"

class CTest
{
public:
	CTest(void);
public:
	void SetInt(int value) { m_Int = value; }
	int GetInt(void) { return m_Int; }
public:
	Property<CTest, int> propInt;
private:
	int		m_Int;
private:
	static CTest Intance;
MD_CLASS_TYPE_DECLARE_BEGIN(CTest)
MD_CLASS_TYPE_DECLARE_DETAIL(CTest)
MD_CLASS_TYPE_DECLARE_END(CTest)
};

