#include "stdafx.h"
#include "..\include\ISerializer.h"

#include "..\include\Serializer.h"

ISerializer *ISerializer::CreateSerializerIntf(void)
{
	return new CSerializer;
}

//ISerializer
ISerializer::ISerializer(void)
{
}


ISerializer::~ISerializer(void)
{
}
