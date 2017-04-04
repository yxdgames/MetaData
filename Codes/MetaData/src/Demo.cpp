#include "stdafx.h"
#include "..\include\Demo.h"

#ifdef __META_DATA_DEMO__

//CClass1
CClass1::CClass1(void)
	: mem_i(8329), mem_char(18), mem_short(189), mem_d(951.243), mem_f(832.321f),
	mem_u_i(9998), mem_long(-9532), p_mem_long(NULL)
{
}

CClass1::~CClass1(void)
{
	if (p_mem_long) delete p_mem_long;
}

int CClass1::cls1_func1(int a, double d)
{
	printf("p_a: %d, p_d: %f, this->mem_short: %d, result: %f\n", a, d, this->mem_short, (a * d * this->mem_short));
	return static_cast<int>(a * d * this->mem_short);
}

int CClass1::cls1_func2(unsigned char c, double d)
{
	int ret;
	printf("p_c: %d, p_d: %f, this->mem_char: %d, result: %f\n", c, d, this->mem_char, (c * d / this->mem_char));
	ret = static_cast<int>(c * d * this->mem_char);
	return ret;
}

double CClass1::cls1_vir_func1(float f, unsigned long l)
{
	printf("p_f: %d, p_l: %f, this->mem_d: %d, result: %f\n", f, l, this->mem_d, (f + l - this->mem_d));
	return static_cast<int>(f + l - this->mem_d);
}

void CClass1::cls1_static_func1(void)
{
	printf("cls1_static_func1 doing.\n");
}

float CClass1::cls1_static_func1(int p_x, double p_d)
{
	printf("p_x: %d, p_d: %f, result: %f\n", p_x, p_d, (p_x - p_d));
	return static_cast<float>(p_x - p_d);
}

unsigned char CClass1::static_mem_uc;
unsigned long CClass1::static_mem_ulong;
bool CClass1::static_mem_bool;
bool *CClass1::p_static_mem_bool;

//CClass3::CClass3_Inner1_Derived1
int CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_func1(double x)
{
	printf("p_x: %f, this->mem_s: %d, result: %f\n", x, this->mem_s, x - this->mem_s);
	return static_cast<int>(x - this->mem_s);
}

void CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_func1(int x)
{
	printf("p_x: %d, this->mem_s: %d, result: %f\n", x, this->mem_s, x + this->mem_s);
}

double CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_virtual_func1(double x)
{
	printf("p_x: %f, this->mem_s: %d, result: %f\n", x, this->mem_s, x * this->mem_s);
	return x * this->mem_s;
}

void CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_virtual_func1(int x)
{
	printf("p_x: %d, this->mem_s: %d, result: %f\n", x, this->mem_s, x / this->mem_s);
}

float CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_static_func1(double x)
{
	printf("p_x: %f\n", x);
	return static_cast<float>(x);
}

float CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_static_func1(int x)
{
	printf("p_x: %d\n", x);
	return static_cast<float>(x);
}

bool CClass3::CClass3_Inner1_Derived1::mem_bool;

//NS1_Sub1_Sub1_CClass1
bool NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::func1(float f, int i)
{
	printf("p_f: %f, p_i: %d, this->mem_f: %f, result: %f\n", f, i, this->mem_f, f * i * this->mem_f);
	return (f * i * this->mem_f) != 0;
}

long NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::vfunc1(int i)
{
	printf("p_i: %d, this->mem_f: %f, result: %f\n", i, this->mem_f, i * this->mem_f);
	return (i * this->mem_f) != 0;
}

bool NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::sfunc1(bool b, short sh)
{
	printf("p_b: %d, p_sh: %d\n", b, sh);
	return b;
}

long NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::mem_long;
double NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::mem_double;

#endif //__META_DATA_DEMO__