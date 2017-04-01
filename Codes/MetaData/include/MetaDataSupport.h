#pragma once
/*
 * file			MetaDataSupport.h
 * brief		为元数据声明、引用提供通用的宏定义
 * note			None
 * attention	有要生成元数据的语法对象的*.h文件，需要引用本头文件。
 */

#include "MetaDataInterface.h"
#include "MetaDataClassType.h"
#include "TypeTraits.h"

//compile option.
#define CO_MD_CUSTOM_TYPE_EXTRA

/***********************/
/* Meta data of module */
/***********************/
#define META_DATA_MODULE()								(::_MD__Module)

/***************************/
/* Meta data of name space */
/***************************/
#define META_DATA_NAME_SPACE(name)						(name::_MD__NS##name)
//嵌套用
#define META_DATA_NAME_SPACE_INNER(name, outer_name)	(outer_name::name::_MD__NS##name)

/***************************/
/* Meta data of inner type */
/***************************/
#define META_DATA_INNER_TYPE(name)						(*reinterpret_cast<CMetaDataInnerType*>(TypeTraits<name>::GetMetaDataType()))

#include "MetaDataSupportCustomType.h"
/**************************/
/* Meta data of interface */
/**************************/
#define META_DATA_INTERFACE(name)						META_DATA_CUSTOM_TYPE(name, CMetaDataInterface)

#define MD_INTERFACE_DECLARE_BEGIN(name)				MD_CUSTOM_TYPE_DECLARE_BEGIN(name, Itf, CMetaDataInterface)
#define MD_INTERFACE_DECLARE_DETAIL(name)				MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface)

				/*--添加接口元数据信息--*/
#define MD_INTERFACE_INTERFACE_DEF(parent_intf_name)	MD_CUSTOM_TYPE_INTERFACE_DEF(parent_intf_name)

				/*--添加成员函数元数据信息--*/
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_INTERFACE_MEMBER_FUNC_DEF(func_name, index)					MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//添加成员函数参数元数据信息
#define MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加成员函数返回值元数据信息
#define MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

#define MD_INTERFACE_DECLARE_END(name)									MD_CUSTOM_TYPE_DECLARE_END(name)

/***************************/
/* Meta data of class type */
/***************************/
#define META_DATA_CLASS_TYPE(name)							META_DATA_CUSTOM_TYPE(name, CMetaDataClassType)
//嵌套用
#define META_DATA_CLASS_TYPE_INNER(name, outer_name)		META_DATA_CUSTOM_TYPE_INNER(name, outer_name, CT)

#define MD_CLASS_TYPE_DECLARE_BEGIN(name)					MD_CUSTOM_TYPE_DECLARE_BEGIN(name, CT, CMetaDataClassType)
#define MD_CLASS_TYPE_DECLARE_DETAIL(name)					MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataClassType)

				/*--添加基类元数据信息--*/
#define MD_CLASS_TYPE_BASE_CLASS_DEF(base_class_name)		MD_CUSTOM_TYPE_BASE_CLASS_DEF(base_class_name)

				/*--添加接口元数据信息--*/
#define MD_CLASS_TYPE_INTERFACE_DEF(intf_name)				MD_CUSTOM_TYPE_INTERFACE_DEF(intf_name)

				/*--添加构造函数元数据信息--*/
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index)	MD_CUSTOM_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index)
#define MD_CLASS_TYPE_CONSTRUCTOR_DEF(index)				MD_CUSTOM_TYPE_CONSTRUCTOR_DEF(index)

					//添加构造函数参数元数据信息
#define MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level)

				/*--添加成员函数元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_CLASS_TYPE_MEMBER_FUNC_DEF(func_name, index)					MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//添加成员函数参数元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加成员函数返回值元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--添加成员变量元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level)

				/*--添加静态成员函数元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)	MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index)				MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index)

					//添加静态成员函数参数元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)	MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加静态成员函数返回值元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level)		MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--添加静态成员变量元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level)	MD_CUSTOM_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level)

#define MD_CLASS_TYPE_DECLARE_END(name)										MD_CUSTOM_TYPE_DECLARE_END(name)

/*************************/
/* Meta data of variable */
/*************************/
#define META_DATA_GLOBAL_VARIABLE(name)				(_MD__V##name)

#define MD_GLOBAL_VARIABLE_DECLARE(name)			extern CMetaDataVariable _MD__V##name;

/*************************/
/* Meta data of function */
/*************************/
#define META_DATA_GLOBAL_FUNCTION(name)				(_MD__F##name)

#define MD_GLOBAL_FUNCTION_DECLARE(name)			extern CMetaDataFunction _MD__F##name;

/*********************************************/
/* Meta data of function parameters & return */
/*********************************************/
#define MD_FUNCTION_PARAM_DEF(name, type, ptr_level, func) \
	(func)->AddParamInfo(new CMetaDataVarBase(#name, (func), (type), (ptr_level));

#define MD_FUNCTION_RETURN_DEF(type, ptr_level, func) \
	(func)->SetReturnInfo(new CMetaDataVarBase(NULL, (func), (type), (ptr_level));

/*********************************************/
/*       __MD_CUSTOM_TYPE_MEMBER_EXTRA       */
/*********************************************/
#ifdef CO_MD_CUSTOM_TYPE_EXTRA
#define __MD_CUSTOM_TYPE_MEMBER_EXTRA \
	public: \
		template <typename T> \
		bool IsTypeOf(void) \
		{ \
			CMetaDataType *thisType(this->GetType()); \
			CMetaDataType *pType(TypeTraits<T>::GetMetaDataType()); \
			return thisType->IsTypeOf(pType); \
		} \
		template <typename T> \
		T *AsType(void) \
		{ \
			CMetaDataType *thisType(this->GetType()); \
			CMetaDataType *pType(TypeTraits<T>::GetMetaDataType()); \
			return reinterpret_cast<T*>(thisType->AsType(this->GetTrueSelf(), pType)); \
		} \
	private: \
		virtual void *GetTrueSelf(void) \
		{ \
			return this; \
		}
#else
#define __MD_CUSTOM_TYPE_MEMBER_EXTRA
#endif //CO_MD_CUSTOM_TYPE_EXTRA