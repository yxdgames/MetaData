#pragma once
/*
 * file			MetaDataSupport2.h
 * brief		为元数据定义提供通用的宏定义
 * note			None
 * attention	由MetaDataObjects.cpp来引用（使用）。其它*.meo参考使用，不需要引用。
 */

/***********************/
/* Meta data of module */
/***********************/
//None

/***************************/
/* Meta data of name space */
/***************************/
#define MD_NAME_SPACE_DEF(name) \
	CMetaDataNameSpace _MD__NS##name(#name, &META_DATA_MODULE()); \
	CMetaDataNameSpace *_MD_NS__GetMetaData(void) \
	{ \
		return &_MD__NS##name; \
	}
#define MD_NAME_SPACE_INNER_DEF(name, out_ns) \
	CMetaDataNameSpace _MD__NS##name(#name, &META_DATA_NAME_SPACE(out_ns)); \
	CMetaDataNameSpace *_MD_NS__GetMetaData(void) \
	{ \
		return &_MD__NS##name; \
	}

/***************************/
/* Meta data of inner type */
/***************************/
#define MD_INNER_TYPE_DEF(name)						CMetaDataInnerType _MD__InnerType##name(#name, &_MD__Module, sizeof(name));
#define MD_INNER_TYPE_2_DEF(name1, name2)			CMetaDataInnerType _MD__InnerType##name1##name2(#name1" "#name2, &_MD__Module, sizeof(name1 name2));

/****************************/
/* Meta data of custom type */
/****************************/
#define MD_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type) \
	md_custom_type name::_MD__##md_obj_pre_name##name(#name, &META_DATA_MODULE(), sizeof(name)); \
	name::C_MD__CTM_DID##name name::_MD__CTM_DIDO##name;

//成员函数封装
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, cls_name) \
	bool cls_name::_MD__CTMMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) + 1) return false; }
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)				(*reinterpret_cast<type_name**>(DataPacket.pParam[0]))
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index) + 1]))
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)			(*reinterpret_cast<type_name*>(DataPacket.pReturn))
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL						(ret_val)

#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END() \
		return ret_val; \
	}

/**************************/
/* Meta data of interface */
/**************************/
#define MD_INTERFACE_DEF(name)						MD_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface)

//成员函数封装
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, intf_name)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, intf_name)

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_END()									MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()

/***************************/
/* Meta data of class type */
/***************************/
//无嵌套
#define MD_CLASS_TYPE_DEF(name)		MD_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType)

//嵌套用(类内部)
#define MD_CLASS_TYPE_IN_CLS_DEF(name, outer_name) \
	CMetaDataClassType outer_name::name::_MD__CT##name(#name, &META_DATA_CLASS_TYPE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name;

//嵌套用(命名空间内部)
#define MD_CLASS_TYPE_IN_NS_DEF(name, outer_name) \
	CMetaDataClassType outer_name::name::_MD__CT##name(#name, &META_DATA_NAME_SPACE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name;

//构造函数封装
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_BEGIN(index, cls_name) \
	bool cls_name::_MD__CTMCR##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) || !(DataPacket.pReturn)) return false; }
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index)]))
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ(type_name)			(*reinterpret_cast<type_name**>(DataPacket.pReturn)) = new type_name

#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_END() \
		return ret_val; \
	}

//成员函数封装
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, cls_name)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, cls_name)

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)			MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()									MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()

//静态成员函数封装
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, cls_name) \
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

/*************************/
/* Meta data of variable */
/*************************/
#define MD_GLOBAL_VARIABLE_DEF(name, parent, type, ptr_level)		CMetaDataVariable _MD__V##name(#name, &(parent), &(type), (ptr_level), &(name));

/*************************/
/* Meta data of function */
/*************************/
#define MD_GLOBAL_FUNCTION_DEF_BEGIN(name) \
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
	CMetaDataFunction _MD__F##name(#name, &META_DATA_MODULE(), _MD__CF##name);