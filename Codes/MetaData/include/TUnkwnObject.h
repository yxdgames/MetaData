#pragma once

#include "IUnkwn.h"

template <typename _Base>
class TEMPLATE_CLASS_DESCRIPT TUnkwnObject : public _Base
{
public:
	TUnkwnObject(void) : m_refCount(0) {}
public:
	//IUnkwn
	virtual HResult IUNKWN_MEMFUN_DESCRIPT QueryInterface(REFIID riid, void **ppvObject);
	virtual ULong IUNKWN_MEMFUN_DESCRIPT AddRef(void) { return m_refCount++; }
	virtual ULong IUNKWN_MEMFUN_DESCRIPT Release(void);
private:
	TUnkwnObject(TUnkwnObject&) {}
	~TUnkwnObject(void) {}
private:
	ULong	m_refCount;
};

template <typename _Base>
HResult TUnkwnObject<_Base>::QueryInterface(REFIID riid, void **ppvObject)
{
	TDGUID type_guid(static_cast<const void*>(&riid));
	*ppvObject = this->GetType()->AsType(static_cast<_Base*>(this), type_guid);
	if (*ppvObject)
	{
		this->AddRef();
		return 0;
	}
	else return -1;
}

template <typename _Base>
ULong TUnkwnObject<_Base>::Release(void)
{
	--m_refCount;
	if (m_refCount == 0)
	{
		delete this;
	}
}
