// MetaData.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include "..\Codes\MetaData\include\MetaDataObjects.h"
#include "..\Codes\MetaData\include\MetaDataSupport.h"

__declspec(dllexport) CMetaDataGlobalSpace * __stdcall GetMetaDataGlobalSpace(void)
{
	return &META_DATA_GLOBALSPACE();
}


