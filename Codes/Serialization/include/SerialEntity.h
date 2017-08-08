#pragma once
#include "ISerialEntity.h"
#include <vector>

class CSerialEntity : public ISerialEntity
{
public:
	CSerialEntity(CSerialEntity *pParent);
	virtual ~CSerialEntity(void);
public:
	void SetReleaseStringFlag(bool flag);
public:
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf)
	{
		return nullptr;
	}
	//ISerialEntity
	//method
	virtual ISerialEntity *NewChild(void);
	virtual void DelChild(ISerialEntity *pChild);
	virtual void ClearChildren(void);
	//virtual ISerialEntity *FindChild(const char *pName, TDUIntPtr EntTypeId, TDUIntPtr Tag);
	virtual ISerialEntity *FindChild(const char *pName, char *EntTypeName, TDUIntPtr Tag);

	//attribute
	virtual void SetName(const char *pName);
	virtual const char *GetName(void);

	//virtual void SetEntTypeId(TDUIntPtr iId);
	//virtual TDUIntPtr GetEntTypeId(void);

	virtual void SetEntTypeName(const char *pName);
	virtual const char *GetEntTypeName(void);

	virtual void SetTag(TDUIntPtr Tag);
	virtual TDUIntPtr GetTag(void);

	virtual void SetValue(const char *pValue);
	virtual void SetValue(const int Value);
	virtual void SetValue(const long long Value);
	virtual void SetValue(const long double Value);
	virtual void SetValue(const bool Value);
	virtual SVariant &GetValue(void);

	virtual ISerialEntity *GetParent(void);
	virtual TDUIntPtr GetChildrenCount(void);
	virtual ISerialEntity *GetChildren(TDUIntPtr index);
private:
	void FreeNameString(void);
	void FreeTypeNameString(void);
	void RemoveChild(CSerialEntity *pChild);
	void FreeChildren(void);
private:
	char *m_pName;
	char *m_pTypeName;
	TDUIntPtr m_Tag;
	SVariant m_value;

	CSerialEntity *m_pParent;
	std::vector<CSerialEntity*>	m_Children;
};

