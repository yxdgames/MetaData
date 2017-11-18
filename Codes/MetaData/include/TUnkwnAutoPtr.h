#pragma once

template <typename IU>
class TUnkwnAutoPtr
{
public:
	TUnkwnAutoPtr(void) : m_pUnkwn(nullptr) {}
	inline TUnkwnAutoPtr(IU *pUnkwn, bool bAutoInc = true);
	inline TUnkwnAutoPtr(TUnkwnAutoPtr &auto_ptr);
	inline ~TUnkwnAutoPtr(void);
public:
	inline operator IU*(void);
	inline IU *operator=(IU *pUnkwn);
	inline IU *operator=(TUnkwnAutoPtr &auto_ptr);
	inline IU *operator->(void);
private:
	IU		*m_pUnkwn;
};


template <typename IU>
inline TUnkwnAutoPtr<IU>::TUnkwnAutoPtr(IU *pUnkwn, bool bAutoInc)
	:m_pUnkwn(pUnkwn)
{
	if (bAutoInc && m_pUnkwn) m_pUnkwn->AddRef();
}

template <typename IU>
inline TUnkwnAutoPtr<IU>::TUnkwnAutoPtr(TUnkwnAutoPtr &auto_ptr)
	:m_pUnkwn(auto_ptr.m_pUnkwn)
{
	if (m_pUnkwn) m_pUnkwn->AddRef();
}

template <typename IU>
inline TUnkwnAutoPtr<IU>::~TUnkwnAutoPtr()
{
	if (m_pUnkwn) m_pUnkwn->Release();
}

template <typename IU>
inline TUnkwnAutoPtr<IU>::operator IU*(void)
{
	return m_pUnkwn;
}

template <typename IU>
inline IU *TUnkwnAutoPtr<IU>::operator=(IU *pUnkwn)
{
	if (m_pUnkwn) m_pUnkwn->Release();
	m_pUnkwn = pUnkwn;
	if (m_pUnkwn) m_pUnkwn->AddRef();
	return m_pUnkwn;
}

template <typename IU>
inline IU *TUnkwnAutoPtr<IU>::operator=(TUnkwnAutoPtr &auto_ptr)
{
	if (m_pUnkwn) m_pUnkwn->Release();
	m_pUnkwn = auto_ptr.m_pUnkwn;
	if (m_pUnkwn) m_pUnkwn->AddRef();
	return m_pUnkwn;
}

template <typename IU>
inline IU *TUnkwnAutoPtr<IU>::operator->(void)
{
	return m_pUnkwn;
}