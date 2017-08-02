// MetaDataTestDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "..\Codes\MetaData\include\MetaDataObjects.h"

extern "C" const void * __stdcall GetMetaDataGlobalSpace(void)
{
	return _MD__GLOBALSPACE__GetMetaData();
}