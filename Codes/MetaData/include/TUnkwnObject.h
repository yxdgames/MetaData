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
	virtual ULong IUNKWN_MEMFUN_DESCRIPT AddRef(void) { return ++m_refCount; }
	virtual ULong IUNKWN_MEMFUN_DESCRIPT Release(void);
private:
	TUnkwnObject(TUnkwnObject&) {}
	~TUnkwnObject(void) {}
private:
	ULong	m_refCount;
};

#define HR_OK				(0x00000000L)
#define HR_E_NOIUNKWN		(0x80004002L)

template <typename _Base>
HResult TUnkwnObject<_Base>::QueryInterface(REFIID riid, void **ppvObject)
{
	TDGUID type_guid(static_cast<const void*>(&riid));
	if (reinterpret_cast<const CMetaDataCustomType*>(this->GetType())->QueryUnknownInterface(this->GetTrueSelf(), type_guid, ppvObject))
	{
		reinterpret_cast<IUnkwn*>(*ppvObject)->AddRef();
		return HR_OK;
	}
	else return HR_E_NOIUNKWN;
}

template <typename _Base>
ULong TUnkwnObject<_Base>::Release(void)
{
	ULong refCount(--m_refCount);
	if (refCount == 0)
	{
		delete this;
	}
	return refCount;
}

//for compiling static library
extern void TUnkwnObject_Dummy_Func(void);