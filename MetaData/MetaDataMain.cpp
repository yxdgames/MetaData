// MetaData.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include "..\Codes\MetaData\include\MetaDataObjects.h"

extern "C" const void * __stdcall GetMetaDataGlobalSpace(void)
{
	return _MD__GLOBALSPACE__GetMetaData();
}