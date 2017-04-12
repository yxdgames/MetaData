#include "stdafx.h"
#include "CdllCls1.h"

#include "..\Codes\MetaData\include\MetaDataSupport2.h"

CdllCls1::CdllCls1(void)
{
}


CdllCls1::~CdllCls1(void)
{
}

//CdllCls1
MD_CLASS_TYPE_DEF(CdllCls1)

	//constructor
MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_BEGIN(CdllCls1, 0)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK(0)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ(CdllCls1);
MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_END()

	//destructor
MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DEF(CdllCls1)