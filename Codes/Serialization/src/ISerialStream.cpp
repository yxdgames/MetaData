#include "stdafx.h"
#include "..\include\ISerialStream.h"

#include "..\include\BinSerialStream.h"
#include "..\include\XmlSerialStream.h"

ISerialStream *ISerialStream::CreateSerialStreamIntf(ESerialStreamIntfType IntfType, std::iostream *pStream, bool hold_stream)
{
	switch(IntfType)
	{
	case ssitBin:
		return new CBinSerialStream(pStream, hold_stream);
	case ssitXml:
		return new CXmlSerialStream(pStream, hold_stream);
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