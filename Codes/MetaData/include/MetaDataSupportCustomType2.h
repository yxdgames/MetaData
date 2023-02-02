#pragma once
/*
 * file			MetaDataSupportCustomType2.h
 * brief		Ϊ�Զ������͵�Ԫ���ݶ����ṩ�����궨��
 * note			None
 * attention	None
 */

#ifndef META_DATA_GLOBALSPACE
#define META_DATA_GLOBALSPACE()			(*(::_MD__GLOBALSPACE__GetMetaData()))
#endif //META_DATA_GLOBALSPACE

/****************************/
/* Meta data of custom type */
/****************************/
//��Ƕ��
#define MD_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type, md_custom_type_id) \
	const md_custom_type name::_MD__##md_obj_pre_name##name(#name, &META_DATA_GLOBALSPACE(), sizeof(name)); \
	name::C_MD__CTM_DID##name name::_MD__CTM_DIDO##name; \
	void name::InitMetaDataManually(void(*initor)(md_custom_type*)) \
	{ \
		_MD__##md_obj_pre_name##name; \
		_MD__CTM_DIDO##name; \
		if (initor) \
			initor(const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
	}

//Ƕ����(�Զ��������ڲ�)
#define MD_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type, md_custom_type_id, outer_name, meta_data_ctm_type_outer_name) \
	const md_custom_type outer_name::name::_MD__##md_obj_pre_name##name(#name, &meta_data_ctm_type_outer_name, sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name; \
	void outer_name::name::InitMetaDataManually(void(*initor)(md_custom_type*)) \
	{ \
		_MD__##md_obj_pre_name##name; \
		_MD__CTM_DIDO##name; \
		if (initor) \
			initor(const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
	}

//Ƕ����(�����ռ��ڲ�)
#define MD_CUSTOM_TYPE_IN_NS_DEF(name, md_obj_pre_name, md_custom_type, md_custom_type_id, outer_name) \
	const md_custom_type outer_name::name::_MD__##md_obj_pre_name##name(#name, &META_DATA_NAME_SPACE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name; \
	void outer_name::name::InitMetaDataManually(void(*initor)(md_custom_type*)) \
	{ \
		_MD__##md_obj_pre_name##name; \
		_MD__CTM_DIDO##name; \
		if (initor) \
			initor(const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
	}

//����������װ
#define MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name) \
	bool cls_name::_MD__CTMDSR(SMetaDataCalledFunctionDataPacket &DataPacket) \
	{ \
		if (DataPacket.ParamCount != 1) return false; \
		delete (*reinterpret_cast<cls_name**>(DataPacket.pParam[0])); \
		return true; \
	}

//��Ա������װ
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

/** ģ����� **/
#include "../../include/MacroTool.h"

//��������
#define MD_TEMPLATE_PARAM_MACRO_NAME(prefix, ...)		MACRO_TOOL_CAT(prefix, MACRO_TOOL_ARG_NUM(__VA_ARGS__))

#define MD_TEMPLATE_PARAM_0()
#define MD_TEMPLATE_PARAM_1(tp1)						typename tp1
#define MD_TEMPLATE_PARAM_2(tp1, tp2)					typename tp1, typename tp2
#ifdef _MSC_VER //msvc
#define MD_TEMPLATE_PARAM_3(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_2(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_4(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_3(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_5(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_4(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_6(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_5(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_7(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_6(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_8(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_7(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_9(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_8(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_10(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_9(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_11(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_10(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_12(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_11(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_13(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_12(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_14(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_13(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_15(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_14(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_16(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_15(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_17(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_16(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_18(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_17(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_19(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_18(__VA_ARGS__))
#define MD_TEMPLATE_PARAM_20(tp1, ...)					typename tp1, MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_19(__VA_ARGS__))

#define MD_TEMPLATE_PARAM(...)							MACRO_TOOL_EXPAND(MD_TEMPLATE_PARAM_MACRO_NAME(MD_TEMPLATE_PARAM_, __VA_ARGS__)(__VA_ARGS__))
#else //_MSC_VER
#define MD_TEMPLATE_PARAM_3(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_2(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_4(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_3(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_5(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_4(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_6(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_5(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_7(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_6(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_8(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_7(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_9(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_8(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_10(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_9(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_11(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_10(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_12(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_11(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_13(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_12(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_14(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_13(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_15(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_14(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_16(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_15(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_17(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_16(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_18(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_17(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_19(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_18(__VA_ARGS__)
#define MD_TEMPLATE_PARAM_20(tp1, ...)					typename tp1, MD_TEMPLATE_PARAM_19(__VA_ARGS__)

#define MD_TEMPLATE_PARAM(...)							MD_TEMPLATE_PARAM_MACRO_NAME(MD_TEMPLATE_PARAM_, __VA_ARGS__)(__VA_ARGS__)
#endif //_MSC_VER

//��Ƕ��
#define MD_TEMPLATE_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type, md_custom_type_id, ...) \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	const md_custom_type name<__VA_ARGS__>::_MD__##md_obj_pre_name##name(#name, &META_DATA_GLOBALSPACE(), sizeof(name<__VA_ARGS__>)); \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	typename name<__VA_ARGS__>::C_MD__CTM_DID##name name<__VA_ARGS__>::_MD__CTM_DIDO##name; \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	void name<__VA_ARGS__>::InitMetaDataManually(void(*initor)(md_custom_type*)) \
	{ \
		_MD__##md_obj_pre_name##name; \
		_MD__CTM_DIDO##name; \
		if (initor) \
			initor(const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
	}

//Ƕ����(�Զ��������ڲ�)
#define MD_TEMPLATE_CUSTOM_TYPE_IN_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type, md_custom_type_id, outer_name, meta_data_ctm_type_outer_name, ...) \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	const md_custom_type outer_name::name<__VA_ARGS__>::_MD__##md_obj_pre_name##name(#name, &meta_data_ctm_type_outer_name, sizeof(name<__VA_ARGS__>)); \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	typename outer_name::name<__VA_ARGS__>::C_MD__CTM_DID##name outer_name::name<__VA_ARGS__>::_MD__CTM_DIDO##name; \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	void outer_name::name<__VA_ARGS__>::InitMetaDataManually(void(*initor)(md_custom_type*)) \
	{ \
		_MD__##md_obj_pre_name##name; \
		_MD__CTM_DIDO##name; \
		if (initor) \
			initor(const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
	}

//Ƕ����(�����ռ��ڲ�)
#define MD_TEMPLATE_CUSTOM_TYPE_IN_NS_DEF(name, md_obj_pre_name, md_custom_type, md_custom_type_id, outer_name, ...) \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	const md_custom_type outer_name::name<__VA_ARGS__>::_MD__##md_obj_pre_name##name(#name, &META_DATA_NAME_SPACE(outer_name), sizeof(name<__VA_ARGS__>)); \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	typename outer_name::name<__VA_ARGS__>::C_MD__CTM_DID##name outer_name::name<__VA_ARGS__>::_MD__CTM_DIDO##name; \
	template<MD_TEMPLATE_PARAM(__VA_ARGS__)> \
	void outer_name::name<__VA_ARGS__>::InitMetaDataManually(void(*initor)(md_custom_type*)) \
	{ \
		_MD__##md_obj_pre_name##name; \
		_MD__CTM_DIDO##name; \
		if (initor) \
			initor(const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
	}
