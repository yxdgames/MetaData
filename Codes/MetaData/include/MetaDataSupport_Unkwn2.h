#pragma once
/*
* file			MetaDataSupport_Unkwn2.h
* brief			为IUnkwn元数据定义提供通用的宏定义
* note			None
* attention		由MetaDataObjects.cpp来引用（使用）。其它*.mdo参考使用，不需要引用。
*/

#include "MetaDataSupportCustomType2.h"

/**********************************/
/* Meta data of unknown interface */
/**********************************/
//无嵌套
#define MD_UNKWN_INTERFACE_DEF(name)						MD_CUSTOM_TYPE_DEF(name, Iukn, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE)

//嵌套用(命名空间内部)
#define MD_UNKWN_INTERFACE_IN_NS_DEF(name, outer_name)		MD_CUSTOM_TYPE_IN_NS_DEF(name, Iukn, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name)

//析构函数封装
#define MD_UNKWN_INTERFACE_DESTRUCTOR_WRAPPER_DEF(intf_name)							MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(intf_name)

//成员函数封装
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)	MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)

#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)			MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)					MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_END()								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()