#pragma once
#include "ExceptionBase.h"
#include "ExceptionID.h"

template <typename T>
class TEMPLATE_CLASS_DESCRIPT TArray
{
public:
	TArray(void) : m_pArray(nullptr), m_Size(0) {}
	inline TArray(const size_t size);
	inline TArray(T *&&array, const size_t size);
	inline TArray(TArray &&src);
	inline ~TArray(void);
public:
	void Reset(const size_t size, bool allow_greater = false);
public:
	T *array(void) { return m_pArray; }
	size_t array_size(void) { return m_Size; }
public:
	inline T &operator[](size_t index);
	inline TArray &operator=(TArray &src);
	inline TArray &operator=(TArray &&src);
private:
	TArray(TArray&) {}
private:
	T *m_pArray;
	size_t m_Size;
};

template <typename T>
inline TArray<T>::TArray(const size_t size)
	: m_pArray(size ? new T[size] : nullptr), m_Size(size)
{
}

template <typename T>
inline TArray<T>::TArray(T *&&array, const size_t size)
	: m_pArray(array), m_Size(size)
{
	array = nullptr;
}

template <typename T>
inline TArray<T>::TArray(TArray &&src)
	: m_pArray(src.m_pArray), m_Size(src.m_Size)
{
	src.m_pArray = nullptr;
	src.m_Size = 0;
}

template <typename T>
inline TArray<T>::~TArray(void)
{
	if (m_pArray) delete[] m_pArray;
}

template <typename T>
void TArray<T>::Reset(const size_t size, bool allow_greater)
{
	if (allow_greater)
	{
		if (size <= m_Size) return;
	}
	else if (size == m_Size) return;
	if (m_pArray) delete[] m_pArray;
	m_Size = size;
	if (m_Size)
		m_pArray = new T[m_Size];
	else m_pArray = nullptr;
}

template <typename T>
inline T &TArray<T>::operator[](size_t index)
{
	if (index >= m_Size) throw new ExceptionBase(D_E_ID_ERROR, "Array overflow!", true);
	return m_pArray[index];
}

template <typename T>
inline TArray<T> &TArray<T>::operator=(TArray<T> &src)
{
	this->Reset(src.array_size());
	memcpy(this->array(), src.array(), this->array_size());
	return *this;
}

template <typename T>
inline TArray<T> &TArray<T>::operator=(TArray &&src)
{
	if (m_pArray) delete[] m_pArray;
	this->m_pArray = src.m_pArray;
	this->m_Size = src.m_Size;
	src.m_pArray = nullptr;
	src.m_Size = 0;
	return *this;
}

#include "Typedef.h"

typedef TArray<char>		TDCharArray;
typedef TArray<wchar_t>		TDWCharArray;
typedef TArray<TDByte>		TDByteArray;