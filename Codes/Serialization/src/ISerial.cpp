#include "stdafx.h"
#include "../include/ISerial.h"
#include "../include/TreeSerial.h"

ISerial *ISerial::CreateSerialIntf(void)
{
	return new CTreeSerial;
}

ISerial::ISerial(void)
{
}


ISerial::~ISerial(void)
{
}
