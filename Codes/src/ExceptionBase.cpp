#include "stdafx.h"
#include "../include/ExceptionBase.h"


ExceptionBase::ExceptionBase(int ID, const char *pDescription, bool InConstantStringTable)
	: m_ID(ID), m_InConstantStringTable(InConstantStringTable)
{
	if (m_InConstantStringTable)
		m_pDescription = pDescription ? pDescription : "";
	else m_strDescription = new std::string(pDescription ? pDescription : "");
}

ExceptionBase::~ExceptionBase(void)
{
	if (!m_InConstantStringTable) delete m_strDescription;
}
