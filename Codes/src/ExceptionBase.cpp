#include "stdafx.h"
#include "../include/ExceptionBase.h"


ExceptionBase::ExceptionBase(int ID, const char *pDescription, bool bDirectRefDesc)
	: m_ID(ID), m_bDirectRefDesc(bDirectRefDesc)
{
	if (m_bDirectRefDesc)
		m_pDescription = pDescription ? pDescription : "";
	else m_strDescription = new std::string(pDescription ? pDescription : "");
}

ExceptionBase::~ExceptionBase(void)
{
	if (!m_bDirectRefDesc) delete m_strDescription;
}
