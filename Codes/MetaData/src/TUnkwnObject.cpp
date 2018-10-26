#include "stdafx.h"
#include "..\include\TUnkwnObject.h"
#include <Windows.h>

//CUnkwnObjRefCountLock
CUnkwnObjRefCountLock::CUnkwnObjRefCountLock(void)
	: m_pLockObject(nullptr)
{
}

CUnkwnObjRefCountLock::~CUnkwnObjRefCountLock(void)
{
}

ULong CUnkwnObjRefCountLock::IncreaseRefCount(volatile ULong &refCount)
{
	return ::InterlockedIncrement(&refCount);
}

ULong CUnkwnObjRefCountLock::DecreaseRefCount(volatile ULong &refCount)
{
	return ::InterlockedDecrement(&refCount);
}
