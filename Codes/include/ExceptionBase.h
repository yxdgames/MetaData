#pragma once

#include "CommonDefine.h"

class CLASS_DESCRIPT ExceptionBase
{
public:
	ExceptionBase(int ID, const char *pCaption);
	virtual ~ExceptionBase(void);
public:
	//attribute
	int GetID(void) const					{ return m_ID; }
	const char *GetCaption(void) const		{ return m_pCaption; }
private:
	int		m_ID;
	const char	*m_pCaption;
};

