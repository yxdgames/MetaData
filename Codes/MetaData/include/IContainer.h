#pragma once

#include "IInterface.h"

class IContainer : public IInterface
{
public:
	IContainer(void);
	virtual ~IContainer(void) = 0;
public:
	//method
	virtual bool AddItem(void *pItem) = 0;
	virtual bool DelItem(void *pItem) = 0;
public:
	//attribute
	virtual unsigned int Count(void) = 0;
	virtual void *GetItem(unsigned int index) = 0;
public:
	virtual CMetaDataType *GetItemType(void) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IContainer)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(AddItem, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(DelItem, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(Count, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(GetItem, 0)
MD_INTERFACE_DECLARE_DETAIL(IContainer)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(AddItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pItem, *TypeTraits<void*>::GetMetaDataType(), 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<bool>::GetMetaDataType(), 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(DelItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pItem, *TypeTraits<void*>::GetMetaDataType(), 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<bool>::GetMetaDataType(), 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(Count, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<unsigned int>::GetMetaDataType(), 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(GetItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(index, *TypeTraits<unsigned int>::GetMetaDataType(), 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<void*>::GetMetaDataType(), 0)
MD_INTERFACE_DECLARE_END(IContainer)
};

