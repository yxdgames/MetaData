#pragma once
/*
 * file			MetaDataSupport2.h
 * brief		为元数据定义提供通用的宏定义
 * note			None
 * attention	由MetaDataObjects.cpp来引用（使用）。其它*.mdo参考使用，不需要引用。
 */

/***********************/
/* Meta data of module */
/***********************/
//None

/***************************/
/* Meta data of name space */
/***************************/
#define MD_NAME_SPACE_DEF(name) \
	const CMetaDataNameSpace name::_MD__NS##name(#name, &META_DATA_GLOBALSPACE()); \
	const CMetaDataNameSpace *name::_MD__NS__GetMetaData(void) \
	{ \
		return &_MD__NS##name; \
	}
#define MD_NAME_SPACE_INNER_DEF(name, out_ns) \
	const CMetaDataNameSpace (out_ns::name::_MD__NS##name)(#name, &META_DATA_NAME_SPACE(out_ns)); \
	const CMetaDataNameSpace *out_ns::name::_MD__NS__GetMetaData(void) \
	{ \
		return &_MD__NS##name; \
	}

/***************************/
/* Meta data of inner type */
/***************************/
#define MD_INNER_TYPE_DEF(name, pfunNewObject, pfunDeleteObject) \
	VAR_DESCRIPT const CMetaDataInnerType _MD__InnerType##name(#name, &META_DATA_GLOBALSPACE(), sizeof(name), pfunNewObject, pfunDeleteObject);
#define MD_INNER_TYPE_2_DEF(name1, name2, pfunNewObject, pfunDeleteObject) \
	VAR_DESCRIPT const CMetaDataInnerType _MD__InnerType##name1##name2(#name1" "#name2, &META_DATA_GLOBALSPACE(), sizeof(name1 name2), pfunNewObject, pfunDeleteObject);
#define MD_INNER_TYPE_3_DEF(name1, name2, name3, pfunNewObject, pfunDeleteObject) \
	VAR_DESCRIPT const CMetaDataInnerType _MD__InnerType##name1##name2##name3(#name1" "#name2" "#name3, &META_DATA_GLOBALSPACE(), sizeof(name1 name2 name3), pfunNewObject, pfunDeleteObject);

#define MD_INNER_TYPE_DEF_NO_VD(name, pfunNewObject, pfunDeleteObject) \
	const CMetaDataInnerType _MD__InnerType##name(#name, &META_DATA_GLOBALSPACE(), sizeof(name), pfunNewObject, pfunDeleteObject);
#define MD_INNER_TYPE_2_DEF_NO_VD(name1, name2, pfunNewObject, pfunDeleteObject) \
	const CMetaDataInnerType _MD__InnerType##name1##name2(#name1" "#name2, &META_DATA_GLOBALSPACE(), sizeof(name1 name2), pfunNewObject, pfunDeleteObject);
#define MD_INNER_TYPE_3_DEF_NO_VD(name1, name2, name3, pfunNewObject, pfunDeleteObject) \
	const CMetaDataInnerType _MD__InnerType##name1##name2##name3(#name1" "#name2" "#name3, &META_DATA_GLOBALSPACE(), sizeof(name1 name2 name3), pfunNewObject, pfunDeleteObject);

#include "MetaDataSupportCustomType2.h"
/**************************/
/* Meta data of interface */
/**************************/
//无嵌套
#define MD_INTERFACE_DEF(name)						MD_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE)

//嵌套用(接口内部)
#define MD_INTERFACE_IN_INTF_DEF(name, outer_name)	MD_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name, META_DATA_INTERFACE(outer_name))

//嵌套用(类内部)
#define MD_INTERFACE_IN_CLS_DEF(name, outer_name)	MD_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name, META_DATA_CLASS_TYPE(outer_name))

//嵌套用(命名空间内部)
#define MD_INTERFACE_IN_NS_DEF(name, outer_name)	MD_CUSTOM_TYPE_IN_NS_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name)

//析构函数封装
#define MD_INTERFACE_DESTRUCTOR_WRAPPER_DEF(intf_name)								MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(intf_name)

//成员函数封装
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)							MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_END()									MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()

/** 模板相关 **/
//无嵌套
#define MD_TEMPLATE_INTERFACE_DEF(name, ...)						MD_TEMPLATE_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, __VA_ARGS__)

//嵌套用(接口内部)
#define MD_TEMPLATE_INTERFACE_IN_INTF_DEF(name, outer_name, ...)	MD_TEMPLATE_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name, META_DATA_INTERFACE(outer_name), __VA_ARGS__)

//嵌套用(类内部)
#define MD_TEMPLATE_INTERFACE_IN_CLS_DEF(name, outer_name, ...)		MD_TEMPLATE_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name, META_DATA_CLASS_TYPE(outer_name), __VA_ARGS__)

//嵌套用(命名空间内部)
#define MD_TEMPLATE_INTERFACE_IN_NS_DEF(name, outer_name, ...)		MD_TEMPLATE_CUSTOM_TYPE_IN_NS_DEF(name, Itf, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, outer_name, __VA_ARGS__)

/***************************/
/* Meta data of class type */
/***************************/
//无嵌套
#define MD_CLASS_TYPE_DEF(name)		MD_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE)

//嵌套用(接口内部)
#define MD_CLASS_TYPE_IN_INTF_DEF(name, outer_name)		MD_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, outer_name, META_DATA_INTERFACE(outer_name))

//嵌套用(类内部)
#define MD_CLASS_TYPE_IN_CLS_DEF(name, outer_name)		MD_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, outer_name, META_DATA_CLASS_TYPE(outer_name))

//嵌套用(命名空间内部)
#define MD_CLASS_TYPE_IN_NS_DEF(name, outer_name)		MD_CUSTOM_TYPE_IN_NS_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, outer_name)

//构造函数封装
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_BEGIN(cls_name, index) \
	bool cls_name::_MD__CTMCR##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) || !(DataPacket.pReturn)) return false; }
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index)]))
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ(type_name)			(*reinterpret_cast<type_name**>(DataPacket.pReturn)) = new type_name

#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_END() \
		return ret_val; \
	}

//析构函数封装
#define MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name)								MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name)

//成员函数封装
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(cls_name, func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(cls_name, func_name, index)

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)			MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()									MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()

//静态成员函数封装
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_BEGIN(cls_name, func_name, index) \
	bool cls_name::_MD__CTMSMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)	{ if (DataPacket.ParamCount != (param_count)) return false; }
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index)]))
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)			(*reinterpret_cast<type_name*>(DataPacket.pReturn))
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_RET_VAL					(ret_val)

#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_END() \
		return ret_val; \
	}

/** 模板相关 **/
//无嵌套
#define MD_TEMPLATE_CLASS_TYPE_DEF(name, ...)						MD_TEMPLATE_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, __VA_ARGS__)

//嵌套用(接口内部)
#define MD_TEMPLATE_CLASS_TYPE_IN_INTF_DEF(name, outer_name, ...)	MD_TEMPLATE_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, outer_name, META_DATA_INTERFACE(outer_name), __VA_ARGS__)

//嵌套用(类内部)
#define MD_TEMPLATE_CLASS_TYPE_IN_CLS_DEF(name, outer_name, ...)	MD_TEMPLATE_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, outer_name, META_DATA_CLASS_TYPE(outer_name), __VA_ARGS__)

//嵌套用(命名空间内部)
#define MD_TEMPLATE_CLASS_TYPE_IN_NS_DEF(name, outer_name, ...)		MD_TEMPLATE_CUSTOM_TYPE_IN_NS_DEF(name, CT, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE, outer_name, __VA_ARGS__)

/*************************/
/* Meta data of variable */
/*************************/
#define MD_GLOBAL_VARIABLE_DEF(name, parent, type, ptr_level)		const CMetaDataVariable _MD__V##name(#name, &(parent), TypeTraits<type>::GetMetaDataType(), (ptr_level), &(name));

/*************************/
/* Meta data of function */
/*************************/
#define MD_GLOBAL_FUNCTION_DEF_BEGIN(name) \
	class _MD__CLS_FOR_GFUN_##name \
	{ \
	private: \
		_MD__CLS_FOR_GFUN_##name(void) \
		{ \
			CMetaDataFunction *pMDFunction(const_cast<CMetaDataFunction*>(&_MD__F##name));

#define MD_GLOBAL_FUNCTION_DEF_DETAIL(name) \
		} \
	private: \
		static _MD__CLS_FOR_GFUN_##name m_SingleInstance; \
	}; \
	bool _MD__FWRAPPER##name(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_GLOBAL_FUNCTION_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count)) return false; }
#define MD_GLOBAL_FUNCTION_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index)]))
#define MD_GLOBAL_FUNCTION_DEF_DP_RET(type_name)			(*reinterpret_cast<type_name*>(DataPacket.pReturn))
#define MD_GLOBAL_FUNCTION_DEF_RET_VAL						(ret_val)

#define MD_GLOBAL_FUNCTION_DEF_END(name) \
		return ret_val; \
	} \
	const CMetaDataFunction _MD__F##name(#name, &META_DATA_GLOBALSPACE(), reinterpret_cast<void*>(&_MD__FWRAPPER##name)); \
	_MD__CLS_FOR_GFUN_##name _MD__CLS_FOR_GFUN_##name::m_SingleInstance;

/*********************************************/
/* Meta data of function parameters & return */
/*********************************************/
#define MD_GLOBAL_FUNCTION_PARAM_DEF(name, type, ptr_level) \
	pMDFunction->AddParamInfo(new CMetaDataVarBase(#name, pMDFunction, TypeTraits<type>::GetMetaDataType(), (ptr_level)));

#define MD_GLOBAL_FUNCTION_RETURN_DEF(type, ptr_level) \
	pMDFunction->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunction, TypeTraits<type>::GetMetaDataType(), (ptr_level)));
