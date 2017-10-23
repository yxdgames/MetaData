#pragma once
/*
 * file			MetaDataSupportCustomType.h
 * brief		Ϊ�Զ������͵�Ԫ���������������ṩ�����궨��
 * note			None
 * attention	None
 */

//compile option.
#define CO_MD_CUSTOM_TYPE_EXTRA

#define INT_FOR_MD_SIZEOF		int

#define TYPE_BYTE4_FOR_MD		unsigned long
#define TYPE_BYTE2_FOR_MD		unsigned short

/****************************/
/* Meta data of custom type */
/****************************/
#define META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id) \
	(*reinterpret_cast<const md_custom_type*>(AssertMetaData(TypeTraits<name>::GetMetaDataType(), md_custom_type_id)))
#define META_DATA_CUSTOM_TYPE_NO_ASSERT(name, md_custom_type) \
	(*reinterpret_cast<const md_custom_type*>(TypeTraits<name>::GetMetaDataType()))

#define MD_CUSTOM_TYPE_DECLARE_BEGIN(name, md_obj_pre_name, md_custom_type) \
	public: \
		virtual const CMetaDataType *GetType(void)			{ return &_MD__##md_obj_pre_name##name; } \
		static const md_custom_type *GetMetaData(void)		{ return &_MD__##md_obj_pre_name##name; } \
	private: \
		static const md_custom_type _MD__##md_obj_pre_name##name; \
		__MD_CUSTOM_TYPE_MEMBER_EXTRA
#define MD_CUSTOM_TYPE_DECLARE_BEGIN_NO_VIRTUAL(name, md_obj_pre_name, md_custom_type) \
	public: \
		const CMetaDataType *GetType(void)					{ return &_MD__##md_obj_pre_name##name; } \
		static const md_custom_type *GetMetaData(void)		{ return &_MD__##md_obj_pre_name##name; } \
	private: \
		static const md_custom_type _MD__##md_obj_pre_name##name;

#define MD_CUSTOM_TYPE_DECLARE_DETAIL(name, md_custom_type, md_custom_type_id, cls_descript) \
	private: \
		static class cls_descript C_MD__CTM_DID##name \
		{ \
		public: \
			C_MD__CTM_DID##name() \
			{ \
				char *pClsName(#name); \
				char *pDsrName("~"#name); \
				md_custom_type &MDType(*const_cast<md_custom_type*>(&META_DATA_CUSTOM_TYPE(name, md_custom_type, md_custom_type_id))); \
				name *pTemObj(reinterpret_cast<name*>(sizeof(INT_FOR_MD_SIZEOF))); \
				name *pTemObj2(reinterpret_cast<name*>(0)); \
				CMetaDataFunction *pMDFunc;

				/*--����GUID--*/
#define MD_CUSTOM_TYPE_GUID_DEF(data1, data2, data3, data4_1, data4_2, data4_3, data4_4, data4_5, data4_6, data4_7, data4_8) \
	struct { \
		TYPE_BYTE4_FOR_MD data_1; \
		TYPE_BYTE2_FOR_MD data_2; \
		TYPE_BYTE2_FOR_MD data_3; \
		TDByte data_4[8]; \
	} guid_data = { (data1), (data2), (data3), { (data4_1), (data4_2), (data4_3), (data4_4), (data4_5), (data4_6), (data4_7), (data4_8) } }; \
	MDType.SetGUID(static_cast<void*>(&guid_data));

				/*--��ӻ���Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_BASE_CLASS_DEF(base_class_name) \
	MDType.AddBaseType(&META_DATA_CUSTOM_TYPE(base_class_name, CMetaDataClassType, D_META_DATA_TYPE_ID_CLASS_TYPE), reinterpret_cast<TDUIntPtr>(static_cast<base_class_name*>(pTemObj)) - sizeof(INT_FOR_MD_SIZEOF));

				/*--��ӽӿ�Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_INTERFACE_DEF(intf_name) \
	MDType.AddInterface(&META_DATA_CUSTOM_TYPE(intf_name, CMetaDataInterface, D_META_DATA_TYPE_ID_INTERFACE), reinterpret_cast<TDUIntPtr>(static_cast<intf_name*>(pTemObj)) - sizeof(INT_FOR_MD_SIZEOF));

				/*--��ӹ��캯��Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(index) \
	private: \
		static bool _MD__CTMCR##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CUSTOM_TYPE_CONSTRUCTOR_DEF(index) \
	static CMetaDataFunction _MD__CR##index(pClsName, &MDType, _MD__CTMCR##index); \
	MDType.AddConstructor(&_MD__CR##index); \
	pMDFunc = &_MD__CR##index; \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &MDType, 1));

					//��ӹ��캯������Ԫ������Ϣ
#define MD_CUSTOM_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, TypeTraits<type>::GetMetaDataType(), (ptr_level)));

				/*--�����������Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_DESTRUCTOR_WRAPPER_DECLARE() \
	private: \
		static bool _MD__CTMDSR(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CUSTOM_TYPE_DESTRUCTOR_DEF() \
	static CMetaDataFunction _MD__DSR(pDsrName, &MDType, _MD__CTMDSR); \
	MDType.SetDestructor(&_MD__DSR); \
	pMDFunc = &_MD__DSR; \
	pMDFunc->AddParamInfo(new CMetaDataVarBase("this", pMDFunc, &MDType, 1));

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index) \
	private: \
		static bool _MD__CTMMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index) \
	static CMetaDataFunction _MD__MF##func_name##index(#func_name, &MDType, _MD__CTMMF##func_name##index); \
	MDType.AddMemberFunc(&_MD__MF##func_name##index); \
	pMDFunc = &_MD__MF##func_name##index; \
	pMDFunc->AddParamInfo(new CMetaDataVarBase("this", pMDFunc, &MDType, 1));

					//��ӳ�Ա��������Ԫ������Ϣ
#define MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, TypeTraits<type>::GetMetaDataType(), (ptr_level)));
					//��ӳ�Ա��������ֵԪ������Ϣ
#define MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, TypeTraits<type>::GetMetaDataType(), (ptr_level)));

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level) \
	static CMetaDataCustomTypeMemberVar _MD__MV##var_name(#var_name, &MDType, TypeTraits<var_type>::GetMetaDataType(), (ptr_level), reinterpret_cast<TDUIntPtr>(&(pTemObj2->var_name))); \
	MDType.AddMemberVar(&_MD__MV##var_name);

				/*--�������Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_PROPERTY_DEF(prop_name, cls, cls_prop_type, set, get, prop_type, ptr_level) \
	static TPropertyBase<cls, cls_prop_type> _MD__CTMPROP##prop_name(&cls::set, &cls::get); \
	static CMetaDataCustomTypeProperty _MD__PROP##prop_name(#prop_name, &MDType, TypeTraits<prop_type>::GetMetaDataType(), (ptr_level), &_MD__CTMPROP##prop_name); \
	MDType.AddProperty(&_MD__PROP##prop_name);
#define MD_CUSTOM_TYPE_MEMBER_PROPERTY_DEF(prop_name, prop_type, ptr_level) \
	static CMetaDataCustomTypeProperty _MD__PROP##prop_name(#prop_name, &MDType, TypeTraits<prop_type>::GetMetaDataType(), (ptr_level), reinterpret_cast<TDUIntPtr>(&(pTemObj2->prop_name))); \
	MDType.AddProperty(&_MD__PROP##prop_name);

				/*--��Ӿ�̬��Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index) \
	private: \
		static bool _MD__CTMSMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_DEF(func_name, index) \
	static CMetaDataFunction _MD__SMF##func_name##index(#func_name, &MDType, _MD__CTMSMF##func_name##index); \
	MDType.AddStaticMemberFunc(&_MD__SMF##func_name##index); \
	pMDFunc = &_MD__SMF##func_name##index;

					//��Ӿ�̬��Ա��������Ԫ������Ϣ
#define MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, TypeTraits<type>::GetMetaDataType(), (ptr_level)));
					//��Ӿ�̬��Ա��������ֵԪ������Ϣ
#define MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, TypeTraits<type>::GetMetaDataType(), (ptr_level)));

				/*--��Ӿ�̬��Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level) \
	static CMetaDataVariable _MD__SMV##var_name(#var_name, &MDType, TypeTraits<var_type>::GetMetaDataType(), (ptr_level), &var_name); \
	MDType.AddStaticMemberVar(&_MD__SMV##var_name);

				/*--����AsTypeEx����ָ��--*/
#define MD_CUSTOM_TYPE_AS_TYPE_EX_DEF(pfun_as_type_ex) \
	MDType.SetAsTypeExFunPtr(pfun_as_type_ex);

#define MD_CUSTOM_TYPE_DECLARE_END(name) \
				pMDFunc = nullptr; \
			} \
		} _MD__CTM_DIDO##name;

/*********************************************/
/*       __MD_CUSTOM_TYPE_MEMBER_EXTRA       */
/*********************************************/
#ifdef CO_MD_CUSTOM_TYPE_EXTRA
#define __MD_CUSTOM_TYPE_MEMBER_EXTRA \
	public: \
		bool IsTypeOf(const CMetaDataType *pType) \
		{ \
			return this->GetType()->IsTypeOf(pType); \
		} \
		bool IsTypeOf(const TDGUID &guid) \
		{ \
			return this->GetType()->IsTypeOf(guid); \
		} \
		template <typename T> \
		bool IsTypeOf(void) \
		{ \
			return this->IsTypeOf(TypeTraits<T>::GetMetaDataType()); \
		} \
		void *AsType(const CMetaDataType *pType) \
		{ \
			return this->GetType()->AsType(this->GetTrueSelf(), pType); \
		} \
		void *AsType(const TDGUID &guid) \
		{ \
			return this->GetType()->AsType(this->GetTrueSelf(), guid); \
		} \
		template <typename T> \
		T *AsType(void) \
		{ \
			return reinterpret_cast<T*>(this->AsType(TypeTraits<T>::GetMetaDataType())); \
		} \
	protected: \
		virtual void *GetTrueSelf(void) \
		{ \
			return this; \
		}
#else
#define __MD_CUSTOM_TYPE_MEMBER_EXTRA
#endif //CO_MD_CUSTOM_TYPE_EXTRA