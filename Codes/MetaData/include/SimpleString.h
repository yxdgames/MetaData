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
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(SimpleString)
MD_CLASS_TYPE_DECLARE_END(SimpleString)
};

