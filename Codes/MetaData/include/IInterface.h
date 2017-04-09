#pragma once

#include "MetaDataSupport.h"
#include "MetaDataInterface.h"
#include "TypeTraits.h"

class CLASS_DESCRIPT IInterface
{
public:
	IInterface(void);
	virtual ~IInterface(void) = 0 {};
public:
	//method of interface
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IInterface)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(QueryInterface, 0)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(QueryInterface, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pIntfName, char, 1)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(outIntf, IInterface, 2)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(bool, 0)
MD_INTERFACE_DECLARE_END(IInterface)
};

