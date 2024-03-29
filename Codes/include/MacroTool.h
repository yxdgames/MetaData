#pragma once

#ifdef _MSC_VER //msvc
//msvc在编译预处理中，将__VA_ARGS__作为参数传给另一个宏时，只会将__VA_ARGS__视作另一个宏的一个入参，而不会展开后再作为N个入参。
//所以通外包一层MACRO_TOOL_EXPAND，促使编译预处理器先进行一次展开，以达到变为N个入参的效果。
#define MACRO_TOOL_EXPAND(x)	x
#endif //_MSC_VER

//最大支持69个变参
#define MACRO_TOOL_ARG_MASK(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, \
							arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, \
							arg20, arg21, arg22, arg23, arg24, arg25, arg26, arg27, arg28, arg29, \
							arg30, arg31, arg32, arg33, arg34, arg35, arg36, arg37, arg38, arg39, \
							arg40, arg41, arg42, arg43, arg44, arg45, arg46, arg47, arg48, arg49, \
							arg50, arg51, arg52, arg53, arg54, arg55, arg56, arg57, arg58, arg59, \
							arg60, arg61, arg62, arg63, arg64, arg65, arg66, arg67, arg68, arg69, \
							cranny, ...)	cranny

#ifdef _MSC_VER //msvc
#define MACRO_TOOL_ARG_NUM(...) \
	MACRO_TOOL_EXPAND(MACRO_TOOL_ARG_MASK("Placeholder", ##__VA_ARGS__, \
						69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
						59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
						49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
						39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
						29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
						19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
						9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#else //_MSC_VER
#define MACRO_TOOL_ARG_NUM(...) \
	MACRO_TOOL_ARG_MASK("Placeholder", ##__VA_ARGS__, \
						69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
						59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
						49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
						39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
						29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
						19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
						9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif //_MSC_VER

#define MACRO_TOOL_CAT_(a, b)	a##b
#define MACRO_TOOL_CAT(a, b)	MACRO_TOOL_CAT_(a, b)