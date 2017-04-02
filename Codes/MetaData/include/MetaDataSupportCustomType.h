#pragma once
/*
 * file			MetaDataSupportCustomType.h
 * brief		�Զ�������Ԫ�������������궨��
 * note			None
 * attention	None
 */

//compile option.
#define CO_MD_CUSTOM_TYPE_EXTRA

/****************************/
/* Meta data of custom type */
/****************************/
#define META_DATA_CUSTOM_TYPE(name, md_custom_type)			(*reinterpret_cast<md_custom_type*>(TypeTraits<name>::GetMetaDataType()))

#define MD_CUSTOM_TYPE_DECLARE_BEGIN(name, md_obj_pre_name, md_custom_type) \
	public: \
		virtual CMetaDataType *GetType(void)			{ return &_MD__##md_obj_pre_name##name; } \
		static md_custom_type *GetMetaData(void)	{ return &_MD__##md_obj_pre_name##name; } \
		static md_custom_type _MD__##md_obj_pre_name##name; \
		__MD_CUSTOM_TYPE_MEMBER_EXTRA

#define MD_CUSTOM_TYPE_DECLARE_DETAIL(name, md_custom_type) \
	private: \
		static class C_MD__CTM_DID##name \
		{ \
		public: \
			C_MD__CTM_DID##name() \
			{ \
				char *pClsName(#name); \
				md_custom_type &MDType(META_DATA_CUSTOM_TYPE(name, md_custom_type)); \
				name *pTemObj(reinterpret_cast<name*>(sizeof(int))); \
				name *pTemObj2(reinterpret_cast<name*>(0)); \
				CMetaDataFunction *pMDFunc;

				/*--��ӻ���Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_BASE_CLASS_DEF(base_class_name) \
	MDType.AddBaseType(&META_DATA_CUSTOM_TYPE(base_class_name, CMetaDataClassType), reinterpret_cast<unsigned int>(static_cast<base_class_name*>(pTemObj)) - sizeof(int));

				/*--��ӽӿ�Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_INTERFACE_DEF(intf_name) \
	MDType.AddInterface(&META_DATA_CUSTOM_TYPE(intf_name, CMetaDataInterface), reinterpret_cast<unsigned int>(static_cast<intf_name*>(pTemObj)) - sizeof(int));

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
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func_name, index) \
	private: \
		static bool _MD__CTMMF##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CUSTOM_TYPE_MEMBER_FUNC_DEF(func_name, index) \
	static CMetaDataFunction _MD__MF##func_name##index(#func_name, &MDType, _MD__CTMMF##func_name##index); \
	MDType.AddMemberFunc(&_MD__MF##func_name##index); \
	pMDFunc = &_MD__MF##func_name##index;

					//��ӳ�Ա��������Ԫ������Ϣ
#define MD_CUSTOM_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//��ӳ�Ա��������ֵԪ������Ϣ
#define MD_CUSTOM_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

				/*--��ӳ�Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_MEMBER_VAR_DEF(var_name, var_type, ptr_level) \
	static CMetaDataCustomTypeMemberVar _MD__MV##var_name(#var_name, &MDType, &(var_type), (ptr_level), reinterpret_cast<unsigned int>(&(pTemObj2->var_name))); \
	MDType.AddMemberVar(&_MD__MV##var_name);

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
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//��Ӿ�̬��Ա��������ֵԪ������Ϣ
#define MD_CUSTOM_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

				/*--��Ӿ�̬��Ա����Ԫ������Ϣ--*/
#define MD_CUSTOM_TYPE_STATIC_MEMBER_VAR_DEF(var_name, var_type, ptr_level) \
	static CMetaDataVariable _MD__SMV##var_name(#var_name, &MDType, &(var_type), (ptr_level), &var_name); \
	MDType.AddStaticMemberVar(&_MD__SMV##var_name);

#define MD_CUSTOM_TYPE_DECLARE_END(name) \
				pMDFunc = NULL; \
			} \
		} _MD__CTM_DIDO##name;

/*********************************************/
/*       __MD_CUSTOM_TYPE_MEMBER_EXTRA       */
/*********************************************/
#ifdef CO_MD_CUSTOM_TYPE_EXTRA
#define __MD_CUSTOM_TYPE_MEMBER_EXTRA \
	public: \
		template <typename T> \
		bool IsTypeOf(void) \
		{ \
			return this->GetType()->IsTypeOf(TypeTraits<T>::GetMetaDataType()); \
		} \
		template <typename T> \
		T *AsType(void) \
		{ \
			return reinterpret_cast<T*>(this->GetType()->AsType(this->GetTrueSelf(), TypeTraits<T>::GetMetaDataType())); \
		} \
	private: \
		virtual void *GetTrueSelf(void) \
		{ \
			return this; \
		}
#else
#define __MD_CUSTOM_TYPE_MEMBER_EXTRA
#endif //CO_MD_CUSTOM_TYPE_EXTRA