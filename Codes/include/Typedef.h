#pragma once

typedef unsigned char		TDByte;
#if defined(CO_MACHINE_X64)
typedef unsigned long long	TDUIntPtr;
#elif defined(CO_MACHINE_X86)
typedef unsigned int		TDUIntPtr;
#else
// Unknown
#endif

typedef int					TDEnumType;