#pragma once
/*
 * file			MetaDataSupport.h
 * brief		为元数据声明、引用提供通用的宏定义
 * note			None
 * attention	有要生成元数据的语法对象的*.h文件，需要引用本头文件。
 */

//compile option.
#define CO_MD_CLASS_TYPE_EXTRA

/***********************/
/* Meta data of module */
/***********************/
#define META_DATA_MODULE()								(::_MD__Module)

/***************************/
/* Meta data of name space */
/***************************/
#define META_DATA_NAME_SPACE(name)						(name::_MD__NS##name)
//嵌套用
#define META_DATA_NAME_SPACE_INNER(name, outer_name)	(outer_name::name::_MD__NS##name)

/***************************/
/* Meta data of inner type */
/***************************/
#define META_DATA_INNER_TYPE(name)						(*reinterpret_cast<CMetaDataInnerType*>(TypeTraits<name>::GetMetaDataType()))

/**************************/
/* Meta data of interface */
/**************************/
#define META_DATA_INTERFACE(name)						(*reinterpret_cast<CMetaDataInterface*>(TypeTraits<name>::GetMetaDataType()))

#define MD_INTERFACE_DECLARE_BEGIN(name) \
	public: \
		virtual CMetaDataType *GetType(void)			{ return &_MD__Itf##name; } \
		static CMetaDataInterface *GetMetaData(void)	{ return &_MD__Itf##name; } \
		static CMetaDataInterface _MD__Itf##name; \
		__MD_INTERFACE_MEMBER_EXTRA

#define MD_INTERFACE_DECLARE_DETAIL(name) \
	private: \
		static class C_MD__Itf_DID##name \
		{ \
		public: \
			C_MD__Itf_DID##name() \
			{ \
				CMetaDataFunction *pMDFunc;

				/*--添加接口元数据信息--*/
#define MD_INTERFACE_INTERFACE_DEF(intf_name, parent_intf_name) \
	META_DATA_INTERFACE(intf_name).AddInterface(&META_DATA_INTERFACE(parent_intf_name), reinterpret_cast<unsigned int>(static_cast<parent_intf_name*>(reinterpret_cast<intf_name*>(sizeof(int)))) - sizeof(int));

				/*--添加成员函数元数据信息--*/
#define MD_INTERFACE_MEMBER_FUNC_WRAPPER_DECLARE(intf_name, func_name, index) \
	static bool _MD__CMF##intf_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_INTERFACE_MEMBER_FUNC_DEF(intf_name, func_name, index) \
	static CMetaDataFunction _MD__MF##intf_name##func_name##index(#func_name, &META_DATA_INTERFACE(intf_name), intf_name::_MD__CMF##intf_name##func_name##index); \
	META_DATA_INTERFACE(intf_name).AddMemberFunc(&_MD__MF##intf_name##func_name##index); \
	pMDFunc = &_MD__MF##intf_name##func_name##index;

					//添加成员函数参数元数据信息
#define MD_INTERFACE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//添加成员函数返回值元数据信息
#define MD_INTERFACE_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

#define MD_INTERFACE_DECLARE_END(name) \
				pMDFunc = NULL; \
			} \
		} _MD__Itf_DIDO##name;

/***************************/
/* Meta data of class type */
/***************************/
#define META_DATA_CLASS_TYPE(name)							(*reinterpret_cast<CMetaDataClassType*>(TypeTraits<name>::GetMetaDataType()))
//嵌套用
#define META_DATA_CLASS_TYPE_INNER(name, outer_name)		(outer_name::name::_MD__CT##name)

#define MD_CLASS_TYPE_DECLARE_BEGIN(name) \
	public: \
		virtual CMetaDataType *GetType(void)			{ return &_MD__CT##name; } \
		static CMetaDataClassType *GetMetaData(void)	{ return &_MD__CT##name; } \
		static CMetaDataClassType _MD__CT##name; \
		__MD_CLASS_TYPE_MEMBER_EXTRA

#define MD_CLASS_TYPE_DECLARE_DETAIL(name) \
	private: \
		static class C_MD__CT_DID##name \
		{ \
		public: \
			C_MD__CT_DID##name() \
			{ \
				CMetaDataFunction *pMDFunc;

				/*--添加基类元数据信息--*/
#define MD_CLASS_TYPE_BASE_CLASS_DEF(cls_name, base_class_name) \
	META_DATA_CLASS_TYPE(cls_name).AddBaseType(&META_DATA_CLASS_TYPE(base_class_name), reinterpret_cast<unsigned int>(static_cast<base_class_name*>(reinterpret_cast<cls_name*>(sizeof(int)))) - sizeof(int));

//#define MD_CLASS_TYPE_BASE_CLASS_1_DEF(cls_name, base_class_name, base_cls_outer_name) \
//	META_DATA_CLASS_TYPE(cls_name).AddBaseType(&META_DATA_CLASS_TYPE_INNER(base_class_name, base_cls_outer_name), \
//												reinterpret_cast<unsigned int>(static_cast<base_cls_outer_name::base_class_name*>(reinterpret_cast<cls_name*>(sizeof(int)))) - sizeof(int));

				/*--添加接口元数据信息--*/
#define MD_CLASS_TYPE_INTERFACE_DEF(cls_name, intf_name) \
	META_DATA_CLASS_TYPE(cls_name).AddInterface(&META_DATA_INTERFACE(intf_name), reinterpret_cast<unsigned int>(static_cast<intf_name*>(reinterpret_cast<cls_name*>(sizeof(int)))) - sizeof(int));

				/*--添加构造函数元数据信息--*/
#define MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(cls_name, index) \
	static bool _MD__CCR##cls_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CLASS_TYPE_CONSTRUCTOR_DEF(cls_name, index) \
	static CMetaDataFunction _MD__CR##cls_name##index(#cls_name, &META_DATA_CLASS_TYPE(cls_name), cls_name::_MD__CCR##cls_name##index); \
	META_DATA_CLASS_TYPE(cls_name).AddConstructor(&_MD__CR##cls_name##index); \
	pMDFunc = &_MD__CR##cls_name##index; \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &META_DATA_CLASS_TYPE(cls_name), 1));

					//添加构造函数参数元数据信息
#define MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));

				/*--添加成员函数元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls_name, func_name, index) \
	static bool _MD__CMF##cls_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls_name, func_name, index) \
	static CMetaDataFunction _MD__MF##cls_name##func_name##index(#func_name, &META_DATA_CLASS_TYPE(cls_name), cls_name::_MD__CMF##cls_name##func_name##index); \
	META_DATA_CLASS_TYPE(cls_name).AddMemberFunc(&_MD__MF##cls_name##func_name##index); \
	pMDFunc = &_MD__MF##cls_name##func_name##index;

					//添加成员函数参数元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//添加成员函数返回值元数据信息
#define MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

				/*--添加成员变量元数据信息--*/
#define MD_CLASS_TYPE_MEMBER_VAR_DEF(cls_name, var_name, var_type, ptr_level) \
	static CMetaDataCustomTypeMemberVar _MD__CT_MV##cls_name##var_name(#var_name, &META_DATA_CLASS_TYPE(cls_name), &(var_type), (ptr_level), reinterpret_cast<unsigned int>(&(reinterpret_cast<cls_name*>(0)->var_name))); \
	META_DATA_CLASS_TYPE(cls_name).AddMemberVar(&_MD__CT_MV##cls_name##var_name);

				/*--添加静态成员函数元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(cls_name, func_name, index) \
	static bool _MD__CSMF##cls_name##func_name##index(SMetaDataCalledFunctionDataPacket &DataPacket);
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(cls_name, func_name, index) \
	static CMetaDataFunction _MD__SMF##cls_name##func_name##index(#func_name, &META_DATA_CLASS_TYPE(cls_name), cls_name::_MD__CSMF##cls_name##func_name##index); \
	META_DATA_CLASS_TYPE(cls_name).AddStaticMemberFunc(&_MD__SMF##cls_name##func_name##index); \
	pMDFunc = &_MD__SMF##cls_name##func_name##index;

					//添加静态成员函数参数元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(name, type, ptr_level) \
	pMDFunc->AddParamInfo(new CMetaDataVarBase(#name, pMDFunc, &(type), (ptr_level)));
					//添加静态成员函数返回值元数据信息
#define MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(type, ptr_level) \
	pMDFunc->SetReturnInfo(new CMetaDataVarBase("__ret_val", pMDFunc, &(type), (ptr_level)));

				/*--添加静态成员变量元数据信息--*/
#define MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(cls_name, var_name, var_type, ptr_level) \
	static CMetaDataVariable _MD__CT_SMV##cls_name##var_name(#var_name, &META_DATA_CLASS_TYPE(cls_name), &(var_type), (ptr_level), &cls_name::var_name); \
	META_DATA_CLASS_TYPE(cls_name).AddStaticMemberVar(&_MD__CT_SMV##cls_name##var_name);

#define MD_CLASS_TYPE_DECLARE_END(name) \
				pMDFunc = NULL; \
			} \
		} _MD__CT_DIDO##name;

#define __MD_INTERFACE_MEMBER_EXTRA	__MD_CLASS_TYPE_MEMBER_EXTRA

#ifdef CO_MD_CLASS_TYPE_EXTRA
#define __MD_CLASS_TYPE_MEMBER_EXTRA \
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
#define __MD_CLASS_TYPE_MEMBER_EXTRA
#endif //CO_MD_CLASS_TYPE_EXTRA

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
