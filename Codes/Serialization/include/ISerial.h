#pragma once
#include "../../MetaData/include/IInterface.h"
#include <iostream>

enum EStructureInStream
{
	sisNone = 0,
	sisBin,
	sisXml,
	ssiMax,
};

class CLASS_DESCRIPT ISerial : public IInterface
{
public:
	ISerial(void);
	virtual ~ISerial(void) = 0;
public:
	//method
	virtual void Clear(void) = 0;
	virtual bool SaveToStream(std::iostream &stream) = 0;
	virtual bool LoadFromStream(std::iostream &stream) = 0;
	virtual bool SaveToFile(const char *pFileName) = 0;
	virtual bool LoadFromFile(const char *pFileName) = 0;
	virtual void DebugPrintSelf(void) = 0;
public:
	//attribute
	virtual EStructureInStream GetStructInStream(void) = 0;
	virtual void SetStructInStream(EStructureInStream value) = 0;

public:
	static ISerial *CreateSerialIntf(void);

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(ISerial)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(ISerial)
	// { FA3749C1-B595-42A9-A88D-A45BB83DCF36 }
	MD_INTERFACE_GUID_DEF(0xfa3749c1, 0xb595, 0x42a9, 0xa8, 0x8d, 0xa4, 0x5b, 0xb8, 0x3d, 0xcf, 0x36)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(ISerial)
};

