#pragma once
/*
 * file			MetaDataSupportCustomType2.h
 * brief		为自定义类型的元数据定义提供基础宏定义
 * note			None
 * attention	None
 */

#ifndef META_DATA_GLOBALSPACE
#define META_DATA_GLOBALSPACE()			(*(::_MD__GLOBALSPACE__GetMetaData()))
#endif //META_DATA_GLOBALSPACE

/****************************/
/* Meta data of custom type */
/****************************/
//无嵌套
#define MD_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type) \
	const md_custom_type name::_MD__##md_obj_pre_name##name(#name, &META_DATA_GLOBALSPACE(), sizeof(name)); \
	name::C_MD__CTM_DID##name name::_MD__CTM_DIDO##name;

//嵌套用(命名空间内部)
#define MD_CUSTOM_TYPE_IN_NS_DEF(name, md_obj_pre_name, md_custom_type, outer_name) \
	const md_custom_type outer_name::name::_MD__##md_obj_pre_name##name(#name, &META_DATA_NAME_SPACE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name;

//析构函数封装
#define MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name) \
	bool cls_name::_MD__CTMDSR(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		if (DataPacket.ParamCount != 1) return false; \
		delete (*reinterpret_cast<cls_name**>(DataPacket.pParam[0])); \
		return true; \
	}

//成员函数封装
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(cls_name, func_name, index) \
	bool cls_name::_MD__CTMMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		bool ret_val(true);

#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)		{ if (DataPacket.ParamCount != (param_count) + 1) return false; }
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)				(*reinterpret_cast<type_name**>(DataPacket.pParam[0]))
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)	(*reinterpret_cast<type_name*>(DataPacket.pParam[(index) + 1]))
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)			(*reinterpret_cast<type_name*>(DataPacket.pReturn))
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL						(ret_val)

#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END() \
		return ret_val; \
	}