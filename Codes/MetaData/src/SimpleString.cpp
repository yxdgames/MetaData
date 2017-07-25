#include "stdafx.h"
#include "..\include\SimpleString.h"
#include <string>

SimpleString::SimpleString(void)
#ifndef CO_SIMPLE_STRING_STL_STRING
	: m_pString(nullptr)
#endif //CO_SIMPLE_STRING_STL_STRING
{
}

SimpleString::SimpleString(char *pStr)
#ifdef CO_SIMPLE_STRING_STL_STRING
	: std::string(pStr)
#else
	: m_pString(nullptr)
#endif //CO_SIMPLE_STRING_STL_STRING
{
#ifdef CO_SIMPLE_STRING_STL_STRING
	//None
#else
	SetValue(pStr);
#endif //CO_SIMPLE_STRING_STL_STRING
}

SimpleString::~SimpleString(void)
{
#ifndef CO_SIMPLE_STRING_STL_STRING
	FreeString();
#endif //CO_SIMPLE_STRING_STL_STRING
}

void SimpleString::SetValue(char *pStr)
{
#ifdef CO_SIMPLE_STRING_STL_STRING
	if (pStr)
		(*this) = pStr;
	else this->clear();
#else
	FreeString();
	if (pStr)
	{
		int str_len(strlen(pStr));
		m_pString = new char[str_len + 1];
		strcpy(m_pString, pStr);
	}
#endif //CO_SIMPLE_STRING_STL_STRING
}

const char *SimpleString::GetValue(void)
{
#ifdef CO_SIMPLE_STRING_STL_STRING
	return this->c_str();
#else
	return m_pString;
#endif //CO_SIMPLE_STRING_STL_STRING
}

#ifndef CO_SIMPLE_STRING_STL_STRING
void SimpleString::FreeString(void)
{
	if (m_pString)
	{
		delete [] m_pString;
		m_pString = nullptr;
	}
}
int SimpleString::Position(char * pString, int StrLen, char c, bool bLeftToRight)
{
	if (!pString || !StrLen) return -1;
	char *pS, *pE;
	int diff_move;
	if (bLeftToRight)
	{
		pS = pString;
		pE = pString + StrLen - 1;
		diff_move = 1;
	}
	else
	{
		pS = pString + StrLen - 1;
		pE = pString;
		diff_move = -1;
	}
	while (pS != pE)
	{
		if (*pS == c)
		{
			return (pS - pString);
		}
		pS += diff_move;
	}

	return -1;
}
#endif //CO_SIMPLE_STRING_STL_STRING

