#pragma once

#include "ISerialStream.h"
#include "ISerialEntity.h"
#include "..\include\EntityBinaryFileStructure.h"
#include "..\..\MetaData\include\IInterfaceDefaultImp.h"

class CLASS_DESCRIPT CSerialStreamBinary : public ISerialStream
{
public:
	CSerialStreamBinary(std::iostream *pStream, bool hold_stream);
	virtual ~CSerialStreamBinary(void);
public:
	//IInterface
	D_IMPLEMENT_IINTERFACE_MEMBER_NO_METADATA
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
		inline SStringFilePositions *FindItem(const char *pString, bool bNew);
	public:
		std::vector<SStringFilePositions> info_vector;
	};
	struct SBlobFilePositionList
	{
	public:
		struct SBlobFilePosition
		{
			IBlob *pBlob;
			std::vector<TDBinBaseUnit> posistions;
		};
	public:
		inline SBlobFilePosition *FindItem(IBlob *pBlob, bool bNew);
	public:
		std::vector<SBlobFilePosition> info_vector;
	};
private:
	void SerialInit(void);
	size_t SerializeEntity(ISerialEntity *pEnt);
	bool SerializeStringTable(void);
	bool SerializeBlob(void);
	void UnserialInit(void);
	size_t UnserializeEntity(ISerialEntity *pEnt, ISerial *pSerial);
private:
	bool m_HoldStream;
	std::iostream *m_pStream;
	TDBinBaseUnit m_StreamPosition;
	SStringFilePositionList m_StringFilePositionList;
	SBlobFilePositionList m_BlobFilePositionList;
};

