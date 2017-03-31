#pragma once
/*
 * file			MetaDataSupport.h
 * brief		为元数据声明、引用提供通用的宏定义
 * note			None
 * attention	有要生成元数据的语法对象的*.h文件，需要引用本头文件。
 */

#include "TypeTraits.h"

//compile option.
#define CO_MD_CLASS_TYPE_EXTRA

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

/**************************/
/* Meta data of interface */
/**************************/
#define META_DATA_INTERFACE(name)						META_DATA_CLASS_TYPE_BASE(name, CMetaDataInterface)

#define MD_INTERFACE_DECLARE_BEGIN(name)				MD_CLASS_TYPE_DECLARE_BEGIN_BASE(name, Itf, CMetaDataInterface)
#define MD_INTERFACE_DECLARE_DETAIL(name)				MD_CLASS_TYPE_DECLARE_DETAIL_BASE(name, CMetaDataInterface)

				/*--添加接口元数据信息--*/
#define MD_INTERFACE_INTERFACE_DEF(parent_intf_name)	MD_CLASS_TYPE_INTERFACE_DEF(parent_intf_name)

				/*--添加成员函数元数据信息--*/
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_INTERFACE_MEMBER_FUNC_DEF(func_name, index)					MD_CLASS_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//添加成员函数参数元数据信息
#define MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//添加成员函数返回值元数据信息
#define MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

#define MD_INTERFACE_DECLARE_END(name)									MD_CLASS_TYPE_DECLARE_END(name)

/***************************/
/* Meta data of class type */
/***************************/
#define META_DATA_CLASS_TYPE(name)							META_DATA_CLASS_TYPE_BASE(name, CMetaDataClassType)
#define META_DATA_CLASS_TYPE_BASE(name, md_type)			(*reinterpret_cast<md_type*>(TypeTraits<name>::GetMetaDataType()))
//嵌套用
#define META_DATA_CLASS_TYPE_INNER(name, outer_name)		(outer_name::name::_MD__CT##name)

#define MD_CLASS_TYPE_DECLARE_BEGIN(name)	MD_CLASS_TYPE_DECLARE_BEGIN_BASE(name, CT, CMetaDataClassType)
#define MD_CLASS_TYPE_DECLARE_BEGIN_BASE(name, md_obj_pre_name, md_type) \
	public: \
		virtual CMetaDataType *GetType(void)			{ return &_MD__##md_obj_pre_name##name; } \
		static md_type *GetMetaData(void)	{ return &_MD__##md_obj_pre_name##name; } \
		static md_type _MD__##md_obj_pre_name##name; \
		__MD_CLASS_TYPE_MEMBER_EXTRA

#define MD_CLASS_TYPE_DECLARE_DETAIL(name)	MD_CLASS_TYPE_DECLARE_DETAIL_BASE(name, CMetaDataClassType)
#define MD_CLASS_TYPE_DECLARE_DETAIL_BASE(name, md_type) \
	private: \
		static class C_MD__CT_DID##name \
		{ \
		public: \
			C_MD__CT_DID##name() \
			{ \
				char *pClsName(#name); \
				md_type &MDType(META_DATA_CLASS_TYPE_BASE(name, md_type)); \
				name *pTemObj(reinterpret_cast<name*>(sizeof(int))); \
				name *pTemObj2(reinterpret_cast<name*>(0)); \
				CMetaDataFunction *pMDFunc;

				/*--添加基类元数据信息--*/
#define MD_CLASS_TYPE_BASE_CLASS_DEF(base_class_name) \
	MDType.AddBaseType(&META_DATA_CLASS_TYPE(base_class_name), reinterpret_cast<unsigned int>(static_cast<base_class_name*>(pTemObj)) - sizeof(int));

				/*--添加接口元数据信息--*/
#define MD_CLASS_TYPE_INTERFACE_DEF(intf_name) \
	MDType.AddInterface(&META_DATA_INTERFACE(intf_name), reinterpret_cast<unsigned int>(static_cast<intf_name*>(pTemObj)) - sizeof(int));

				/*--添加构造函数元数据信息--*/
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index) \
	private: \
		static bool _MD__CLSCR##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CLASS_TYPE_CONSTRUCTOR_DEF(index) \
	static CMetaDataFunction _MD__CR##index(pClsName, &MDType, _MD__CLSCR##index); \
	MDType.AddConstructor(&_MD__CR##index); \
	pMDFunc = &_MD__CR##index; \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &MDType, 1));

					//添加构造函数参数元数据信息
#define MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));

				/*--添加成员函数元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index) \
	private: \
		static bool _MD__CLSMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CLASS_TYPE_MEMBER_FUNC_DEF(func_name, index) \
	static CMetaDataFunction _MD__MF##func_name##index(#func_name, &MDType, _MD__CLSMF##func_name##index); \
	MDType.AddMemberFunc(&_MD__MF##func_name##index); \
	pMDFunc = &_MD__MF##func_name##index;

					//添加成员函数参数元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//添加成员函数返回值元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

				/*--添加成员变量元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level) \
	static CMetaDataCustomTypeMemberVar _MD__CT_MV##var_name(#var_name, &MDType, &(var_type), (ptr_level), reinterpret_cast<unsigned int>(&(pTemObj2->var_name))); \
	MDType.AddMemberVar(&_MD__CT_MV##var_name);

				/*--添加静态成员函数元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index) \
	private: \
		static bool _MD__CLSSMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index) \
	static CMetaDataFunction _MD__SMF##func_name##index(#func_name, &MDType, _MD__CLSSMF##func_name##index); \
	MDType.AddStaticMemberFunc(&_MD__SMF##func_name##index); \
	pMDFunc = &_MD__SMF##func_name##index;

					//添加静态成员函数参数元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//添加静态成员函数返回值元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

				/*--添加静态成员变量元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level) \
	static CMetaDataVariable _MD__CT_SMV##var_name(#var_name, &MDType, &(var_type), (ptr_level), &var_name); \
	MDType.AddStaticMemberVar(&_MD__CT_SMV##var_name);

#define MD_CLASS_TYPE_DECLARE_END(name) \
				pMDFunc = NULL; \
			} \
		} _MD__CT_DIDO##name;

#define __MD_INTERFACE_MEMBER_EXTRA	__MD_CLASS_TYPE_MEMBER_EXTRA

#ifdef CO_MD_CLASS_TYPE_EXTRA
#define __MD_CLASS_TYPE_MEMBER_EXTRA \
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
#define __MD_CLASS_TYPE_MEMBER_EXTRA
#endif //CO_MD_CLASS_TYPE_EXTRA

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
