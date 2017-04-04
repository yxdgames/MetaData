#pragma once
/*
 * file			MetaDataSupport.h
 * brief		ΪԪ���������������ṩͨ�õĺ궨��
 * note			None
 * attention	��Ҫ����Ԫ���ݵ��﷨�����*.h�ļ�����Ҫ���ñ�ͷ�ļ���
 */

#include "MetaDataNameSpace.h"
#include "MetaDataInterface.h"
#include "MetaDataClassType.h"
#include "TypeTraits.h"

/***********************/
/* Meta data of module */
/***********************/
#define META_DATA_MODULE()								(*(::_MD__MODULE__GetMetaData()))

/***************************/
/* Meta data of name space */
/***************************/
#define META_DATA_NAME_SPACE(name)						(*(name::_MD__NS__GetMetaData()))

#define MD_NAME_SPACE_DECLARE(name) \
	extern CMetaDataNameSpace _MD__NS##name; \
	extern CMetaDataNameSpace *_MD__NS__GetMetaData(void);

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

				/*--��ӽӿ�Ԫ������Ϣ--*/
#define MD_INTERFACE_INTERFACE_DEF(parent_intf_name)	MD_CUSTOM_TYPE_INTERFACE_DEF(parent_intf_name)

				/*--�����������Ԫ������Ϣ--*/
#define MD_INTERFACE_DESTRUCTOR_WRAPPER_DECLARE()						MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
#define MD_INTERFACE_DESTRUCTOR_DEF()									MD_CUSTOM_TYPE_DESTRUCTOR_DEF()

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

				/*--�����������Ԫ������Ϣ--*/
#define MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DECLARE()			MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
#define MD_CLASS_TYPE_DESTRUCTOR_DEF()						MD_CUSTOM_TYPE_DESTRUCTOR_DEF()

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
