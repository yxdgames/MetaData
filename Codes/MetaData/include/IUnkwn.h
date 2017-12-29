#pragma once
/*-------------------------------------------------------------------*/
/*                                                                   */
/*                            �����Խӿ�                             */
/*          �ṩһ�������Ʋ���Ľӿڣ��������������Խ���             */
/*                      ����Ԫ���ݲ���δ֪�ġ�                       */
/*                                                                   */
/*   ��ȻCMetaDataCustomType������һ��ר��Vector�����δ֪�ӿ���Ϣ�� */
/* ��CMetaDataCustomTypeֻ���ṩ��һ����Ϣ���������ֻ��֪����ŵ�   */
/* ��һ����IInterfaceϵ�ӿڵ���Ϣ������֪����IUnkwn���͡�ʹ��ʱ����  */
/* ʹ�÷�ǿת��ʹ�á�                                                */
/*                                                                   */
/*   ������IUnkwn���ӽӿڣ����뽫IUnkwn��Ϊ��һ�����ӿڡ�            */
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

/*---IUnkwn(��COM IUnknown����)---*/
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