#pragma once

#include "ISerialStream.h"
#include "ISerialEntity.h"
#include "..\include\EntityBinaryFileStructure.h"

class CSerialStreamBinary : public ISerialStream
{
public:
	CSerialStreamBinary(std::iostream *pStream, bool hold_stream);
	virtual ~CSerialStreamBinary(void);
public:
	//
public:
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf)
	{
		return nullptr;
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
			const char *str;
			std::vector<TDBinBaseUnit> positions;
		};
	public:
		SStringFilePositions *FindItem(const char *pString, bool bNew);
	public:
		std::vector<SStringFilePositions> info_vector;
	};
private:
	void SerialInit(void);
	bool SerializeEntity(ISerialEntity *pEnt, size_t &EntSize);
	bool SerializeStringTable(void);
	void UnserialInit(void);
	bool UnserializeEntity(ISerialEntity *pEnt, size_t &EntSize);
private:
	bool m_HoldStream;
	std::iostream *m_pStream;
	TDBinBaseUnit m_StreamPosition;
	SStringFilePositionList m_StringFilePositionList;
};

