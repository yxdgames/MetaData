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
#define MD_NAME_SPACE_DEF(name)						CMetaDataNameSpace _MD__NS##name(#name, &META_DATA_MODULE());
#define MD_NAME_SPACE_INNER_DEF(name, out_ns)		CMetaDataNameSpace _MD__NS##name(#name, &(out_ns));

/***************************/
/* Meta data of inner type */
/***************************/
#define MD_INNER_TYPE_DEF(name)						CMetaDataInnerType _MD__InnerType##name(#name, &_MD__Module, sizeof(name));
#define MD_INNER_TYPE_2_DEF(name1, name2)			CMetaDataInnerType _MD__InnerType##name1##name2(#name1" "#name2, &_MD__Module, sizeof(name1 name2));

/**************************/
/* Meta data of interface */
/**************************/
#define MD_INTERFACE_DEF(name) \
	CMetaDataInterface name::_MD__Itf##name(#name, &META_DATA_MODULE(), sizeof(name)); \
	name::C_MD__Itf_DID##name name::_MD__Itf_DIDO##name;

//成员函数封装
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, intf_name) \
	bool intf_name::_MD__CMF##intf_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_1_DEF_BEGIN(index, func_name, intf_name, outer_name) \
	bool outer_name::intf_name::_MD__CMF##intf_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) + 1) return false; }
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)				(*reinterpret_cast<type_name**>(DataPacket.pParam[0]))
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)		(*reinterpret_cast<type_name*>(DataPacket.pParam[(index) + 1]))
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)				(*reinterpret_cast<type_name*>(DataPacket.pReturn))
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL						(ret_val)

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_END() \
		return ret_val; \
	}

/***************************/
/* Meta data of class type */
/***************************/
//无嵌套
#define MD_CLASS_TYPE_DEF(name) \
	CMetaDataClassType name::_MD__CT##name(#name, &META_DATA_MODULE(), sizeof(name)); \
	name::C_MD__CT_DID##name name::_MD__CT_DIDO##name;

//一层嵌套用(类内部)
#define MD_CLASS_TYPE_IN_CLS_1_DEF(name, outer_name) \
	CMetaDataClassType outer_name::name::_MD__CT##name(#name, &META_DATA_CLASS_TYPE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CT_DID##name outer_name::name::_MD__CT_DIDO##name;

//一层以上嵌套用(类内部)
#define MD_CLASS_TYPE_IN_CLS_2_DEF(name, outer_name1, outer_name2) \
	CMetaDataClassType outer_name2::outer_name1::name::_MD__CT##name(#name, &META_DATA_CLASS_TYPE_INNER(outer_name1, outer_name2), sizeof(name)); \
	outer_name2::outer_name1::name::C_MD__CT_DID##name outer_name2::outer_name1::name::_MD__CT_DIDO##name;

//一层嵌套用(命名空间内部)
#define MD_CLASS_TYPE_IN_NS_1_DEF(name, outer_name) \
	CMetaDataClassType outer_name::name::_MD__CT##name(#name, &META_DATA_NAME_SPACE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CT_DID##name outer_name::name::_MD__CT_DIDO##name;

//一层以上嵌套用(命名空间类内部)
#define MD_CLASS_TYPE_IN_NS_2_DEF(name, outer_name1, outer_name2) \
	CMetaDataClassType outer_name2::outer_name1::name::_MD__CT##name(#name, &META_DATA_NAME_SPACE_INNER(outer_name1, outer_name2), sizeof(name)); \
	outer_name2::outer_name1::name::C_MD__CT_DID##name outer_name2::outer_name1::name::_MD__CT_DIDO##name;

//构造函数封装
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_BEGIN(index, cls_name) \
	bool cls_name::_MD__CCR##cls_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_1_DEF_BEGIN(index, cls_name, outer_name) \
	bool outer_name::cls_name::_MD__CCR##cls_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) || !(DataPacket.pReturn)) return false; }
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index)]))
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_NEW_OBJ(type_name)			(*reinterpret_cast<type_name**>(DataPacket.pReturn)) = new type_name

#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DEF_END() \
		return ret_val; \
	}

//成员函数封装
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, cls_name) \
	bool cls_name::_MD__CMF##cls_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_1_DEF_BEGIN(index, func_name, cls_name, outer_name) \
	bool outer_name::cls_name::_MD__CMF##cls_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) + 1) return false; }
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_THIS(type_name)				(*reinterpret_cast<type_name**>(DataPacket.pParam[0]))
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index) + 1]))
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)				(*reinterpret_cast<type_name*>(DataPacket.pReturn))
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL						(ret_val)

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_END() \
		return ret_val; \
	}

//静态成员函数封装
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DEF_BEGIN(index, func_name, cls_name) \
	bool cls_name::_MD__CSMF##cls_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_1_DEF_BEGIN(index, func_name, cls_name, outer_name) \
	bool outer_name::cls_name::_MD__CSMF##cls_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
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
	bool _MD__CF##name(SMetaDataCalledFunctionDataPacket &DataPacket) \
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