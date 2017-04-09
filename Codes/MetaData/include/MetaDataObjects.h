#pragma once

#include "MetaDataGlobalSpace.h"
#include "MetaDataInnerType.h"

////////////////////////////////////////////////
//             System Meta Data               //
////////////////////////////////////////////////
FUNC_DESCRIPT CMetaDataGlobalSpace * __stdcall _MD__GLOBALSPACE__GetMetaData(void);

extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypechar;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypeshort;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypelong;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypeint;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypefloat;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypedouble;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypeunsignedchar;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypeunsignedshort;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypeunsignedlong;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypeunsignedint;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypebool;
extern VAR_DESCRIPT CMetaDataInnerType _MD__InnerTypePtr;