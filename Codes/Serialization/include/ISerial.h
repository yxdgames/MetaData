#pragma once

#include "..\..\MetaData\include\IInterface.h"
#include <iostream>

enum EStructureInStream
{
	sisNone = 0,
	sisBin,
	sisXml,
	ssiMax,
};

class ISerial : public IInterface
{
public:
	ISerial(void);
	virtual ~ISerial(void) = 0;
public:
	//method
	virtual bool SaveToStream(std::iostream &stream) = 0;
	virtual bool LoadFromStream(std::iostream &stream) = 0;
	virtual bool SaveToFile(char *pFileName) = 0;
	virtual bool LoadFromFile(char *pFileName) = 0;
	virtual void DebugPrintSelf(void) = 0;
public:
	//attribute
	virtual EStructureInStream GetStructInStream(void) = 0;
	virtual void SetStructInStream(EStructureInStream value) = 0;
public:
	static ISerial *CreateSerialIntf(void);

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(ISerial)
MD_INTERFACE_DECLARE_DETAIL(ISerial)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(ISerial)
};

