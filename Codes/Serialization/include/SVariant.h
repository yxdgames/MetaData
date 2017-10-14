#pragma once

#include "..\..\MetaData\include\IBlob.h"

enum EVarType
{
	vtNone = 0,
	vtBOOL,
	vtINT,
	vtLONGLONG,
	vtFLOAT,
	vtLONGFLOAT,
	/*以vtPointer为界，以下为指针*/
	vtPointer,
	vtCSTR_PTR,
	vtIntfBlob,
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
		IBlob *_pblob;
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
	void SetValue(const char * const pStr, bool release_flag);
	inline void SetValue(IBlob *pBlob, bool release_flag);
	inline void SetValueEmpty(void);
public:
	inline SVariant &operator=(SVariant &src);
	inline SVariant &operator=(const bool Value);
	inline SVariant &operator=(const int Value);
	inline SVariant &operator=(const long long Value);
	inline SVariant &operator=(const double Value);
	inline SVariant &operator=(const long double Value);
	inline SVariant &operator=(const char * const pStr);
	inline SVariant &operator=(IBlob *pBlob);
private:
	inline void FreeStr(void);
	inline void FreeBlob(void);
	inline void FreeResource(void);
private:
	bool release_flag;
};

/*--------------------------------*/
/*   Inline Function Definition   */
/*--------------------------------*/
#include <string>

inline void SVariant::SetValue(const bool Value)
{
	FreeResource();
	type = vtBOOL;
	value._b = Value;
}

inline void SVariant::SetValue(const int Value)
{
	FreeResource();
	type = vtINT;
	value._i = Value;
}

inline void SVariant::SetValue(const long long Value)
{
	FreeResource();
	type = vtLONGLONG;
	value._ll = Value;
}

inline void SVariant::SetValue(const double Value)
{
	FreeResource();
	type = vtFLOAT;
	value._d = Value;
}

inline void SVariant::SetValue(const long double Value)
{
	FreeResource();
	type = vtLONGFLOAT;
	value._ld = Value;
}

inline void SVariant::SetValue(IBlob *pBlob, bool release_flag)
{
	FreeResource();
	type = vtIntfBlob;
	this->release_flag = release_flag;
	value._pblob = pBlob;
}

inline void SVariant::SetValueEmpty(void)
{
	FreeResource();
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
	SetValue(pStr, true);
	return *this;
}

inline SVariant &SVariant::operator=(IBlob *pBlob)
{
	SetValue(pBlob, false);
	return *this;
}

inline void SVariant::FreeStr(void)
{
	if (type == vtCSTR_PTR && value._pcstr && this->release_flag)
	{
		delete[] value._pcstr;
		value._pcstr = nullptr;
	}
}

inline void SVariant::FreeBlob(void)
{
	if (type == vtIntfBlob && value._pblob && release_flag)
	{
		delete value._pblob;
		value._pblob = nullptr;
	}
}

inline void SVariant::FreeResource(void)
{
	this->FreeStr();
	this->FreeBlob();
}