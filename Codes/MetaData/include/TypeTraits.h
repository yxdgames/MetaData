#pragma once
/*
 * file			TypeTraits.h
 * brief		类型元数据相关
 * note			None
 * attention	None
 */

#include "MetaDataObjects.h"

struct __bool_true {};
struct __bool_false {};

template <typename T>
class TypeTraits
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)		{ return T::GetMetaData(); }
	static const CMetaDataType *GetMetaDataType(T *pObj)	{ return pObj ? pObj->GetType() : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

//Specialization
template <>
class TypeTraits<char>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypechar; }
	static const CMetaDataType *GetMetaDataType(char *pObj)	{ return pObj ? &_MD__InnerTypechar : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<wchar_t>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypewchar_t; }
	static const CMetaDataType *GetMetaDataType(char *pObj)	{ return pObj ? &_MD__InnerTypewchar_t : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<short>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypeshort; }
	static const CMetaDataType *GetMetaDataType(short *pObj)	{ return pObj ? &_MD__InnerTypeshort : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<long>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypelong; }
	static const CMetaDataType *GetMetaDataType(long *pObj)	{ return pObj ? &_MD__InnerTypelong : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<int>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypeint; }
	static const CMetaDataType *GetMetaDataType(int *pObj)	{ return pObj ? &_MD__InnerTypeint : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<float>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypefloat; }
	static const CMetaDataType *GetMetaDataType(float *pObj)	{ return pObj ? &_MD__InnerTypefloat : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<double>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypedouble; }
	static const CMetaDataType *GetMetaDataType(double *pObj)	{ return pObj ? &_MD__InnerTypedouble : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<unsigned char>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedchar; }
	static const CMetaDataType *GetMetaDataType(unsigned char *pObj)	{ return pObj ? &_MD__InnerTypeunsignedchar : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<unsigned short>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedshort; }
	static const CMetaDataType *GetMetaDataType(unsigned short *pObj)	{ return pObj ? &_MD__InnerTypeunsignedshort : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<unsigned long>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedlong; }
	static const CMetaDataType *GetMetaDataType(unsigned long *pObj)	{ return pObj ? &_MD__InnerTypeunsignedlong : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<unsigned int>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedint; }
	static const CMetaDataType *GetMetaDataType(unsigned int *pObj)	{ return pObj ? &_MD__InnerTypeunsignedint : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<bool>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypebool; }
	static const CMetaDataType *GetMetaDataType(bool *pObj)	{ return pObj ? &_MD__InnerTypebool : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TypeTraits<void*>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypePtr; }
	static const CMetaDataType *GetMetaDataType(void **pObj)	{ return pObj ? &_MD__InnerTypePtr : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};