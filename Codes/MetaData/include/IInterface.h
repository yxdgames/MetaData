#pragma once
/*--------------------------------------------------------*/
/*                                                        */
/*               元数据提供的默认接口基类                 */
/*              元数据可以识别到IInterface                */
/*                                                        */
/* IInterface系接口要求：                                 */
/*     直接派生自IInterface，并且将IInterface作为         */
/* 第一个父接口的接口，称之为“IInterface系接口”。       */
/*     间接派生自IInterface，并且将“IInterface系接口”   */
/* 作为第一个父接口的接口，也称之为“IInterface系接口”。 */
/*                                                        */
/*--------------------------------------------------------*/
#include "MetaDataSupport.h"

class CLASS_DESCRIPT IInterface
{
public:
	IInterface(void) {}
	virtual ~IInterface(void) = 0 {};
public:
	//method of interface
	virtual bool QueryInterface(TDGUID &guid, IInterface **outIntf) = 0;
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IInterface)
	MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(QueryInterface, 0)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IInterface)
	// { 3D8C41F5-647D-4828-AB40-37FF2CA42DA8 }
	MD_INTERFACE_GUID_DEF(0x3d8c41f5, 0x647d, 0x4828, 0xab, 0x40, 0x37, 0xff, 0x2c, 0xa4, 0x2d, 0xa8)
	MD_INTERFACE_MEMBER_FUNC_DEF(QueryInterface, 0)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(pIntfName, char, 1)
		MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(outIntf, IInterface, 2)
		MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(bool, 0)
MD_INTERFACE_DECLARE_END(IInterface)
};
