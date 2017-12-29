#pragma once
/*-------------------------------------------------------------------*/
/*                                                                   */
/*                            跨语言接口                             */
/*          提供一个二进制层面的接口，可以与其它语言交互             */
/*                      对于元数据侧是未知的。                       */
/*                                                                   */
/*   虽然CMetaDataCustomType定义了一个专门Vector来存放未知接口信息， */
/* 但CMetaDataCustomType只是提供了一个信息存放容器，只是知道存放的   */
/* 是一个非IInterface系接口的信息，并不知道是IUnkwn类型。使用时，由  */
/* 使用方强转后使用。                                                */
/*                                                                   */
/*   派生自IUnkwn的子接口，必须将IUnkwn作为第一个父接口。            */
/*                                                                   */
/*-------------------------------------------------------------------*/
#include "MetaDataSupport_Unkwn.h"
#include <guiddef.h>

/*---Type Definition---*/
typedef long			HResult;
typedef unsigned long	ULong;

/*---Macro---*/
#define IUNKWN_CALLCONVENTION				__stdcall
#define IUNKWN_MEMFUN_DESCRIPT				IUNKWN_CALLCONVENTION

#define IUNKWN_CONSTRAINT(unkwn_name) \
	protected: \
		unkwn_name(void) {} \
		~unkwn_name(void) {}

/*---IUnkwn(与COM IUnknown兼容)---*/
struct STRUCT_DESCRIPT IUnkwn
{
public:
	virtual HResult IUNKWN_MEMFUN_DESCRIPT QueryInterface(
        /* [in] */ REFIID riid,
        /* [out] */ void **ppvObject) = 0;
    virtual ULong IUNKWN_MEMFUN_DESCRIPT AddRef(void) = 0;
    virtual ULong IUNKWN_MEMFUN_DESCRIPT Release(void) = 0;

IUNKWN_CONSTRAINT(IUnkwn)
/*Meta Data Definition*/
MD_UNKWN_INTERFACE_DECLARE_BEGIN(IUnkwn)
MD_UNKWN_INTERFACE_DECLARE_DETAIL_KERNEL(IUnkwn)
	// { 00000000-0000-0000-C000-000000000046 }
	MD_UNKWN_INTERFACE_GUID_DEF(0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46)
MD_UNKWN_INTERFACE_DECLARE_END(IUnkwn)
};

/*---------------------------------------*/
/*   Global Inline Function Definition   */
/*---------------------------------------*/
inline const IID &GuidOfMetaDataToIID(const TDGUID &guid)
{
	return *reinterpret_cast<const IID*>(guid.Data);
}

inline const IID &GetIIDFromMetaData(const CMetaData *pMetaData)
{
	return *reinterpret_cast<const IID*>(pMetaData->GetGUID().Data);
}

#define D_IUNKWN_GUID(iukn)	GetIIDFromMetaData(TypeTraits<iukn>::GetMetaDataType())

//for compiling static library
extern void IUnkwn_Dummy_Func(void);