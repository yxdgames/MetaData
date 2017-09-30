#pragma once

#include "ISerializer.h"
#include "ITreeSerial.h"
#include "..\..\MetaData\include\IInterfaceDefaultImp.h"

#define D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX			(256)

class CLASS_DESCRIPT CSerializer : public ISerializer
{
public:
	CSerializer(void);
	virtual ~CSerializer(void);
public:
	//IInterface
	D_IMPLEMENT_IINTERFACE_MEMBER
	//ISerializer
	//method
	//atrribute
	virtual ISerial *GetSerial(void)			{ return m_pTreeSerial; }
	virtual void SetSerial(ISerial *pSerial);
protected:
	//ISerializer
	//method
	virtual bool DoSerialize(const CMetaDataType *pType, void *pObj, const char *pName);
	virtual bool DoUnserialize(const CMetaDataType *pType, void *pObj, const char *pName);
private:
	bool SerializeCustomTypeWrapper(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX]);
	bool SerializeCustomType(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX]);
	bool SerializeInnerType(const CMetaDataInnerType *pType, void *pObj, ISerialEntity *pSEntity);
	bool UnserializeCustomTypeWrapper(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX]);
	bool UnserializeCustomType(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj, char strBuffer[D_SERIALIZER_H_STRING_BUFFER_SIZE_MAX]);
	bool UnserializeInnerType(ISerialEntity *pSEntity, const CMetaDataInnerType *pType, void *pObj);
private:
	inline const CMetaDataType *FindMetaDataType(const char *pTypeName);
private:
	ITreeSerial				*m_pTreeSerial;
};

