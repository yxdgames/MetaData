#pragma once

typedef unsigned char		TDByte;
#ifdef CO_PLATFORM_WIN_X64
typedef unsigned long long	TDUIntPtr;
#else
typedef unsigned int		TDUIntPtr;
#endif

typedef int					TDEnumType;