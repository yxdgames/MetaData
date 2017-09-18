#pragma once

#if defined(CO_METADATA_KERNEL_DLL_EXPORTS)
#define CLASS_DESCRIPT			__declspec(dllexport)
#define STRUCT_DESCRIPT			__declspec(dllexport)
#define FUNC_DESCRIPT			__declspec(dllexport)
#define VAR_DESCRIPT			__declspec(dllexport)
#define TEMPLATE_CLASS_DESCRIPT	__declspec(dllexport)
#define TEMPLATE_FUNC_DESCRIPT	__declspec(dllexport)
#elif defined(CO_METADATA_KERNEL_DLL_IMPORTS)
#define CLASS_DESCRIPT			__declspec(dllimport)
#define STRUCT_DESCRIPT			__declspec(dllimport)
#define FUNC_DESCRIPT			__declspec(dllimport)
#define VAR_DESCRIPT			__declspec(dllimport)
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
