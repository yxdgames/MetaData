#include "stdafx.h"
#include "..\include\InterfacedObject.h"

CInterfacedObject::CInterfacedObject(void)
{
}


CInterfacedObject::~CInterfacedObject(void)
{
}

bool CInterfacedObject::QueryInterface(char *pIntfName, IInterface **outIntf)
{
	return DoQueryInterface(this, pIntfName, outIntf);
}

