#pragma once
/*
* file			MetaDataSupport_Unkwn2.h
* brief			ΪIUnkwnԪ���ݶ����ṩͨ�õĺ궨��
* note			None
* attention		��MetaDataObjects.cpp�����ã�ʹ�ã�������*.mdo�ο�ʹ�ã�����Ҫ���á�
*/

#include "MetaDataSupportCustomType2.h"

/**********************************/
/* Meta data of unknown interface */
/**********************************/
//��Ƕ��
#define MD_UNKWN_INTERFACE_DEF(name)						MD_CUSTOM_TYPE_DEF(name, Iukn, CMetaDataInterface)

//Ƕ����(�����ռ��ڲ�)
#define MD_UNKWN_INTERFACE_IN_NS_DEF(name, outer_name)		MD_CUSTOM_TYPE_IN_NS_DEF(name, Iukn, CMetaDataInterface, outer_name)

//����������װ
#define MD_UNKWN_INTERFACE_DESTRUCTOR_WRAPPER_DEF(intf_name)							MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(intf_name)

//��Ա������װ
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)	MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)

#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)			MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)					MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_END()								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()