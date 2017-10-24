#pragma once
/*
 * file			MetaDataSupport.h
 * brief		为元数据声明、引用提供通用的宏定义
 * note			None
 * attention	有要生成元数据的语法对象的*.h文件，需要引用本头文件。
 */

#include "MetaDataNameSpace.h"
#include "TypeTraits.h"

#define CLASS_DESCRIPT_FOR_MD_SUPPORT

/***********************/
/* Meta data of module */
/***********************/
#define META_DATA_GLOBALSPACE()							(*(::_MD__GLOBALSPACE__GetMetaData()))

/***************************/
/* Meta data of name space */
/***************************/
#define META_DATA_NAME_SPACE(name)						(*(name::_MD__NS__GetMetaData()))

#define MD_NAME_SPACE_DECLARE(name) \
	extern const CMetaDataNameSpace _MD__NS##name; \
	extern const CMetaDataNameSpace *_MD__NS__GetMetaData(void);

/***************************/
/* Meta data of inner type */
/***************************/
#define META_DATA_INNER_TYPE(name) \
	(*reinterpret_cast<const CMetaDataInnerType*>(AssertMetaData(TypeTraits<name>::GetMetaDataType(), D_META_DATA_TYPE_ID_INNER_TYPE)))

#include "MetaDataSupportCustomType.h"
/**************************/
/* Meta data of interface */
/**************************/
#define META_DATA_INTERFACE(name)						META_DATA_CUSTOM_TYPE(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE)
#define META_DATA_INTERFACE_NO_ASSERT(name)				META_DATA_CUSTOM_TYPE_NO_ASSERT(name, CMetaDataInterface)

#define MD_INTERFACE_DECLARE_BEGIN(name)				MD_CUSTOM_TYPE_DECLARE_BEGIN(name, Itf, CMetaDataInterface)
#define MD_INTERFACE_DECLARE_DETAIL(name)				MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, CLASS_DESCRIPT_FOR_MD_SUPPORT)
#define MD_INTERFACE_DECLARE_DETAIL_KERNEL(name)		MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, CLASS_DESCRIPT)

				/*--设置GUID--*/
#define MD_INTERFACE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8) \
	MD_CUSTOM_TYPE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8)

				/*--添加接口元数据信息--*/
#define MD_INTERFACE_INTERFACE_DEF(parent_intf_name)					MD_CUSTOM_TYPE_INTERFACE_DEF(parent_intf_name)

				/*--添加析构函数元数据信息--*/
#define MD_INTERFACE_DESTRUCTOR_WRAPPER_DECLARE()						MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
#define MD_INTERFACE_DESTRUCTOR_DEF()									MD_CUSTOM_TYPE_DESTRUCTOR_DEF()

				/*--添加成员函数元数据信息--*/
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_INTERFACE_MEMBER_FUNC_DEF(func_name, index)					MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//添加成员函数参数元数据信息
#define MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加成员函数返回值元数据信息
#define MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--添加属性元数据信息--*/
#define MD_INTERFACE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level) \
	MD_CUSTOM_TYPE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level)

#define MD_INTERFACE_DECLARE_END(name)									MD_CUSTOM_TYPE_DECLARE_END(name)

/***************************/
/* Meta data of class type */
/***************************/
#define META_DATA_CLASS_TYPE(name)							META_DATA_CUSTOM_TYPE(name, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE)
#define META_DATA_CLASS_TYPE_NO_ASSERT(name)				META_DATA_CUSTOM_TYPE_NO_ASSERT(name, CMetaDataClassType)

#define MD_CLASS_TYPE_DECLARE_BEGIN(name)					MD_CUSTOM_TYPE_DECLARE_BEGIN(name, CT, CMetaDataClassType)
#define MD_CLASS_TYPE_DECLARE_DETAIL(name)					MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, CLASS_DESCRIPT_FOR_MD_SUPPORT)
#define MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(name)			MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, CLASS_DESCRIPT)

				/*--设置GUID--*/
#define MD_CLASS_TYPE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8) \
	MD_CUSTOM_TYPE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8)

				/*--添加基类元数据信息--*/
#define MD_CLASS_TYPE_BASE_CLASS_DEF(base_class_name)		MD_CUSTOM_TYPE_BASE_CLASS_DEF(base_class_name)

				/*--添加接口元数据信息--*/
#define MD_CLASS_TYPE_INTERFACE_DEF(intf_name)				MD_CUSTOM_TYPE_INTERFACE_DEF(intf_name)

				/*--添加未知接口元数据信息--*/
#define MD_CLASS_TYPE_UNKNOWN_INTERFACE_DEF(unkwn_intf_name)			MD_CUSTOM_TYPE_UNKNOWN_INTERFACE_DEF(unkwn_intf_name)

				/*--添加构造函数元数据信息--*/
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index)	MD_CUSTOM_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index)
#define MD_CLASS_TYPE_CONSTRUCTOR_DEF(index)				MD_CUSTOM_TYPE_CONSTRUCTOR_DEF(index)

					//添加构造函数参数元数据信息
#define MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level)

				/*--添加析构函数元数据信息--*/
#define MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DECLARE()			MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
#define MD_CLASS_TYPE_DESTRUCTOR_DEF()						MD_CUSTOM_TYPE_DESTRUCTOR_DEF()

				/*--添加成员函数元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_CLASS_TYPE_MEMBER_FUNC_DEF(func_name, index)					MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//添加成员函数参数元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加成员函数返回值元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--添加成员变量元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level)

				/*--添加属性元数据信息--*/
#define MD_CLASS_TYPE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level) \
	MD_CUSTOM_TYPE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level)
#define MD_CLASS_TYPE_MEMBER_PROPERTY_DEF(prop_name, prop_type, ptr_level) \
	MD_CUSTOM_TYPE_MEMBER_PROPERTY_DEF(prop_name, prop_type, ptr_level)

				/*--添加静态成员函数元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)	MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index)				MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index)

					//添加静态成员函数参数元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)	MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加静态成员函数返回值元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level)		MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--添加静态成员变量元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level)	MD_CUSTOM_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level)

				/*--添加AsTypeEx函数指针--*/
#define MD_CLASS_TYPE_AS_TYPE_EX_DEF(pfun_as_type_ex)						MD_CUSTOM_TYPE_AS_TYPE_EX_DEF(pfun_as_type_ex)

#define MD_CLASS_TYPE_DECLARE_END(name)										MD_CUSTOM_TYPE_DECLARE_END(name)

/*************************/
/* Meta data of variable */
/*************************/
#define META_DATA_GLOBAL_VARIABLE(name)				(_MD__V##name)

#define MD_GLOBAL_VARIABLE_DECLARE(name)			extern const CMetaDataVariable _MD__V##name;

/*************************/
/* Meta data of function */
/*************************/
#define META_DATA_GLOBAL_FUNCTION(name)				(_MD__F##name)

#define MD_GLOBAL_FUNCTION_DECLARE(name)			extern const CMetaDataFunction _MD__F##name;
