#include "stdafx.h"
#include "..\include\ISerialStream.h"

#include "..\include\SerialStreamBinary.h"
#include "..\include\SerialStreamXml.h"

ISerialStream *ISerialStream::CreateSerialStreamIntf(ESerialStreamIntfType IntfType, std::iostream *pStream, bool hold_stream)
{
	switch(IntfType)
	{
	case ssitBin:
		return new CSerialStreamBinary(pStream, hold_stream);
	case ssitXml:
		return new CSerialStreamXml(pStream, hold_stream);
	default:
		return NULL;
	}
}

ISerialStream::ISerialStream(void)
{
}

ISerialStream::~ISerialStream(void)
{
}