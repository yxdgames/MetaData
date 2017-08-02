#pragma once

#include "..\..\MetaData\include\IInterface.h"
#include "SVariant.h"

class ISerialEntity : public IInterface
{
public:
	ISerialEntity(void);
	virtual ~ISerialEntity(void) = 0;
public:
	//method
	virtual ISerialEntity *NewChild(void) = 0;
	virtual void DelChild(ISerialEntity *pChild) = 0;
	virtual void ClearChildren(void) = 0;
	virtual ISerialEntity *FindChild(const char *pName, unsigned int EntTypeId, unsigned int Tag) = 0;
	virtual ISerialEntity *FindChild(const char *pName, char *EntTypeName, unsigned int Tag) = 0;
public:
	//attribute
	virtual void SetName(const char *pName) = 0;
	virtual const char *GetName(void) = 0;

	virtual void SetEntTypeName(const char *pName) = 0;
	virtual const char *GetEntTypeName(void) = 0;

	virtual void SetTag(unsigned int Tag) = 0;
	virtual unsigned int GetTag(void) = 0;

	virtual void SetValue(const char *pValue) = 0;
	virtual void SetValue(const int Value) = 0;
	virtual void SetValue(const long long Value) = 0;
	virtual void SetValue(const long double Value) = 0;
	virtual void SetValue(const bool Value) = 0;
	virtual SVariant &GetValue(void) = 0;

	virtual ISerialEntity *GetParent(void) = 0;
	virtual unsigned int GetChildrenCount(void) = 0;
	virtual ISerialEntity *GetChildren(unsigned int index) = 0;

public:
	static ISerialEntity *CreateSerialEntityIntf(void);
};
