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
	MD_INTERFACE_INTERFACE_DEF(ISerial)
MD_INTERFACE_DECLARE_END(ITreeSerial)
};

