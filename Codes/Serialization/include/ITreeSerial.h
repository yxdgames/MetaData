#pragma once

#include "ISerial.h"
#include "ISerialEntity.h"

class CLASS_DESCRIPT ITreeSerial : public ISerial
{
public:
	ITreeSerial(void);
	virtual ~ITreeSerial(void) = 0;
public:
	virtual ISerialEntity *Root(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(ITreeSerial)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(ITreeSerial)
	// { 515B785E-66CC-4877-B507-6881B0A7748A }
	MD_INTERFACE_GUID_DEF(0x515b785e, 0x66cc, 0x4877, 0xb5, 0x7, 0x68, 0x81, 0xb0, 0xa7, 0x74, 0x8a)
	MD_INTERFACE_INTERFACE_DEF(ISerial)
MD_INTERFACE_DECLARE_END(ITreeSerial)
};

