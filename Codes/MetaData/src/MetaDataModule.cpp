#include "stdafx.h"
#include "..\include\MetaDataModule.h"


CMetaDataModule::CMetaDataModule(char *pName, CMetaData *pParent)
	:CMetaData(pName, pParent, false)
{
}


CMetaDataModule::~CMetaDataModule(void)
{
}
