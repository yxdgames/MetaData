#include "stdafx.h"
#include "..\include\CharArray.h"


CCharArray::CCharArray(unsigned int size)
	:m_pCharArray(new char [size])
{
}


CCharArray::~CCharArray(void)
{
	delete [] m_pCharArray;
}
