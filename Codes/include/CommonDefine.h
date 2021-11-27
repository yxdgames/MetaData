#pragma once

#if defined(CO_OS_WIN)
#define __DECL_MOD_EXPORT__             __declspec(dllexport)
#define __DECL_MOD_IMPORT__             __declspec(dllimport)
#elif defined(CO_OS_LINUX)
#define __DECL_MOD_EXPORT__             __attribute__((visibility("default")))
#define __DECL_MOD_IMPORT__
#else
// Unknown
#endif

#if defined(CO_METADATA_KERNEL_DLL_EXPORTS)
#define CLASS_DESCRIPT			__DECL_MOD_EXPORT__
#define STRUCT_DESCRIPT			__DECL_MOD_EXPORT__
#define FUNC_DESCRIPT			__DECL_MOD_EXPORT__
#define VAR_DESCRIPT			__DECL_MOD_EXPORT__
#define TEMPLATE_CLASS_DESCRIPT	__DECL_MOD_EXPORT__
#define TEMPLATE_FUNC_DESCRIPT	__DECL_MOD_EXPORT__
#elif defined(CO_METADATA_KERNEL_DLL_IMPORTS)
#define CLASS_DESCRIPT			__DECL_MOD_IMPORT__
#define STRUCT_DESCRIPT			__DECL_MOD_IMPORT__
#define FUNC_DESCRIPT			__DECL_MOD_IMPORT__
#define VAR_DESCRIPT			__DECL_MOD_IMPORT__
#define TEMPLATE_CLASS_DESCRIPT
#define TEMPLATE_FUNC_DESCRIPT
#else
#define CLASS_DESCRIPT
#define STRUCT_DESCRIPT
#define FUNC_DESCRIPT
#define VAR_DESCRIPT
#define TEMPLATE_CLASS_DESCRIPT
#define TEMPLATE_FUNC_DESCRIPT
#endif
