#pragma once

enum EVarType
{
	vtNone = 0,
	vtBOOL,
	vtINT,
	vtFLOAT,
	vtLONGLONG,
	vtSTR_PTR,
};

struct SVariant
{
	EVarType type;
	union {
		bool _b;
		int _i;
		long double _d;
		long long _ll;
		char *_pstr;
	} value;
public:
	SVariant(void);
	SVariant(SVariant &src);
	~SVariant(void);
public:
	void SetValue(const bool Value);
	void SetValue(const int Value);
	void SetValue(const long double Value);
	void SetValue(const long long Value);
	void SetValue(const char *pStr);
	void SetValueEmpty(void);
public:
	SVariant &operator=(SVariant &src);
	SVariant &operator=(const bool Value);
	SVariant &operator=(const int Value);
	SVariant &operator=(const long double Value);
	SVariant &operator=(const long long Value);
	SVariant &operator=(const char *pStr);
public:
	void SetReleaseStringFlag(bool flag);
private:
	void FreeStr(void);
private:
	bool release_string;
};

