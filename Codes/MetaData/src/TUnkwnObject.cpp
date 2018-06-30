#include "stdafx.h"
#include "..\include\TUnkwnObject.h"
#include <winsync.h>

//CUnkwnObjLock
CUnkwnObjLock::CUnkwnObjLock(void)
	: m_pLockObject(new CRITICAL_SECTION)
{
	if (!::InitializeCriticalSectionAndSpinCount(reinterpret_cast<CRITICAL_SECTION*>(m_pLockObject), 0))
		throw new ExceptionBase(D_E_ID_ERROR, "InitializeCriticalSectionAndSpinCount Error!");
}

CUnkwnObjLock::~CUnkwnObjLock(void)
{
	::DeleteCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(m_pLockObject));
	delete reinterpret_cast<CRITICAL_SECTION*>(m_pLockObject);
}

void CUnkwnObjLock::Lock(void)
{
	::EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(m_pLockObject));
}

void CUnkwnObjLock::Unlock(void)
{
	::LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION*>(m_pLockObject));
}