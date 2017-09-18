#pragma once

#include "..\..\include\CommonDefine.h"

class CLASS_DESCRIPT CPropertyBase
{
public:
	CPropertyBase(void)
		:m_pSet(nullptr), m_pGet(nullptr) {}
	~CPropertyBase(void) {}
public:
	virtual void CallSet(void *pObj, void *value) = 0;
	virtual void CallGet(void *pObj, void *value) = 0;
	bool ExistSet(void) { return m_pSet != nullptr; }
	bool ExistGet(void) { return m_pGet != nullptr; }
protected:
	void		*m_pSet;
	void		*m_pGet;
private:
	CPropertyBase(CPropertyBase&) {}
};

template <typename CLASS, typename T>
class CLASS_DESCRIPT TProperty : public CPropertyBase
{
	typedef void (CLASS::*Tpfun_set)(T value);
	typedef T (CLASS::*Tpfun_get)(void);
public:
	TProperty(CLASS *pObj, Tpfun_set set, Tpfun_get get);
	~TProperty(void) {}
public:
	virtual void CallSet(void *pObj, void *value);
	virtual void CallGet(void *pObj, void *value);
public:
	inline TProperty &operator =(T value);
	inline operator T();
private:
	TProperty(void) {}
	TProperty(TProperty&) {}
private:
	CLASS			*m_pObj;

private:
#if 0
	class CDebugCheck
	{
	public:
		CDebugCheck(void)
		{
			if (sizeof(void*) != sizeof(Tpfun_set) || sizeof(void*) != sizeof(Tpfun_get))
				throw ExceptionMetaData(D_E_ID_MD_ERROR, "属性类（类模板）丢失类成员函数指针数据！");
		}
	};
	static CDebugCheck m_DebugCheckObject;
#endif
};

//template <typename CLASS, typename T>
//TProperty<CLASS, T>::CDebugCheck TProperty<CLASS, T>::m_DebugCheckObject;

template <typename CLASS, typename T>
TProperty<CLASS, T>::TProperty(CLASS *pObj, Tpfun_set set, Tpfun_get get)
	:m_pObj(pObj)
{
	memcpy(&m_pSet, &set, sizeof(m_pSet));
	memcpy(&m_pGet, &get, sizeof(m_pGet));
}

template <typename CLASS, typename T>
void TProperty<CLASS, T>::CallSet(void *pObj, void *value)
{
	if (pObj && value && m_pSet)
	{
		Tpfun_set pfun_set;
		memcpy(&pfun_set, &m_pSet, sizeof(pfun_set));
		(reinterpret_cast<CLASS*>(pObj)->*pfun_set)(*reinterpret_cast<T*>(value));
	}
}

template <typename CLASS, typename T>
void TProperty<CLASS, T>::CallGet(void *pObj, void *value)
{
	if (pObj && value && m_pGet)
	{
		Tpfun_get pfun_get;
		memcpy(&pfun_get, &m_pGet, sizeof(pfun_get));
		*reinterpret_cast<T*>(value) = (reinterpret_cast<CLASS*>(pObj)->*pfun_get)();
	}
}

template <typename CLASS, typename T>
inline TProperty<CLASS, T> &TProperty<CLASS, T>::operator=(T value)
{
	this->CallSet(m_pObj, &value);
	return *this;
}

template <typename CLASS, typename T>
inline TProperty<CLASS, T>::operator T()
{
	T value;
	this->CallGet(m_pObj, &value);
	return value;
}