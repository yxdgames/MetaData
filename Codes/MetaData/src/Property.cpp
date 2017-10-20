#include "stdafx.h"
#include "..\include\Property.h"
#include "..\include\IPropertyNotify.h"

void CPropertyBase::BeginSet(void * pObj, void * value)
{
	if (m_pPropertyNotify) m_pPropertyNotify->BeginSet(pObj, value);
}

void CPropertyBase::EndSet(void * pObj, void * value)
{
	if (m_pPropertyNotify) m_pPropertyNotify->EndSet(pObj, value);
}

void CPropertyBase::BeginGet(void *pObj)
{
	if (m_pPropertyNotify) m_pPropertyNotify->BeginGet(pObj);
}

void CPropertyBase::EndGet(void * pObj, void * value)
{
	if (m_pPropertyNotify) m_pPropertyNotify->EndGet(pObj, value);
}
