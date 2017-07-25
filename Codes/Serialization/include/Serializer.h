#pragma once

#include "ISerializer.h"
#include "ITreeSerial.h"

class CSerializer : public ISerializer
{
public:
	CSerializer(void);
	virtual ~CSerializer(void);
public:
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf)
	{
		return nullptr;
	}
	//ISerializer
	//method
	//atrribute
	virtual ISerial *GetSerial(void)			{ return m_pTreeSerial; }
	virtual void SetSerial(ISerial *pSerial);
protected:
	//ISerializer
	//method
	virtual bool DoSerialize(CMetaDataType *pType, void *pObj, const char *pName);
	virtual bool DoUnserialize(CMetaDataType *pType, void *pObj, const char *pName);
private:
	bool SerializeCustomTypeWrapper(CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, unsigned int EntTag);
	bool SerializeCustomType(CMetaDataCustomType *pType, void *pObj, ISerialEntity *pSEntity, unsigned int EntTag);
	bool SerializeInnerType(CMetaDataInnerType *pType, void *pObj, ISerialEntity *pSEntity);
	bool UnserializeCustomTypeWrapper(ISerialEntity *pSEntity, CMetaDataCustomType *pType, void *pObj, unsigned int EntTag);
	bool UnserializeCustomType(ISerialEntity *pSEntity, CMetaDataCustomType *pType, void *pObj, unsigned int EntTag);
	bool UnserializeInnerType(ISerialEntity *pSEntity, CMetaDataInnerType *pType, void *pObj);
	
	void *NewObject(CMetaDataType *pType);
private:
	ITreeSerial				*m_pTreeSerial;
};

