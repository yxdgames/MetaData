#pragma once

#include "MetaDataSupport.h"
#include "MetaDataClassType.h"

//#define CO_SIMPLE_STRING_STL_STRING

#ifdef CO_SIMPLE_STRING_STL_STRING
#include <string>
#endif //CO_SIMPLE_STRING_STL_STRING

class CLASS_DESCRIPT SimpleString
#ifdef CO_SIMPLE_STRING_STL_STRING
	: private std::string
#endif //CO_SIMPLE_STRING_STL_STRING
{
public:
	SimpleString(void);
	SimpleString(char *pStr);
	virtual ~SimpleString(void);
public:
	//attr
	void SetValue(char *pStr);
	const char *GetValue(void);
#ifndef CO_SIMPLE_STRING_STL_STRING
private:
	void FreeString(void);
private:
	char	*m_pString;
#endif //CO_SIMPLE_STRING_STL_STRING

MD_CLASS_TYPE_DECLARE_BEGIN(SimpleString)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(SimpleString)
MD_CLASS_TYPE_DECLARE_END(SimpleString)
};