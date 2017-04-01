#pragma once
/*
 * file			MetaDataSupport.h
 * brief		ΪԪ���������������ṩͨ�õĺ궨��
 * note			None
 * attention	��Ҫ����Ԫ���ݵ��﷨�����*.h�ļ�����Ҫ���ñ�ͷ�ļ���
 */

#include "MetaDataSupportBase.h"
#include "MetaDataType.h"
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
//Ƕ����
#define META_DATA_NAME_SPACE_INNER(name, outer_name)	(outer_name::name::_MD__NS##name)

/***************************/
/* Meta data of inner type */
/***************************/
#define META_DATA_INNER_TYPE(name)						(*reinterpret_cast<CMetaDataInnerType*>(TypeTraits<name>::GetMetaDataType()))

/**************************/
/* Meta data of interface */
/**************************/
#define META_DATA_INTERFACE(name)						META_DATA_CUSTOM_TYPE(name, CMetaDataInterface)

#define MD_INTERFACE_DECLARE_BEGIN(name)				MD_CUSTOM_TYPE_DECLARE_BEGIN(name, Itf, CMetaDataInterface)
#define MD_INTERFACE_DECLARE_DETAIL(name)				MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface)

				/*--��ӽӿ�Ԫ������Ϣ--*/
#define MD_INTERFACE_INTERFACE_DEF(parent_intf_name)	MD_CUSTOM_TYPE_INTERFACE_DEF(parent_intf_name)

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_INTERFACE_MEMBER_FUNC_DEF(func_name, index)					MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//��ӳ�Ա��������Ԫ������Ϣ
#define MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//��ӳ�Ա��������ֵԪ������Ϣ
#define MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

#define MD_INTERFACE_DECLARE_END(name)									MD_CUSTOM_TYPE_DECLARE_END(name)

/***************************/
/* Meta data of class type */
/***************************/
#define META_DATA_CLASS_TYPE(name)							META_DATA_CUSTOM_TYPE(name, CMetaDataClassType)
//Ƕ����
#define META_DATA_CLASS_TYPE_INNER(name, outer_name)		META_DATA_CUSTOM_TYPE_INNER(name, outer_name, CT)

#define MD_CLASS_TYPE_DECLARE_BEGIN(name)					MD_CUSTOM_TYPE_DECLARE_BEGIN(name, CT, CMetaDataClassType)
#define MD_CLASS_TYPE_DECLARE_DETAIL(name)					MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataClassType)

				/*--��ӻ���Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_BASE_CLASS_DEF(base_class_name)		MD_CUSTOM_TYPE_BASE_CLASS_DEF(base_class_name)

				/*--��ӽӿ�Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_INTERFACE_DEF(intf_name)				MD_CUSTOM_TYPE_INTERFACE_DEF(intf_name)

				/*--��ӹ��캯��Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index)	MD_CUSTOM_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index)
#define MD_CLASS_TYPE_CONSTRUCTOR_DEF(index)				MD_CUSTOM_TYPE_CONSTRUCTOR_DEF(index)

					//��ӹ��캯������Ԫ������Ϣ
#define MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level)

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)		MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_CLASS_TYPE_MEMBER_FUNC_DEF(func_name, index)					MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//��ӳ�Ա��������Ԫ������Ϣ
#define MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//��ӳ�Ա��������ֵԪ������Ϣ
#define MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level)

				/*--��Ӿ�̬��Ա����Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)	MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index)				MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index)

					//��Ӿ�̬��Ա��������Ԫ������Ϣ
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)	MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//��Ӿ�̬��Ա��������ֵԪ������Ϣ
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level)		MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--��Ӿ�̬��Ա����Ԫ������Ϣ--*/
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