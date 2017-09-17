#pragma once

#include "..\..\include\CommonDefine.h"

template <typename CLASS, typename T>
class CLASS_DESCRIPT TPropertyBase
{
public:
	typedef void (CLASS::*Tpfun_set)(T value);
	typedef T (CLASS::*Tpfun_get)(void);
public:
	TPropertyBase(Tpfun_set set, Tpfun_get get)
		:m_pSet(set), m_pGet(get) {}
	~TPropertyBase(void) {}
public:
	inline void CallSet(CLASS *pObj, T value);
	inline T CallGet(CLASS *pObj);
	bool ExistSet(void) { return m_pSet; }
	bool ExistGet(void) { return m_pGet; }
protected:
	Tpfun_set		m_pSet;
	Tpfun_get		m_pGet;
private:
	TPropertyBase(void) {}
	TPropertyBase(TPropertyBase&) {}
};

template <typename CLASS, typename T>
inline void TPropertyBase<CLASS, T>::CallSet(CLASS *pObj, T value)
{
	if (pObj && m_pSet) (pObj->*m_pSet)(value);
}

template <typename CLASS, typename T>
inline T TPropertyBase<CLASS, T>::CallGet(CLASS *pObj)
{
	if (pObj && m_pGet)
		return (pObj->*m_pGet)();
	else return T();
}

template <typename CLASS, typename T>
class CLASS_DESCRIPT TProperty : public TPropertyBase<CLASS, T>
{
public:
	TProperty(CLASS *pObj, Tpfun_set set, Tpfun_get get)
		:TPropertyBase<CLASS, T>(set, get), m_pObj(pObj) {}
	~TProperty(void) {}
public:
	inline TProperty &operator =(T value);
	inline operator T();
private:
	TProperty(void) {}
	TProperty(TProperty&) {}
private:
	CLASS			*m_pObj;
};

template <typename CLASS, typename T>
inline TProperty<CLASS, T> &TProperty<CLASS, T>::operator=(T value)
{
	this->CallSet(m_pObj, value);
	return *this;
}

template <typename CLASS, typename T>
inline TProperty<CLASS, T>::operator T()
{
	return this->CallGet(m_pObj);
}