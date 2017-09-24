#pragma once
#include "..\..\include\CommonDefine.h"

/*---CPropertyBase---*/
class CLASS_DESCRIPT CPropertyBase
{
public:
	CPropertyBase(void) {}
	virtual ~CPropertyBase(void) {}
public:
	virtual void CallSet(void *pObj, void *value) = 0;
	virtual void CallGet(void *pObj, void *value) = 0;
	virtual bool ExistSet(void) = 0;
	virtual bool ExistGet(void) = 0;
private:
	CPropertyBase(CPropertyBase&) {}
};

/*---TPropertyBase---*/
template <typename CLASS, typename T>
class TEMPLATE_CLASS_DESCRIPT TPropertyBase : public CPropertyBase
{
public:
	typedef void (CLASS::*Tpfun_set)(const T value);
	typedef const T (CLASS::*Tpfun_get)(void);
public:
	inline TPropertyBase(Tpfun_set set, Tpfun_get get);
	virtual ~TPropertyBase(void) {}
public:
	virtual void CallSet(void *pObj, void *value);
	virtual void CallGet(void *pObj, void *value);
	virtual bool ExistSet(void) { return m_pSet != nullptr; }
	virtual bool ExistGet(void) { return m_pGet != nullptr; }
private:
	TPropertyBase(void) {}
	TPropertyBase(TPropertyBase&) {}
private:
	Tpfun_set	m_pSet;
	Tpfun_get	m_pGet;
};

template <typename CLASS, typename T>
inline TPropertyBase<CLASS, T>::TPropertyBase(Tpfun_set set, Tpfun_get get)
	: m_pSet(set), m_pGet(get)
{
}

template <typename CLASS, typename T>
void TPropertyBase<CLASS, T>::CallSet(void *pObj, void *value)
{
	if (pObj && value && m_pSet)
	{
		(reinterpret_cast<CLASS*>(pObj)->*m_pSet)(*reinterpret_cast<T*>(value));
	}
}

template <typename CLASS, typename T>
void TPropertyBase<CLASS, T>::CallGet(void *pObj, void *value)
{
	if (pObj && value && m_pGet)
	{
		*reinterpret_cast<T*>(value) = (reinterpret_cast<CLASS*>(pObj)->*m_pGet)();
	}
}

/*---Property---*/
template <typename CLASS, typename T>
class TEMPLATE_CLASS_DESCRIPT Property : public TPropertyBase<CLASS, T>
{
public:
	Property(CLASS *pObj, Tpfun_set set, Tpfun_get get)
		: TPropertyBase<CLASS, T>(set, get), m_pObj(pObj){}
	virtual ~Property(void) {}
public:
	inline Property &operator =(T value);
	inline operator T();
private:
	Property(void) {}
	Property(Property&) {}
private:
	CLASS			*m_pObj;
};

template <typename CLASS, typename T>
inline Property<CLASS, T> &Property<CLASS, T>::operator=(T value)
{
	this->CallSet(m_pObj, &value);
	return *this;
}

template <typename CLASS, typename T>
inline Property<CLASS, T>::operator T()
{
	T value;
	this->CallGet(m_pObj, &value);
	return value;
}