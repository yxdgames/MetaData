#pragma once
/*
* file			MetaDataSupport_Unkwn.h
* brief			为IUnkwn元数据声明、引用提供通用的宏定义
* note			None
* attention		有要生成IUnkwn元数据的语法对象的*.h文件，需要引用本头文件。
*/

#include "MetaDataSupportCustomType.h"

#ifndef CLASS_DESCRIPT_FOR_MD_SUPPORT
#define CLASS_DESCRIPT_FOR_MD_SUPPORT
#endif //CLASS_DESCRIPT_FOR_MD_SUPPORT

/**********************************/
/* Meta data of unknown interface */
/**********************************/
#define META_DATA_UNKWN_INTERFACE(name)						META_DATA_CUSTOM_TYPE(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE)
#define META_DATA_UNKWN_INTERFACE_NO_ASSERT(name)			META_DATA_CUSTOM_TYPE_NO_ASSERT(name, CMetaDataInterface)

#define MD_UNKWN_INTERFACE_DECLARE_BEGIN(name)				MD_CUSTOM_TYPE_DECLARE_BEGIN_NO_VIRTUAL(name, Iukn, CMetaDataInterface)
#define MD_UNKWN_INTERFACE_DECLARE_DETAIL(name)				MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, CLASS_DESCRIPT_FOR_MD_SUPPORT)
#define MD_UNKWN_INTERFACE_DECLARE_DETAIL_KERNEL(name)		MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, CLASS_DESCRIPT)

				/*--设置GUID--*/
#define MD_UNKWN_INTERFACE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8) \
	MD_CUSTOM_TYPE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8)

				/*--添加未知接口元数据信息--*/
#define MD_UNKWN_INTERFACE_UNKWN_INTERFACE_DEF(parent_intf_name)			MD_CUSTOM_TYPE_UNKNOWN_INTERFACE_DEF(parent_intf_name)

				/*--添加析构函数元数据信息--*/
#define MD_UNKWN_INTERFACE_DESTRUCTOR_WRAPPER_DECLARE()						MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
#define MD_UNKWN_INTERFACE_DESTRUCTOR_DEF()									MD_CUSTOM_TYPE_DESTRUCTOR_DEF()

				/*--添加成员函数元数据信息--*/
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)	MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_DEF(func_name, index)				MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//添加成员函数参数元数据信息
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加成员函数返回值元数据信息
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--添加属性元数据信息--*/
#define MD_UNKWN_INTERFACE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level) \
	MD_CUSTOM_TYPE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level)

#define MD_UNKWN_INTERFACE_DECLARE_END(name)								MD_CUSTOM_TYPE_DECLARE_END(name)