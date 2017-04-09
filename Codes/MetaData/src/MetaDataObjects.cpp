#include "stdafx.h"
#include "..\include\MetaDataObjects.h"

#include "..\include\MetaDataSupport2.h"

////////////////////////////////////////////////
//             System Meta Data               //
////////////////////////////////////////////////
//宇宙原像（根）元数据 -- 唯一
static CMetaDataGlobalSpace _MD__GlobalSpace;
FUNC_DESCRIPT CMetaDataGlobalSpace * __stdcall _MD__GLOBALSPACE__GetMetaData(void)
{
	return &_MD__GlobalSpace;
}

#ifndef META_DATA_GLOBALSPACE
#define META_DATA_GLOBALSPACE()		(*(::_MD__GLOBALSPACE__GetMetaData()))
#endif

//内建类型元数据
MD_INNER_TYPE_DEF(char)
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
VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypePtr("void*", &META_DATA_GLOBALSPACE(), sizeof(void*));

#ifdef CO_META_DATA_EXTRA_SYSTEM_DEF
//系统扩展类型元数据
#include "IInterface.meo"
#include "IClone.meo"
#include "IContainer.meo"
#include "InterfacedObject.meo"
#include "SimpleString.meo"
#endif //CO_META_DATA_EXTRA_SYSTEM_DEF

////////////////////////////////////////////////
//             Extra Meta Data                //
////////////////////////////////////////////////
#include "..\..\src\MetaDataExtraObjects.meo"