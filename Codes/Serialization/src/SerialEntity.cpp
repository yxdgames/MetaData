#include "stdafx.h"
#include "..\include\SerialEntity.h"

CSerialEntity::CSerialEntity(CSerialEntity *pParent)
	:m_pName(new std::string), m_pTypeName(new std::string),
	m_Tag(0), m_pParent(pParent),
	m_pChildren(new std::vector<CSerialEntity*>)
{
	if (m_pParent) m_pParent->m_pChildren->push_back(this);
}


CSerialEntity::~CSerialEntity(void)
{
	FreeChildren();
	
	if (m_pParent) m_pParent->RemoveChild(this);

	delete m_pChildren;
	delete m_pTypeName;
	delete m_pName;
}

void CSerialEntity::SetReleaseStringFlag(bool flag)
{
	m_value.SetReleaseStringFlag(flag);
}

//method
ISerialEntity *CSerialEntity::NewChild(void)
{
	return new CSerialEntity(this);
}

void CSerialEntity::DelChild(ISerialEntity *pChild)
{
	std::vector<CSerialEntity*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if (*itr == pChild)
		{
			delete (*itr);
			break;
		}
	}
}

void CSerialEntity::ClearChildren(void)
{
	FreeChildren();
}

ISerialEntity *CSerialEntity::FindChild(const char *pName, char *EntTypeName, TDUIntPtr Tag)
{
	std::vector<CSerialEntity*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if (strcmp((*itr)->GetName(), pName) == 0 && strcmp((*itr)->GetEntTypeName(), EntTypeName) == 0
			&& (*itr)->GetTag() == Tag)
		{
			return *itr;
		}
	}
	return nullptr;
}

//attribute
void CSerialEntity::SetName(const char *pName)
{
	if (pName)
	{
		*m_pName = pName;
	}
	else *m_pName = "";
}

const char *CSerialEntity::GetName(void)
{
	return m_pName->c_str();
}

void CSerialEntity::SetEntTypeName(const char *pName)
{
	if (pName)
	{
		*m_pTypeName = pName;
	}
	else *m_pTypeName = "";
}

const char *CSerialEntity::GetEntTypeName(void)
{
	return m_pTypeName->c_str();
}

void CSerialEntity::SetTag(TDUIntPtr Tag)
{
	m_Tag = Tag;
}

TDUIntPtr CSerialEntity::GetTag(void)
{
	return m_Tag;
}

void CSerialEntity::SetValue(const char *pValue)
{
	m_value.SetValue(pValue);
}

void CSerialEntity::SetValue(const int Value)
{
	m_value.SetValue(Value);
}

void CSerialEntity::SetValue(const long long Value)
{
	m_value.SetValue(Value);
}

void CSerialEntity::SetValue(const double Value)
{
	m_value.SetValue(Value);
}

void CSerialEntity::SetValue(const long double Value)
{
	m_value.SetValue(Value);
}

void CSerialEntity::SetValue(const bool Value)
{
	m_value.SetValue(Value);
}

SVariant &CSerialEntity::GetValue(void)
{
	return m_value;
}

ISerialEntity *CSerialEntity::GetParent(void)
{
	return m_pParent;
}

size_t CSerialEntity::GetChildrenCount(void)
{
	return m_pChildren->size();
}

ISerialEntity *CSerialEntity::GetChildren(size_t index)
{
	return m_pChildren->at(index);
}

void CSerialEntity::RemoveChild(CSerialEntity *pChild)
{
	std::vector<CSerialEntity*>::iterator itr;
	for (itr = m_pChildren->begin(); itr != m_pChildren->end(); ++itr)
	{
		if ((*itr) == pChild)
		{
			m_pChildren->erase(itr);
			break;
		}
	}
}

void CSerialEntity::FreeChildren(void)
{
	for (size_t index = m_pChildren->size(); index > 0; --index)
	{
		delete m_pChildren->at(index - 1);
	}
}