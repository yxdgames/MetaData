#pragma once

#if defined(__METADATA_DLL_EXPORTS__)
#define CLASS_DESCRIPT	__declspec(dllexport)
#elif defined(__METADATA_DLL_IMPORTS__)
#define CLASS_DESCRIPT	__declspec(dllimport)
#else
#define CLASS_DESCRIPT
#endif