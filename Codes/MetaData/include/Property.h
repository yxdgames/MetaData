#pragma once
#include "..\..\include\CommonDefine.h"
#include <vector>

class CLASS_DESCRIPT IPropertyNotify;

/*---CPropertyBase---*/
class CLASS_DESCRIPT CPropertyBase
{
public:
	CPropertyBase(void) :m_pPropertyNotifications(new std::vector<IPropertyNotify*>) {}
	virtual ~CPropertyBase(void) { delete m_pPropertyNotifications; }
public:
	virtual void CallSet(void *pObj, void *value) = 0;
	virtual void CallGet(void *pObj, void *value) = 0;
	virtual void CallSet(void *value) {}
	virtual void CallGet(void *value) {}
	virtual bool ExistSet(void) = 0;
	virtual bool ExistGet(void) = 0;
	virtual size_t GetDataSize(void) = 0;
	virtual CPropertyBase *Clone(void) = 0;
public:
	void AddPropertyNotification(IPropertyNotify *pNotify);
	void DelPropertyNotification(IPropertyNotify *pNotify);
	void ClearNotification(void);
public:
	IPropertyNotify *GetPropertyNotification(size_t index) { return m_pPropertyNotifications->at(index); }
	size_t GetPropertyNotificationCount(void) { return m_pPropertyNotifications->size(); }
protected:
	void BeginSet(void *pObj, void *value);
	void EndSet(void *pObj, void *value);
	void BeginGet(void *pObj);
	void EndGet(void *pObj, void *value);
protected:
	inline CPropertyBase(CPropertyBase &src);
private:
	std::vector<IPropertyNotify*>	*m_pPropertyNotifications;
};

inline CPropertyBase::CPropertyBase(CPropertyBase &src)
	:m_pPropertyNotifications(new std::vector<IPropertyNotify*>(*src.m_pPropertyNotifications))
{
}

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
	virtual size_t GetDataSize(void) { return sizeof(T); }
	virtual CPropertyBase *Clone(void);
protected:
	inline TPropertyBase(TPropertyBase &src);
private:
	TPropertyBase(void) {}
private:
	const Tpfun_set	m_pSet;
	const Tpfun_get	m_pGet;
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
	return new TPropertyBase<CLASS, T>(*this);
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
	//attribute
	CLASS *GetObject(void) { return m_pObj; }
public:
	inline Property &operator =(T value);
	inline operator T();
protected:
	inline Property(Property &src);
private:
	Property(void) {}
private:
	CLASS		* const m_pObj;
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
	return new Property<CLASS, T>(*this);
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