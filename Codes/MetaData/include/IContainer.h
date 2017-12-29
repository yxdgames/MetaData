#pragma once

#include "IInterface.h"

class CLASS_DESCRIPT IContainer : public IInterface
{
public:
	IContainer(void) {}
	virtual ~IContainer(void) = 0;
public:
	//method
	virtual void *NewItem(size_t type_index) = 0;
	virtual bool AddItem(size_t type_index, void *pItem) = 0;
	virtual bool DelItem(size_t type_index, void *pItem) = 0;
	virtual void ClearItems(size_t type_index) = 0;
public:
	//attribute
	virtual size_t Count(size_t type_index) = 0;
	virtual void *GetItem(size_t type_index, size_t index) = 0;
public:
	virtual size_t GetItemTypeCount(void) = 0;
	virtual const CMetaDataType *GetItemType(size_t type_index) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IContainer)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(NewItem, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(AddItem, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(DelItem, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(ClearItems, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(Count, 0)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(GetItem, 0)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IContainer)
	// { 678D5B51-3EBD-4F9C-824E-87D58BC750EA }
	MD_INTERFACE_GUID_DEF(0x678d5b51, 0x3ebd, 0x4f9c, 0x82, 0x4e, 0x87, 0xd5, 0x8b, 0xc7, 0x50, 0xea)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
	MD_INTERFACE_MEMBER_FUNC_DEF(NewItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(type_index, size_t, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(void*, 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(AddItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(type_index, size_t, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pItem, void*, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(bool, 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(DelItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(type_index, size_t, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pItem, void*, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(bool, 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(ClearItems, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(type_index, size_t, 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(Count, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(type_index, size_t, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(size_t, 0)
	MD_INTERFACE_MEMBER_FUNC_DEF(GetItem, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(type_index, size_t, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(index, size_t, 0)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(void*, 0)
MD_INTERFACE_DECLARE_END(IContainer)
};
