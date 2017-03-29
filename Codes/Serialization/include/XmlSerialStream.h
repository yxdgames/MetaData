#pragma once

#include "ISerialStream.h"
#include "ISerialEntity.h"

class CXmlSerialStream : public ISerialStream
{
public:
	CXmlSerialStream(std::iostream *pStream, bool hold_stream);
	virtual ~CXmlSerialStream(void);
public:
	//
public:
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf)	{ return NULL; }
	//ISerialStream
	//method
	virtual bool Serialize(ISerial *pSerial);
	virtual bool Unserialize(ISerial *pSerial);
private:
	bool DoSerialize(ISerialEntity *pEnt, char *pBuff);
private:
	bool m_HoldStream;
	std::iostream *m_pStream;
};

