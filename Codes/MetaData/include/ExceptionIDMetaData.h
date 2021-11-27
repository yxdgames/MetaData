#pragma once
#include "../../include/ExceptionID.h"

#define D_E_ID_MD_BEGIN								(D_E_ID_METADATA_BEGIN)

#define D_E_ID_MD_ERROR								(D_E_ID_MD_BEGIN - 0)
#define D_E_ID_MD_META_DATA_OF_FUNC_CALL			(D_E_ID_MD_BEGIN - 1) //函数元数据调用异常
//...

#define D_E_ID_MD_END								(D_E_ID_METADATA_END)