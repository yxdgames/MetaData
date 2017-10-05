#pragma once

#include "..\..\include\CommonDefine.h"

enum EVarType
{
	vtNone = 0,
	vtBOOL,
	vtINT,
	vtLONGLONG,
	vtFLOAT,
	vtLONGFLOAT,
	vtCSTR_PTR,
};

struct STRUCT_DESCRIPT SVariant
{
	EVarType type;
	union {
		bool _b;
		int _i;
		long long _ll;
		double _d;
		long double _ld;
		const char *_pcstr;
	} value;
public:
	SVariant(void);
	SVariant(SVariant &src);
	~SVariant(void);
public:
	void SetValue(SVariant &src);
	inline void SetValue(const bool Value);
	inline void SetValue(const int Value);
	inline void SetValue(const long long Value);
	inline void SetValue(const double Value);
	inline void SetValue(const long double Value);
	void SetValue(const char * const pStr);
	inline void SetValueEmpty(void);
public:
	inline SVariant &operator=(SVariant &src);
	inline SVariant &operator=(const bool Value);
	inline SVariant &operator=(const int Value);
	inline SVariant &operator=(const long long Value);
	inline SVariant &operator=(const double Value);
	inline SVariant &operator=(const long double Value);
	inline SVariant &operator=(const char * const pStr);
public:
	void SetReleaseStringFlag(bool flag);
private:
	void FreeStr(void);
private:
	bool release_string;
};

/*--------------------------------*/
/*   Inline Function Definition   */
/*--------------------------------*/
#include <string>

inline void SVariant::SetValue(const bool Value)
{
	FreeStr();
	type = vtBOOL;
	value._b = Value;
}

inline void SVariant::SetValue(const int Value)
{
	FreeStr();
	type = vtINT;
	value._i = Value;
}

inline void SVariant::SetValue(const long long Value)
{
	FreeStr();
	type = vtLONGLONG;
	value._ll = Value;
}

inline void SVariant::SetValue(const double Value)
{
	FreeStr();
	type = vtFLOAT;
	value._d = Value;
}

inline void SVariant::SetValue(const long double Value)
{
	FreeStr();
	type = vtLONGFLOAT;
	value._ld = Value;
}

inline void SVariant::SetValueEmpty(void)
{
	FreeStr();
	type = vtNone;
	memset(&value, 0x00, sizeof(value));
}

inline SVariant &SVariant::operator=(SVariant &src)
{
	SetValue(src);
	return *this;
}

inline SVariant &SVariant::operator=(const bool Value)
{
	SetValue(Value);
	return *this;
}

inline SVariant &SVariant::operator=(const int Value)
{
	SetValue(Value);
	return *this;
}

inline SVariant &SVariant::operator=(const long long Value)
{
	SetValue(Value);
	return *this;
}

inline SVariant &SVariant::operator=(const double Value)
{
	SetValue(Value);
	return *this;
}

inline SVariant &SVariant::operator=(const long double Value)
{
	SetValue(Value);
	return *this;
}

inline SVariant &SVariant::operator=(const char * const pStr)
{
	SetValue(pStr);
	return *this;
}