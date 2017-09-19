#pragma once
/*
 * file			MetaDataSupport2.h
 * brief		ΪԪ���ݶ����ṩͨ�õĺ궨��
 * note			None
 * attention	��MetaDataObjects.cpp�����ã�ʹ�ã�������*.meo�ο�ʹ�ã�����Ҫ���á�
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
	const CMetaDataNameSpace out_ns::name::_MD__NS##name(#name, &META_DATA_NAME_SPACE(out_ns)); \
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

/****************************/
/* Meta data of custom type */
/****************************/
//��Ƕ��
#define MD_CUSTOM_TYPE_DEF(name, md_obj_pre_name, md_custom_type) \
	const md_custom_type name::_MD__##md_obj_pre_name##name(#name, &META_DATA_GLOBALSPACE(), sizeof(name)); \
	name::C_MD__CTM_DID##name name::_MD__CTM_DIDO##name;

//Ƕ����(�����ռ��ڲ�)
#define MD_CUSTOM_TYPE_IN_NS_DEF(name, md_obj_pre_name, md_custom_type, outer_name) \
	const md_custom_type outer_name::name::_MD__##md_obj_pre_name##name(#name, &META_DATA_NAME_SPACE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name;

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

/**************************/
/* Meta data of interface */
/**************************/
//��Ƕ��
#define MD_INTERFACE_DEF(name)						MD_CUSTOM_TYPE_DEF(name, Itf, CMetaDataInterface)

//Ƕ����(�����ռ��ڲ�)
#define MD_INTERFACE_IN_NS_DEF(name, outer_name)	MD_CUSTOM_TYPE_IN_NS_DEF(name, Itf, CMetaDataInterface, outer_name)

//����������װ
#define MD_INTERFACE_DESTRUCTOR_WRAPPER_DEF(intf_name)								MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name)

//��Ա������װ
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(intf_name, func_name, index)

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)							MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DEF_END()									MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()

/***************************/
/* Meta data of class type */
/***************************/
//��Ƕ��
#define MD_CLASS_TYPE_DEF(name)		MD_CUSTOM_TYPE_DEF(name, CT, CMetaDataClassType)

//Ƕ����(���ڲ�)
#define MD_CLASS_TYPE_IN_CLS_DEF(name, outer_name) \
	const CMetaDataClassType outer_name::name::_MD__CT##name(#name, &META_DATA_CLASS_TYPE(outer_name), sizeof(name)); \
	outer_name::name::C_MD__CTM_DID##name outer_name::name::_MD__CTM_DIDO##name;

//Ƕ����(�����ռ��ڲ�)
#define MD_CLASS_TYPE_IN_NS_DEF(name, outer_name)		MD_CUSTOM_TYPE_IN_NS_DEF(name, CT, CMetaDataClassType, outer_name)

//���캯����װ
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

//����������װ
#define MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name)								MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DEF(cls_name)

//��Ա������װ
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(cls_name, func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_BEGIN(cls_name, func_name, index)

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)				MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_PROC_CHECK(param_count)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_OBJ(type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)			MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_PARAM(index, type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)						MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_DP_RET(type_name)
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL								MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_RET_VAL

#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()									MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DEF_END()

//��̬��Ա������װ
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
	const CMetaDataFunction _MD__F##name(#name, &META_DATA_GLOBALSPACE(), _MD__FWRAPPER##name); \
	_MD__CLS_FOR_GFUN_##name _MD__CLS_FOR_GFUN_##name::m_SingleInstance;

/*********************************************/
/* Meta data of function parameters & return */
/*********************************************/
#define MD_GLOBAL_FUNCTION_PARAM_DEF(name, type, ptr_level) \
	pMDFunction->AddParamInfo(new CMetaDataVarBase(#name, pMDFunction, TypeTraits<type>::GetMetaDataType(), (ptr_level)));

#define MD_GLOBAL_FUNCTION_RETURN_DEF(type, ptr_level) \
	pMDFunction->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunction, TypeTraits<type>::GetMetaDataType(), (ptr_level)));