#pragma once
#include "ISerialEntity.h"
#include "../../MetaData/include/IInterfaceDefaultImp.h"
#include <vector>

class CLASS_DESCRIPT CSerialEntity : public ISerialEntity
{
public:
	CSerialEntity(CSerialEntity *pParent);
	virtual ~CSerialEntity(void);
public:
	//IInterface
	D_IMPLEMENT_IINTERFACE_MEMBER_NO_METADATA
	//ISerialEntity
	//method
	virtual ISerialEntity *NewChild(void);
	virtual void DelChild(ISerialEntity *pChild);
	virtual void ClearChildren(void);
	virtual ISerialEntity *FindChild(const char *pName, char *EntTypeName, TDUIntPtr Tag);
	//attribute
	virtual void SetName(const char *pName);
	virtual const char *GetName(void);
	virtual void SetEntTypeName(const char *pName);
	virtual const char *GetEntTypeName(void);
	virtual void SetTag(TDUIntPtr Tag);
	virtual TDUIntPtr GetTag(void);
	virtual void SetValue(const bool Value);
	virtual void SetValue(const int Value);
	virtual void SetValue(const long long Value);
	virtual void SetValue(const double Value);
	virtual void SetValue(const long double Value);
	virtual void SetValue(const char * const pValue);
	virtual void SetValue(IBlob *pBlob, bool release_flag = false);
	virtual SVariant &GetValue(void);

	virtual ISerialEntity *GetParent(void);
	virtual size_t GetChildrenCount(void);
	virtual ISerialEntity *GetChildren(size_t index);
private:
	void RemoveChild(CSerialEntity *pChild);
	void FreeChildren(void);
private:
	std::string *m_pName;
	std::string *m_pTypeName;
	TDUIntPtr m_Tag;
	SVariant m_value;

	CSerialEntity *m_pParent;
	std::vector<CSerialEntity*> *m_pChildren;
};

