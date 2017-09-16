#include "stdafx.h"
#include "..\include\SimpleString.h"
#include <string>

SimpleString::SimpleString(void)
	: m_pString(new std::string)
{
}

SimpleString::SimpleString(char *pStr)
	: m_pString(new std::string(pStr ? pStr : ""))
{

}

SimpleString::SimpleString(SimpleString &Src)
	: m_pString(new std::string(*Src.m_pString))
{
}

SimpleString::~SimpleString(void)
{
	FreeString();
}

inline void SimpleString::FreeString(void)
{
	if (m_pString)
	{
		delete m_pString;
		m_pString = nullptr;
	}
}

