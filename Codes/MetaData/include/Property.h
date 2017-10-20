#pragma once
#include "..\..\include\CommonDefine.h"

class IPropertyNotify;

/*---CPropertyBase---*/
class CLASS_DESCRIPT CPropertyBase
{
public:
	CPropertyBase(void) :m_pPropertyNotify(nullptr) {}
	virtual ~CPropertyBase(void) {}
public:
	virtual void CallSet(void *pObj, void *value) = 0;
	virtual void CallGet(void *pObj, void *value) = 0;
	virtual void CallSet(void *value) {}
	virtual void CallGet(void *value) {}
	virtual bool ExistSet(void) = 0;
	virtual bool ExistGet(void) = 0;
	virtual CPropertyBase *Clone(void) = 0;
public:
	void SetPropertyNotify(IPropertyNotify *value) { m_pPropertyNotify = value; }
protected:
	void BeginSet(void *pObj, void *value);
	void EndSet(void *pObj, void *value);
	void BeginGet(void *pObj);
	void EndGet(void *pObj, void *value);
protected:
	CPropertyBase(CPropertyBase &src) :m_pPropertyNotify(src.m_pPropertyNotify) {}
private:
	IPropertyNotify		*m_pPropertyNotify;
};

/*---TPropertyBase---*/
template <typename CLASS, typename T>
class TEMPLATE_CLASS_DESCRIPT TPropertyBase : public CPropertyBase
{
public:
	typedef void (CLASS::*Tpfun_set)(T value);
	typedef T (CLASS::*Tpfun_get)(void);
public:
	inline TPropertyBase(Tpfun_set set, Tpfun_get get);
	virtual ~TPropertyBase(void) {}
public:
	//override
	virtual void CallSet(void *pObj, void *value);
	virtual void CallGet(void *pObj, void *value);
	virtual bool ExistSet(void) { return m_pSet != nullptr; }
	virtual bool ExistGet(void) { return m_pGet != nullptr; }
	virtual CPropertyBase *Clone(void);
protected:
	inline TPropertyBase(TPropertyBase &src);
private:
	TPropertyBase(void) {}
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
		this->BeginSet(pObj, value);
		(reinterpret_cast<CLASS*>(pObj)->*m_pSet)(*reinterpret_cast<T*>(value));
		this->EndSet(pObj, value);
	}
}

template <typename CLASS, typename T>
void TPropertyBase<CLASS, T>::CallGet(void *pObj, void *value)
{
	if (pObj && value && m_pGet)
	{
		this->BeginGet(pObj);
		*reinterpret_cast<T*>(value) = (reinterpret_cast<CLASS*>(pObj)->*m_pGet)();
		this->EndGet(pObj, value);
	}
}

template <typename CLASS, typename T>
CPropertyBase *TPropertyBase<CLASS, T>::Clone(void)
{
	TPropertyBase<CLASS, T> *pProperty(new TPropertyBase<CLASS, T>(*this));
	return pProperty;
}

template <typename CLASS, typename T>
inline TPropertyBase<CLASS, T>::TPropertyBase(TPropertyBase &src)
	:CPropertyBase(src), m_pSet(src.m_pSet), m_pGet(src.m_pGet)
{
}

/*---Property---*/
template <typename CLASS, typename T>
class TEMPLATE_CLASS_DESCRIPT Property : public TPropertyBase<CLASS, T>
{
public:
	Property(CLASS *pObj, Tpfun_set set, Tpfun_get get)
		: TPropertyBase<CLASS, T>(set, get), m_pObj(pObj) {}
	virtual ~Property(void) {}
public:
	//override
	virtual inline void CallSet(void *value);
	virtual inline void CallGet(void *value);
	virtual CPropertyBase *Clone(void);
public:
	inline Property &operator =(T value);
	inline operator T();
private:
	Property(void) {}
	Property(Property &src);
private:
	CLASS			*m_pObj;
};

template <typename CLASS, typename T>
inline void Property<CLASS, T>::CallSet(void *value)
{
	this->TPropertyBase<CLASS, T>::CallSet(m_pObj, value);
}

template <typename CLASS, typename T>
inline void Property<CLASS, T>::CallGet(void *value)
{
	this->TPropertyBase<CLASS, T>::CallGet(m_pObj, value);
}

template <typename CLASS, typename T>
CPropertyBase *Property<CLASS, T>::Clone(void)
{
	Property<CLASS, T> *pProperty(new Property<CLASS, T>(*this));
	return pProperty;
}

template <typename CLASS, typename T>
inline Property<CLASS, T> &Property<CLASS, T>::operator=(T value)
{
	this->CallSet(&value);
	return *this;
}

template <typename CLASS, typename T>
inline Property<CLASS, T>::operator T()
{
	T value;
	this->CallGet(&value);
	return value;
}

template <typename CLASS, typename T>
inline Property<CLASS, T>::Property(Property &src)
	:TPropertyBase<CLASS, T>(src), m_pObj(src.m_pObj)
{
}