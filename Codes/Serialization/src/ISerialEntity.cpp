#include "stdafx.h"
#include "..\include\ISerialEntity.h"

#include "..\include\SerialEntity.h"

ISerialEntity *ISerialEntity::CreateSerialEntityIntf(void)
{
	return new CSerialEntity(NULL);
}

ISerialEntity::ISerialEntity(void)
{
}


ISerialEntity::~ISerialEntity(void)
{
}
