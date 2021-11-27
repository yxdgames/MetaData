#include "stdafx.h"
#include "../../include/Demo/Demo.h"

#ifdef __META_DATA_DEMO__

//CClass1
CClass1::CClass1(void)
	: mem_i(8329), mem_char(18), mem_short(189), mem_d(951.243), mem_f(832.321f),
	mem_u_i(9998), mem_long(-9532), p_mem_long(nullptr),
	//property
	MemI(this, &CClass1::Set_mem_i, &CClass1::Get_mem_i)
{
}

CClass1::~CClass1(void)
{
	if (p_mem_long) delete p_mem_long;
}

int CClass1::cls1_func1(int a, double d)
{
	double ret_d = a * d * this->mem_short;
	int ret = static_cast<int>(ret_d);
	printf("a(%d) * d(%f) * this->mem_short(%d), result: %f -> %d\n", a, d, this->mem_short, ret_d, ret);
	return ret;
}

int CClass1::cls1_func2(unsigned char c, double d)
{
	double ret_d = c * d * this->mem_char;
	int ret = static_cast<int>(ret_d);
	printf("c(%d) * d(%f) * this->mem_char(%d), result: %f -> %d\n", c, d, this->mem_char, ret_d, ret);
	return ret;
}

TDByte CClass1::SetParam(SParam param, float f, long l)
{
	m_Param = param;
	float fr = m_Param.Data[0] + m_Param.Data[1] + m_Param.Data[2] - f + l;
	TDByte ret = (TDByte)fr;
	printf("m_Param.Data[0]:%d, m_Param.Data[1]:%d, m_Param.Data[2]:%d, f:%f, l:%ld, fr:%f, ret = %d\n",
		this->m_Param.Data[0], this->m_Param.Data[1], this->m_Param.Data[2], f, l, fr, ret);
	return ret;
}

double CClass1::cls1_vir_func1(float f, unsigned long l)
{
	double ret = f + l - this->mem_d;
	printf("f(%f) + l(%ld) - this->mem_d(%f), result: %f\n", f, l, this->mem_d, ret);
	return ret;
}

void CClass1::cls1_static_func1(void)
{
	printf("cls1_static_func1 done.\n");
}

float CClass1::cls1_static_func1(int p_x, double p_d)
{
	double ret_d = p_x - p_d;
	float ret = static_cast<float>(ret_d);
	printf("p_x(%d) - p_d(%f), result: %f -> %f\n", p_x, p_d, ret_d, ret);
	return ret;
}

unsigned char CClass1::static_mem_uc;
unsigned long CClass1::static_mem_ulong;
bool CClass1::static_mem_bool;
bool *CClass1::p_static_mem_bool;

//CClass3::CClass3_Inner1_Derived1
int CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_func1(double x)
{
	double ret_d = x - this->mem_s;
	int ret = static_cast<int>(ret_d);
	printf("x(%f) - this->mem_s(%d), result: %f -> %d\n", x, this->mem_s, ret_d, ret);
	return ret;
}

void CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_func1(int x)
{
	printf("x(%d) + this->mem_s(%d), result: %d\n", x, this->mem_s, x + this->mem_s);
}

double CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_virtual_func1(double x)
{
	double ret = x * this->mem_s;
	printf("x(%f) * this->mem_s(%d), result: %f\n", x, this->mem_s, ret);
	return ret;
}

void CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_virtual_func1(int x)
{
	printf("x(%d) / this->mem_s(%d), result: %d\n", x, this->mem_s, x / this->mem_s);
}

float CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_static_func1(double x)
{
	printf("x: %f\n", x);
	return static_cast<float>(x);
}

float CClass3::CClass3_Inner1_Derived1::cls3_i1_d1_static_func1(int x)
{
	printf("x: %d\n", x);
	return static_cast<float>(x);
}

bool CClass3::CClass3_Inner1_Derived1::mem_bool;

//NS1_Sub1_Sub1_CClass1
bool NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::func1(float f, int i)
{
	float val = f * i * this->mem_f;
	printf("f(%f) * i(%d) * this->mem_f(%f), result: %f\n", f, i, this->mem_f, val);
	return val != 0;
}

long NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::vfunc1(int i)
{
	float ret_f = i * this->mem_f;
	printf("i(%d) * this->mem_f(%f), result: %f\n", i, this->mem_f, ret_f);
	return ret_f != 0;
}

bool NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::sfunc1(bool b, short sh)
{
	printf("b: %d, sh: %d\n", b, sh);
	return b;
}

long NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::mem_long;
double NameSpace1::NameSpace1_Sub1::NameSpasce1_Sub1_Sub1::NS1_Sub1_Sub1_CClass1::mem_double;

int global_A;

int global_func(int a)
{
	return -11;
}

#endif //__META_DATA_DEMO__