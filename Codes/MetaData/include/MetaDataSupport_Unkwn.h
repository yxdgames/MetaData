#pragma once
/*
* file			MetaDataSupport_Unkwn.h
* brief			ΪIUnkwnԪ���������������ṩͨ�õĺ궨��
* note			None
* attention		��Ҫ����IUnkwnԪ���ݵ��﷨�����*.h�ļ�����Ҫ���ñ�ͷ�ļ���
*/

#include "MetaDataSupportCustomType.h"

#ifndef CLASS_DESCRIPT_FOR_MD_SUPPORT
#define CLASS_DESCRIPT_FOR_MD_SUPPORT
#endif //CLASS_DESCRIPT_FOR_MD_SUPPORT

/**********************************/
/* Meta data of unknown interface */
/**********************************/
#define META_DATA_UNKWN_INTERFACE(name)						META_DATA_CUSTOM_TYPE(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE)
#define META_DATA_UNKWN_INTERFACE_NO_ASSERT(name)			META_DATA_CUSTOM_TYPE_NO_ASSERT(name, CMetaDataInterface)

#define MD_UNKWN_INTERFACE_DECLARE_BEGIN(name)				MD_CUSTOM_TYPE_DECLARE_BEGIN_NO_VIRTUAL(name, Iukn, CMetaDataInterface)
#define MD_UNKWN_INTERFACE_DECLARE_DETAIL(name)				MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, CLASS_DESCRIPT_FOR_MD_SUPPORT)
#define MD_UNKWN_INTERFACE_DECLARE_DETAIL_KERNEL(name)		MD_CUSTOM_TYPE_DECLARE_DETAIL(name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE, CLASS_DESCRIPT)

				/*--����GUID--*/
#define MD_UNKWN_INTERFACE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8) \
	MD_CUSTOM_TYPE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8)

				/*--���δ֪�ӿ�Ԫ������Ϣ--*/
#define MD_UNKWN_INTERFACE_UNKWN_INTERFACE_DEF(parent_intf_name)			MD_CUSTOM_TYPE_UNKNOWN_INTERFACE_DEF(parent_intf_name)

				/*--�����������Ԫ������Ϣ--*/
#define MD_UNKWN_INTERFACE_DESTRUCTOR_WRAPPER_DECLARE()						MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
#define MD_UNKWN_INTERFACE_DESTRUCTOR_DEF()									MD_CUSTOM_TYPE_DESTRUCTOR_DEF()

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)	MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index)
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_DEF(func_name, index)				MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index)

					//��ӳ�Ա��������Ԫ������Ϣ
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)		MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level)
					//��ӳ�Ա��������ֵԪ������Ϣ
#define MD_UNKWN_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)			MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level)

				/*--�������Ԫ������Ϣ--*/
#define MD_UNKWN_INTERFACE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level) \
	MD_CUSTOM_TYPE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level)

#define MD_UNKWN_INTERFACE_DECLARE_END(name)								MD_CUSTOM_TYPE_DECLARE_END(name)