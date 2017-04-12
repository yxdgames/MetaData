#include "stdafx.h"
#include "CdllCls2.h"

#include "..\Codes\MetaData\include\MetaDataSupport2.h"

CdllCls2::CdllCls2(void)
{
}


CdllCls2::~CdllCls2(void)
{
}

//CdllCls2
MD_CLASS_TYPE_DEF(CdllCls2)

	//constructor
MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_BEGIN(CdllCls2, 0)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK(0)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ(CdllCls2);
MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_END()

	//destructor
MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DEF(CdllCls2)