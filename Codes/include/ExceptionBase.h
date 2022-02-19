#pragma once
#include "CommonDefine.h"
#include <string>

class CLASS_DESCRIPT ExceptionBase
{
public:
	ExceptionBase(int ID, const char *pDescription, bool InConstantStringTable);
	virtual ~ExceptionBase(void);
public:
	//attribute
	int GetID(void) const					{ return m_ID; }
	const char *GetDescription(void) const	{ return m_InConstantStringTable ? m_pDescription : m_strDescription->c_str(); }
private:
	const int	m_ID;
	const bool	m_InConstantStringTable;
	union {
		const char *m_pDescription;
		std::string *m_strDescription;
	};
};

