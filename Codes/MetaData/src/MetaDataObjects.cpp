#include "stdafx.h"
#include "../include/MetaDataObjects.h"
#include "../include/MetaDataSupport2.h"

////////////////////////////////////////////////
//             System Meta Data               //
////////////////////////////////////////////////
//全局空间元数据 -- 唯一
static const CMetaDataGlobalSpace _MD__GlobalSpace;
FUNC_DESCRIPT const CMetaDataGlobalSpace * _MD__GLOBALSPACE__GetMetaData(void)
{
	return &_MD__GlobalSpace;
}

template<typename T>
static void *NewObject(void)
{
	return new T;
}

template<typename T>
static void DeleteObject(void *pObj)
{
	if (pObj) delete reinterpret_cast<T*>(pObj);
}

//内建类型元数据
MD_INNER_TYPE_DEF_NO_VD(char, NewObject<char>, DeleteObject<char>)
MD_INNER_TYPE_DEF_NO_VD(wchar_t, NewObject<wchar_t>, DeleteObject<wchar_t>)
MD_INNER_TYPE_DEF_NO_VD(short, NewObject<short>, DeleteObject<short>)
MD_INNER_TYPE_DEF_NO_VD(int, NewObject<int>, DeleteObject<int>)
MD_INNER_TYPE_DEF_NO_VD(long, NewObject<long>, DeleteObject<long>)
MD_INNER_TYPE_2_DEF_NO_VD(long, long, NewObject<long long>, DeleteObject<long long>)
MD_INNER_TYPE_2_DEF_NO_VD(unsigned, char, NewObject<unsigned char>, DeleteObject<unsigned char>)
MD_INNER_TYPE_2_DEF_NO_VD(unsigned, short, NewObject<unsigned short>, DeleteObject<unsigned short>)
MD_INNER_TYPE_2_DEF_NO_VD(unsigned, int, NewObject<unsigned int>, DeleteObject<unsigned int>)
MD_INNER_TYPE_2_DEF_NO_VD(unsigned, long, NewObject<unsigned long>, DeleteObject<unsigned long>)
MD_INNER_TYPE_3_DEF_NO_VD(unsigned, long, long, NewObject<unsigned long long>, DeleteObject<unsigned long long>)
MD_INNER_TYPE_DEF_NO_VD(float, NewObject<float>, DeleteObject<float>)
MD_INNER_TYPE_DEF_NO_VD(double, NewObject<double>, DeleteObject<double>)
MD_INNER_TYPE_DEF_NO_VD(bool, NewObject<bool>, DeleteObject<bool>)
const CMetaDataInnerType _MD__InnerTypePtr("void*", &META_DATA_GLOBALSPACE(), sizeof(void*), NewObject<void*>, DeleteObject<void*>);

//系统扩充类型元数据
#include "IInterface.mdo"
#include "IClone.mdo"
#include "IContainer.mdo"
#include "IBlob.mdo"
#include "IPropertyNotify.mdo"
#include "SimpleString.mdo"

//跨言语接口（与COM兼容的接口基类）
#include "../include/MetaDataSupport_Unkwn2.h"
#include "IUnkwn.mdo"

////////////////////////////////////////////////
//             Extra Meta Data                //
////////////////////////////////////////////////
//Demo
#ifdef __META_DATA_DEMO__
#include "Demo/Demo.mdo"
#endif //__META_DATA_DEMO__

#include "../../src/ExtraMetaDataObjects.mdo"