#include "stdafx.h"
#include "..\include\MetaDataObjects.h"

#include "..\include\MetaDataSupport2.h"

////////////////////////////////////////////////
//             System Meta Data               //
////////////////////////////////////////////////
//ģ��Ԫ���� -- Ψһ
static CMetaDataModule _MD__Module("");
CMetaDataModule *_MD__MODULE__GetMetaData(void)
{
	return &_MD__Module;
}

#ifndef META_DATA_MODULE
#define META_DATA_MODULE()		(*(::_MD__MODULE__GetMetaData()))
#endif

//�ڽ�����Ԫ����
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
CMetaDataInnerType _MD__InnerTypePtr("void*", _MD__MODULE__GetMetaData(), sizeof(void*));

#ifdef CO_META_DATA_EXTRA_SYSTEM_DEF
//ϵͳ��չ����Ԫ����
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