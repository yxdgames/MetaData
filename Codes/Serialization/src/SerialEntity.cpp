#include "stdafx.h"
#include "..\include\SerialEntity.h"

CSerialEntity::CSerialEntity(CSerialEntity *pParent)
	:m_pName(nullptr), m_pTypeName(nullptr), m_Tag(0), m_pParent(pParent)
{
	if (m_pParent) m_pParent->m_Children.push_back(this);
}


CSerialEntity::~CSerialEntity(void)
{
	FreeNameString();
	FreeTypeNameString();

	FreeChildren();
	
	if (m_pParent) m_pParent->RemoveChild(this);
}

void CSerialEntity::SetReleaseStringFlag(bool flag)
{
	m_value.SetReleaseStringFlag(flag);
}

//method
ISerialEntity *CSerialEntity::NewChild(void)
{
	CSerialEntity *pEnt(new CSerialEntity(this));
	return pEnt;
}

void CSerialEntity::DelChild(ISerialEntity *pChild)
{
	std::vector<CSerialEntity*>::iterator itr;
	ISerialEntity *pIntfSE;
	for (itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		pIntfSE = *itr;
		if (pIntfSE == pChild)
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

//ISerialEntity *CSerialEntity::FindChild(const char *pName, unsigned int EntTypeId, TDUIntPtr Tag)
//{
//	return nullptr;
//}

ISerialEntity *CSerialEntity::FindChild(const char *pName, char *EntTypeName, TDUIntPtr Tag)
{
	std::vector<CSerialEntity*>::iterator itr;
	for (itr = m_Children.begin(); itr != m_Children.end(); ++itr)
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
	FreeNameString();
	if (pName)
	{
		m_pName = new char [strlen(pName) + 1];
		strcpy(m_pName, pName);
	}
}

const char *CSerialEntity::GetName(void)
{
	return m_pName;
}

//void CSerialEntity::SetEntTypeId(unsigned int iId)
//{
//}

//unsigned int CSerialEntity::GetEntTypeId(void)
//{
//	return 0;
//}

void CSerialEntity::SetEntTypeName(const char *pName)
{
	FreeTypeNameString();
	if (pName)
	{
		m_pTypeName = new char [strlen(pName) + 1];
		strcpy(m_pTypeName, pName);
	}
}

const char *CSerialEntity::GetEntTypeName(void)
{
	return m_pTypeName;
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

TDUIntPtr CSerialEntity::GetChildrenCount(void)
{
	return m_Children.size();
}

ISerialEntity *CSerialEntity::GetChildren(TDUIntPtr index)
{
	return m_Children[index];
}

void CSerialEntity::FreeNameString(void)
{
	if (m_pName)
	{
		delete [] m_pName;
		m_pName = nullptr;
	}
}

void CSerialEntity::FreeTypeNameString(void)
{
	if (m_pTypeName)
	{
		delete [] m_pTypeName;
		m_pTypeName = nullptr;
	}
}

void CSerialEntity::RemoveChild(CSerialEntity *pChild)
{
	std::vector<CSerialEntity*>::iterator itr;
	for (itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		if ((*itr) == pChild)
		{
			m_Children.erase(itr);
			break;
		}
	}
}

void CSerialEntity::FreeChildren(void)
{
	for (TDUIntPtr index = m_Children.size() - 1; index >= 0; --index)
	{
		delete m_Children[index];
	}
}