#pragma once
/*
 * file			TypeTraits.h
 * brief		类型元数据相关
 * note			None
 * attention	None
 */

#include "MetaDataObjects.h"

struct STRUCT_DESCRIPT __bool_true {};
struct STRUCT_DESCRIPT __bool_false {};

template <typename T>
class TEMPLATE_CLASS_DESCRIPT TypeTraits
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<char>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<wchar_t>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<short>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<int>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<long>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<long long>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)			{ return &_MD__InnerTypelonglong; }
	static const CMetaDataType *GetMetaDataType(long long *pObj)	{ return pObj ? &_MD__InnerTypelonglong : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TEMPLATE_CLASS_DESCRIPT TypeTraits<unsigned char>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<unsigned short>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<unsigned int>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<unsigned long>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<unsigned long long>
{
public:
	//method
	static const CMetaDataType *GetMetaDataType(void)					{ return &_MD__InnerTypeunsignedlonglong; }
	static const CMetaDataType *GetMetaDataType(unsigned long long *pObj)	{ return pObj ? &_MD__InnerTypeunsignedlonglong : nullptr; }
public:
	//type traits
private:
	TypeTraits(void)	{}
	~TypeTraits(void)	{}
};

template <>
class TEMPLATE_CLASS_DESCRIPT TypeTraits<float>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<double>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<bool>
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
class TEMPLATE_CLASS_DESCRIPT TypeTraits<void*>
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