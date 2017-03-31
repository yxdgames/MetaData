#pragma once

#include "MetaDataSupport.h"
#include "MetaDataInterface.h"
#include "TypeTraits.h"

class IInterface
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
MD_INTERFACE_DECLARE_DETAIL(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(QueryInterface, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pIntfName, *TypeTraits<char>::GetMetaDataType(), 1)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(outIntf, *TypeTraits<IInterface>::GetMetaDataType(), 2)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<bool>::GetMetaDataType(), 0)
MD_INTERFACE_DECLARE_END(IInterface)
};

