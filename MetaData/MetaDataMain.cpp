// MetaData.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "..\Codes\MetaData\include\MetaDataObjects.h"
#include "..\Codes\MetaData\include\MetaDataSupport.h"

__declspec(dllexport) CMetaDataGlobalSpace * __stdcall GetMetaDataGlobalSpace(void)
{
	return &META_DATA_GLOBALSPACE();
}


