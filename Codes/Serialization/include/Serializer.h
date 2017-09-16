#pragma once

#include "ISerializer.h"
#include "ITreeSerial.h"
#include "..\..\MetaData\include\IInterfaceDefaultImp.h"

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
	bool SerializeCustomTypeWrapper(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity);
	bool SerializeCustomType(const CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity);
	bool SerializeInnerType(const CMetaDataInnerType *pType, void *pObj, ISerialEntity *pSEntity);
	bool UnserializeCustomTypeWrapper(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj);
	bool UnserializeCustomType(ISerialEntity *pSEntity, const CMetaDataCustomType *pType, void *pObj);
	bool UnserializeInnerType(ISerialEntity *pSEntity, const CMetaDataInnerType *pType, void *pObj);
	
	void *NewObject(const CMetaDataType *pType);
private:
	ITreeSerial				*m_pTreeSerial;
};

