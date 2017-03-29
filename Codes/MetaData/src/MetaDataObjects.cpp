#include "stdafx.h"
#include "..\include\MetaDataObjects.h"

#include "..\include\MetaDataSupport2.h"

////////////////////////////////////////////////
//             System Meta Data               //
////////////////////////////////////////////////
//ģ��Ԫ���� -- Ψһ
CMetaDataModule _MD__Module("");
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
CMetaDataInnerType _MD__InnerTypePtr("void*", &_MD__Module, sizeof(void*));

#ifdef CO_SYSTEM_EXTENDED_TYPE_META_DATA_DEF
//ϵͳ��չ����Ԫ����
#include "IInterface.meo"
#include "IClone.meo"
#include "IContainer.meo"
#include "InterfacedObject.meo"
#include "SimpleString.meo"
#endif //CO_SYSTEM_EXTENDED_TYPE_META_DATA_DEF

////////////////////////////////////////////////
//             Extra Meta Data                //
////////////////////////////////////////////////
#include "..\..\include\MetaDataExtraObjects.meo"