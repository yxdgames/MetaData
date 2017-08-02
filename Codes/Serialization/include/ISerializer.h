#pragma once

#include "..\..\MetaData\include\IInterface.h"
#include "ISerial.h"

class ISerializer : public IInterface
{
public:
	ISerializer(void);
	virtual ~ISerializer(void) = 0;
public:
	template <typename T>
	bool Serialize(T *pObj, const char *pName)
	{
		return DoSerialize(TypeTraits<T>::GetMetaDataType(pObj), pObj, pName);
	}
	template <typename T>
	bool Unserialize(const char *pName, T **pObj)
	{
		if (!pObj) return false;
		if (!(*pObj)) *pObj = new T;
		return DoUnserialize(TypeTraits<T>::GetMetaDataType(*pObj), reinterpret_cast<void*>(*pObj), pName);
	}
public:
	//method
public:
	//attribute
	virtual ISerial *GetSerial(void) = 0;
	virtual void SetSerial(ISerial *pSerial) = 0;
protected:
	//method
	virtual bool DoSerialize(const CMetaDataType *pType, void *pObj, const char *pName) = 0;
	virtual bool DoUnserialize(const CMetaDataType *pType, void *pObj, const char *pName) = 0;

public:
	static ISerializer *CreateSerializerIntf(void);
};

