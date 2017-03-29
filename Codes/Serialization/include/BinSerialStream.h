#pragma once

#include "ISerialStream.h"
#include "ISerialEntity.h"
#include "..\include\EntityBinaryFileStructure.h"

class CBinSerialStream : public ISerialStream
{
public:
	CBinSerialStream(std::iostream *pStream, bool hold_stream);
	virtual ~CBinSerialStream(void);
public:
	//
public:
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf)
	{
		return NULL;
	}
	//ISerialStream
	//method
	virtual bool Serialize(ISerial *pSerial);
	virtual bool Unserialize(ISerial *pSerial);
private:
	struct SStringFilePositionList
	{
	public:
		struct SStringFilePositions
		{
			char *str;
			std::vector<TypeBaseUnit> positions;
		};
	public:
		SStringFilePositions *FindItem(const char *pString, bool bNew);
	public:
		std::vector<SStringFilePositions> info_vector;
	};
private:
	void SerialInit(void);
	bool SerializeEntity(ISerialEntity *pEnt, unsigned long &EntSize);
	bool SerializeStringTable(void);
	void UnserialInit(void);
	bool UnserializeEntity(ISerialEntity *pEnt, unsigned long &EntSize);
private:
	bool m_HoldStream;
	std::iostream *m_pStream;
	TypeBaseUnit m_StreamPosition;
	SStringFilePositionList m_StringFilePositionList;
};

