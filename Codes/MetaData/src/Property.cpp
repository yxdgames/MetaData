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

void CPropertyBase::BeginSet(void * pObj, void * value)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->BeginSet(pObj, value);
	}
}

void CPropertyBase::EndSet(void * pObj, void * value)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->EndSet(pObj, value);
	}
}

void CPropertyBase::BeginGet(void *pObj)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->BeginGet(pObj);
	}
}

void CPropertyBase::EndGet(void * pObj, void * value)
{
	for (size_t i = 0; i < m_pPropertyNotifications->size(); ++i)
	{
		m_pPropertyNotifications->at(i)->EndGet(pObj, value);
	}
}
