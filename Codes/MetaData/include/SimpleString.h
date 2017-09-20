#pragma once

#include "MetaDataSupport.h"
#include "MetaDataClassType.h"

#include <string>

class CLASS_DESCRIPT SimpleString
{
public:
	SimpleString(void);
	SimpleString(char *pStr);
	SimpleString(SimpleString &Src);
	virtual ~SimpleString(void);
public:
	//attr
	void SetValue(char *pStr) { (*m_pString) = pStr ? pStr : ""; }
	const char *GetValue(void) { return m_pString->c_str(); }
public:
	//operator
	SimpleString &operator=(char *pStr) { this->SetValue(pStr); return *this; }
	SimpleString &operator=(SimpleString &Src) { *this->m_pString = *Src.m_pString; return *this; }
private:
	inline void FreeString(void);
private:
	std::string		*m_pString;

MD_CLASS_TYPE_DECLARE_BEGIN(SimpleString)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(0)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(1)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(2)
	MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(SimpleString)
	MD_CLASS_TYPE_CONSTRUCTOR_DEF(0)
	MD_CLASS_TYPE_CONSTRUCTOR_DEF(1)
		MD_CUSTOM_TYPE_CONSTRUCTOR_PARAM_DEF(pStr, char, 1)
	MD_CLASS_TYPE_CONSTRUCTOR_DEF(2)
		MD_CUSTOM_TYPE_CONSTRUCTOR_PARAM_DEF(Src, SimpleString, 1)
	MD_CLASS_TYPE_DESTRUCTOR_DEF()
MD_CLASS_TYPE_DECLARE_END(SimpleString)
};

