#include "stdafx.h"
#include "../include/ExceptionBase.h"


ExceptionBase::ExceptionBase(int ID, const char *pCaption)
	: m_ID(ID), m_pCaption(pCaption)
{
}

ExceptionBase::~ExceptionBase(void)
{
}
