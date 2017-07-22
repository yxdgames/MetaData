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
	static CMetaDataType *GetMetaDataType(void)		{ return T::GetMetaData(); }
	static CMetaDataType *GetMetaDataType(T *pObj)	{ return pObj ? pObj->GetType() : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypechar; }
	static CMetaDataType *GetMetaDataType(char *pObj)	{ return pObj ? &_MD__InnerTypechar : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypewchar_t; }
	static CMetaDataType *GetMetaDataType(char *pObj)	{ return pObj ? &_MD__InnerTypewchar_t : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypeshort; }
	static CMetaDataType *GetMetaDataType(short *pObj)	{ return pObj ? &_MD__InnerTypeshort : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypelong; }
	static CMetaDataType *GetMetaDataType(long *pObj)	{ return pObj ? &_MD__InnerTypelong : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypeint; }
	static CMetaDataType *GetMetaDataType(int *pObj)	{ return pObj ? &_MD__InnerTypeint : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypefloat; }
	static CMetaDataType *GetMetaDataType(float *pObj)	{ return pObj ? &_MD__InnerTypefloat : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypedouble; }
	static CMetaDataType *GetMetaDataType(double *pObj)	{ return pObj ? &_MD__InnerTypedouble : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedchar; }
	static CMetaDataType *GetMetaDataType(unsigned char *pObj)	{ return pObj ? &_MD__InnerTypeunsignedchar : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedshort; }
	static CMetaDataType *GetMetaDataType(unsigned short *pObj)	{ return pObj ? &_MD__InnerTypeunsignedshort : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedlong; }
	static CMetaDataType *GetMetaDataType(unsigned long *pObj)	{ return pObj ? &_MD__InnerTypeunsignedlong : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedint; }
	static CMetaDataType *GetMetaDataType(unsigned int *pObj)	{ return pObj ? &_MD__InnerTypeunsignedint : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypebool; }
	static CMetaDataType *GetMetaDataType(bool *pObj)	{ return pObj ? &_MD__InnerTypebool : NULL; }
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
	static CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypePtr; }
	static CMetaDataType *GetMetaDataType(void **pObj)	{ return pObj ? &_MD__InnerTypePtr : NULL; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};