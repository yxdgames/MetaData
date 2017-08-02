#include "stdafx.h"
#include "..\include\MetaDataObjects.h"

#include "..\include\MetaDataSupport2.h"

////////////////////////////////////////////////
//             System Meta Data               //
////////////////////////////////////////////////
//全局空间元数据 -- 唯一
static const CMetaDataGlobalSpace _MD__GlobalSpace;
FUNC_DESCRIPT const CMetaDataGlobalSpace * _MD__GLOBALSPACE__GetMetaData(void)
{
	return &_MD__GlobalSpace;
}

#ifndef META_DATA_GLOBALSPACE
#define META_DATA_GLOBALSPACE()		(*(::_MD__GLOBALSPACE__GetMetaData()))
#endif

//内建类型元数据
MD_INNER_TYPE_DEF(char)
MD_INNER_TYPE_DEF(wchar_t)
MD_INNER_TYPE_DEF(short)
MD_INNER_TYPE_DEF(long)
MD_INNER_TYPE_DEF(int)
MD_INNER_TYPE_DEF(float)
MD_INNER_TYPE_DEF(double)
MD_INNER_TYPE_DEF(bool)
MD_INNER_TYPE_2_DEF(unsigned, char)
MD_INNER_TYPE_2_DEF(unsigned, short)
MD_INNER_TYPE_2_DEF(unsigned, long)
MD_INNER_TYPE_2_DEF(unsigned, int)
VAR_DESCRIPT const CMetaDataInnerType _MD__InnerTypePtr("void*", &META_DATA_GLOBALSPACE(), sizeof(void*));

//系统扩充类型元数据
#include "IInterface.mdo"
#include "IClone.mdo"
#include "IContainer.mdo"
#include "SimpleString.mdo"

////////////////////////////////////////////////
//             Extra Meta Data                //
////////////////////////////////////////////////
//Demo
#ifdef __META_DATA_DEMO__
#include "Demo.mdo"
#endif //__META_DATA_DEMO__

#include "..\..\src\ExtraMetaDataObjects.mdo"