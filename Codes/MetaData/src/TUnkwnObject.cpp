#include "stdafx.h"
#include "../include/TUnkwnObject.h"
#if defined(CO_OS_WIN)
#include <Windows.h>
#elif defined(CO_OS_LINUX)
#include <mutex>
#else
// Unknown
#endif

//CUnkwnObjRefCountLock
CUnkwnObjRefCountLock::CUnkwnObjRefCountLock(void)
	:
#if defined(CO_OS_WIN)
	m_pLockObject(nullptr)
#elif defined(CO_OS_LINUX)
	m_pLockObject(new std::mutex)
#else
	m_pLockObject(nullptr)
#endif
{
}

CUnkwnObjRefCountLock::~CUnkwnObjRefCountLock(void)
{
#ifdef CO_OS_LINUX
	delete reinterpret_cast<std::mutex*>(m_pLockObject);
#endif
}

ULong CUnkwnObjRefCountLock::IncreaseRefCount(volatile ULong &refCount)
{
#if defined(CO_OS_WIN)
	return ::InterlockedIncrement(&refCount);
#elif defined(CO_OS_LINUX)
	std::lock_guard<std::mutex> _lck(*reinterpret_cast<std::mutex*>(m_pLockObject));
	++refCount;
	return refCount;
#else
	return -1;
#endif
}

ULong CUnkwnObjRefCountLock::DecreaseRefCount(volatile ULong &refCount)
{
#if defined(CO_OS_WIN)
	return ::InterlockedDecrement(&refCount);
#elif defined(CO_OS_LINUX)
	std::lock_guard<std::mutex> _lck(*reinterpret_cast<std::mutex*>(m_pLockObject));
	--refCount;
	return refCount;
#else
	return -1;
#endif
}
