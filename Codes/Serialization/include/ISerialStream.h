#pragma once

#include "ISerial.h"
#include <iostream>

enum ESerialStreamIntfType
{
	ssitNone = 0,
	ssitBin,
	ssitXml,
};

class CLASS_DESCRIPT ISerialStream : public IInterface
{
public:
	ISerialStream(void);
	virtual ~ISerialStream(void) = 0;
public:
	//method
	virtual bool Serialize(ISerial *pSerial) = 0;
	virtual bool Unserialize(ISerial *pSerial) = 0;
public:
	//attribute

public:
	static ISerialStream *CreateSerialStreamIntf(ESerialStreamIntfType IntfType, std::iostream *pStream, bool hold_stream);
};