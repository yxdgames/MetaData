#include "stdafx.h"
#include "..\include\Property.h"
#include "..\include\IPropertyNotify.h"

void CPropertyBase::AddPropertyNotification(IPropertyNotify *pNotify)
{
	if (pNotify) m_pPropertyNotifications->push_back(pNotify);
}

void CPropertyBase::DelPropertyNotification(IPropertyNotify *pNotify)
{
	if (!pNotify) return;
	for (std::vector<IPropertyNotify*>::iterator itr = m_pPropertyNotifications->begin();
		itr != m_pPropertyNotifications->end(); ++itr)
	{
		if (*itr == pNotify)
		{
			m_pPropertyNotifications->erase(itr);
			break;
		}
	}
}

void CPropertyBase::ClearNotification(void)
{
	this->m_pPropertyNotifications->clear();
}

void CPropertyBase::BeginSet(void * pObj, TDUIntPtr PropertyTag, void * value)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->BeginSet(pObj, PropertyTag, value);
	}
}

void CPropertyBase::EndSet(void * pObj, TDUIntPtr PropertyTag, void * value)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->EndSet(pObj, PropertyTag, value);
	}
}

void CPropertyBase::BeginGet(void *pObj, TDUIntPtr PropertyTag)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->BeginGet(pObj, PropertyTag);
	}
}

void CPropertyBase::EndGet(void * pObj, TDUIntPtr PropertyTag, void * value)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->EndGet(pObj, PropertyTag, value);
	}
}
