#pragma once

#include "Property.h"
#include "SimpleString.h"
#include "MetaDataSupport.h"

//#define	__META_DATA_DEMO__

#ifdef __META_DATA_DEMO__
////////////////////////////////////////////////
//                  Demo                      //
////////////////////////////////////////////////

class CLASS_DESCRIPT CClass1
{
public:
	CClass1(void);
	~CClass1(void);
public:
	int cls1_func1(int a, double d);
	int cls1_func2(unsigned char c, double d);
public:
	virtual double cls1_vir_func1(float f, unsigned long l);
public:
	static void cls1_static_func1(void);
	static float cls1_static_func1(int p_x, double p_d);
public:
	int mem_i;
	char mem_char;
	short mem_short;
	double mem_d;
	float mem_f;
	unsigned int mem_u_i;
	long mem_long;
	long *p_mem_long;
	const char *pString;
public:
	void Set_mem_i(int value) { mem_i = value; printf("Set_mem_i\n"); }
	int Get_mem_i(void) { printf("Get_mem_i\n"); return mem_i; }
	void Set_mem_char(char value) { mem_char = value; printf("Set_mem_char\n"); }
	char Get_mem_char(void) { printf("Get_mem_char\n"); return mem_char; }
	void Set_mem_string(const char *value) { pString = value; }
	const char *Get_mem_string(void) { return pString; }
	//propert
	Property<CClass1, int>			MemI;
	Property<CClass1, const char*>	MemString;
public:
	static unsigned char static_mem_uc;
	static unsigned long static_mem_ulong;
	static bool static_mem_bool;
	static bool *p_static_mem_bool;
MD_CLASS_TYPE_DECLARE_BEGIN(CClass1)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(0)
	MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
	MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls1_func1, 0)
	MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls1_func2, 0)
	MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls1_vir_func1, 0)
	MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(cls1_static_func1, 0)
	MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(cls1_static_func1, 1)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1)
	MD_CLASS_TYPE_CONSTRUCTOR_DEF(0)
	MD_CLASS_TYPE_DESTRUCTOR_DEF()
	MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls1_func1, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(a, int, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(d, double, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(int, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls1_func2, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(c, unsigned char, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(d, double, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(int, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls1_vir_func1, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(f, float, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(l, unsigned long, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(double, MD_NO_ASTERISK)
	MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(cls1_static_func1, 0)
	MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(cls1_static_func1, 1)
		MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(p_x, int, MD_NO_ASTERISK)
		MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(p_d, double, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(float, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_i, int, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_char, char, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_short, short, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_d, double, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_f, float, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_u_i, unsigned int, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_long, long, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(p_mem_long, long, *)
	MD_CLASS_TYPE_MEMBER_PROPERTY_DEF(MemI, int, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_PROPERTY_DEF(MemString, char, *)
	MD_CLASS_TYPE_PROPERTY_DEF(mem_char, CClass1, char, MD_NO_ASTERISK, Set_mem_char, Get_mem_char)
	MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(static_mem_uc, unsigned char, MD_NO_ASTERISK)
	MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(static_mem_ulong, unsigned long, MD_NO_ASTERISK)
	MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(static_mem_bool, bool, MD_NO_ASTERISK)
	MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(p_static_mem_bool, bool, *)
MD_CLASS_TYPE_DECLARE_END(CClass1)
};

class CClass1_Derived1 : public CClass1
{
public:
	CClass1_Derived1(void);
	~CClass1_Derived1(void);
public:
	int *cls1_der1_func1(unsigned char c, double d) { return nullptr; }
	int ***cls1_der1_func2(unsigned char c, double d) { return nullptr; };

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Derived1)
	MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls1_der1_func1, 0)
	MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls1_der1_func2, 0)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1)
	MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls1_der1_func1, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(c, unsigned char, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(d, double, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(int, *)
	MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls1_der1_func2, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(c, unsigned char, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(d, double, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(int, ***)
MD_CLASS_TYPE_DECLARE_END(CClass1_Derived1)
};

class CClass1_Derived2 : public CClass1
{
public:
	CClass1_Derived2(void);
	~CClass1_Derived2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Derived2)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Derived2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1)
MD_CLASS_TYPE_DECLARE_END(CClass1_Derived2)
};


class CClass1_Descendant1 : public CClass1_Derived1
{
public:
	CClass1_Descendant1(void);
	~CClass1_Descendant1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant1)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Descendant1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived1)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant1)
};

class CClass1_Descendant2 : public CClass1_Derived2
{
public:
	CClass1_Descendant2(void);
	~CClass1_Descendant2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant2)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Descendant2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant2)
};

class CClass1_Descendant3 : public CClass1_Derived1, public CClass1_Derived2
{
public:
	CClass1_Descendant3(void);
	~CClass1_Descendant3(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant3)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Descendant3)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant3)
};

class CClass1_Descendant4 : public CClass1_Descendant2
{
public:
	CClass1_Descendant4(void);
	~CClass1_Descendant4(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant4)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Descendant4)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Descendant2)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant4)
};

class CClass1_Descendant5 : public CClass1_Descendant3
{
public:
	CClass1_Descendant5(void);
	~CClass1_Descendant5(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass1_Descendant5)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass1_Descendant5)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass1_Descendant3)
MD_CLASS_TYPE_DECLARE_END(CClass1_Descendant5)
};

class CClass2
{
public:
	CClass2(void) {}
	virtual ~CClass2(void) {}
public:
	int mem_a;
	long mem_b;

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_a, int, MD_NO_ASTERISK)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_b, long, MD_NO_ASTERISK)
MD_CLASS_TYPE_DECLARE_END(CClass2)
};

class CClass2_Derived1 : public CClass2
{
public:
	CClass2_Derived1(void);
	virtual ~CClass2_Derived1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Derived1)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Derived1)
};

class CClass2_Derived2 : public CClass2
{
public:
	CClass2_Derived2(void);
	virtual ~CClass2_Derived2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Derived2)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Derived2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Derived2)
};

class CClass2_Descendant1 : public CClass2_Derived1
{
public:
	CClass2_Descendant1(void);
	virtual ~CClass2_Descendant1(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant1)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Descendant1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived1)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant1)
};

class CClass2_Descendant2 : public CClass2_Derived2
{
public:
	CClass2_Descendant2(void);
	virtual ~CClass2_Descendant2(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant2)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Descendant2)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant2)
};

class CClass2_Descendant3 : public CClass2_Derived1, public CClass2_Derived2
{
public:
	CClass2_Descendant3(void);
	virtual ~CClass2_Descendant3(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant3)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Descendant3)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived1)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Derived2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant3)
};

class CClass2_Descendant4 : public CClass2_Descendant2
{
public:
	CClass2_Descendant4(void);
	virtual ~CClass2_Descendant4(void);

MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant4)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Descendant4)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Descendant2)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant4)
};

class CClass2_Descendant5 : public CClass2_Descendant3
{
public:
	CClass2_Descendant5(void);
	virtual ~CClass2_Descendant5(void);
MD_CLASS_TYPE_DECLARE_BEGIN(CClass2_Descendant5)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass2_Descendant5)
	MD_CLASS_TYPE_BASE_CLASS_DEF(CClass2_Descendant3)
MD_CLASS_TYPE_DECLARE_END(CClass2_Descendant5)
};

class CClass3
{
public:
	CClass3(void);
	~CClass3(void);
public:
	class CClass3_Inner1
	{
	public:
		CClass3_Inner1(void) {}
		~CClass3_Inner1(void) {}
	public:
		SimpleString mem_string;
		char mem_char;
		float mem_float;
		bool mem_bool;
		CClass2 mem_cls2;

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1)
		MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1)
		MD_CLASS_TYPE_DESTRUCTOR_DEF()
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_string, SimpleString, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_char, char, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_float, float, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_bool, bool, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_cls2, CClass2, MD_NO_ASTERISK)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1)
	};
	class CClass3_Inner2
	{
	public:
		CClass3_Inner2(void);
		virtual ~CClass3_Inner2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner2)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner2)
	};
	class CClass3_Inner3
	{
	public:
		CClass3_Inner3(void);
		~CClass3_Inner3(void);
	public:
		class CClass3_Inner3_Inner1
		{
		public:
			CClass3_Inner3_Inner1(void);
			~CClass3_Inner3_Inner1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner3_Inner1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner3_Inner1)
		MD_CLASS_TYPE_DECLARE_END(CClass3_Inner3_Inner1)
		};
		class CClass3_Inner3_Inner2
		{
		public:
			CClass3_Inner3_Inner2(void);
			~CClass3_Inner3_Inner2(void);
		public:
			class CClass3_Inner3_Inner2_Inner1
			{
			public:
				CClass3_Inner3_Inner2_Inner1(void);
				~CClass3_Inner3_Inner2_Inner1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner3_Inner2_Inner1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner3_Inner2_Inner1)
			MD_CLASS_TYPE_DECLARE_END(CClass3_Inner3_Inner2_Inner1)
			};

		MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner3_Inner2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner3_Inner2)
		MD_CLASS_TYPE_DECLARE_END(CClass3_Inner3_Inner2)
		};

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner3)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner3)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner3)
	};
	class CClass3_Inner1_Derived1 : public CClass3_Inner1
	{
	public:
		CClass3_Inner1_Derived1(void) {}
		CClass3_Inner1_Derived1(int a)
		{
			mem_cls1.mem_i = 0;
		}
		~CClass3_Inner1_Derived1(void) {}
	public:
		int cls3_i1_d1_func1(double x);
		void cls3_i1_d1_func1(int x);
	public:
		virtual double cls3_i1_d1_virtual_func1(double x);
		virtual void cls3_i1_d1_virtual_func1(int x);
	public:
		static float cls3_i1_d1_static_func1(double x);
		static float cls3_i1_d1_static_func1(int x);
	public:
		CClass1 mem_cls1;
		short mem_s;
	public:
		static bool mem_bool;

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Derived1)
		MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(0)
		MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(1)
		MD_CLASS_TYPE_DESTRUCTOR_WRAPPER_DECLARE()
		MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls3_i1_d1_func1, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls3_i1_d1_func1, 1)
		MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls3_i1_d1_virtual_func1, 0)
		MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(cls3_i1_d1_virtual_func1, 1)
		MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(cls3_i1_d1_static_func1, 0)
		MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(cls3_i1_d1_static_func1, 1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Derived1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1)
		MD_CLASS_TYPE_CONSTRUCTOR_DEF(0)
		MD_CLASS_TYPE_CONSTRUCTOR_DEF(1)
			MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(a, int, MD_NO_ASTERISK)
		MD_CLASS_TYPE_DESTRUCTOR_DEF()
		MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls3_i1_d1_func1, 0)
			MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(x, double, MD_NO_ASTERISK)
			MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(int, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls3_i1_d1_func1, 1)
			MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(x, int, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls3_i1_d1_virtual_func1, 0)
			MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(x, double, MD_NO_ASTERISK)
			MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(double, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_FUNC_DEF(cls3_i1_d1_virtual_func1, 1)
			MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(x, int, MD_NO_ASTERISK)
		MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(cls3_i1_d1_static_func1, 0)
			MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(x, double, MD_NO_ASTERISK)
			MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(float, MD_NO_ASTERISK)
		MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(cls3_i1_d1_static_func1, 1)
			MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(x, int, MD_NO_ASTERISK)
			MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(float, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_cls1, CClass1, MD_NO_ASTERISK)
		MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_s, short, MD_NO_ASTERISK)
		MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(mem_bool, bool, MD_NO_ASTERISK)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Derived1)
	};
	class CClass3_Inner1_Derived2 : public CClass3_Inner1
	{
	public:
		CClass3_Inner1_Derived2(void);
		~CClass3_Inner1_Derived2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Derived2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Derived2)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Derived2)
	};
	class CClass3_Inner1_Descendant1 : public CClass3_Inner1_Derived1
	{
	public:
		CClass3_Inner1_Descendant1(void);
		~CClass3_Inner1_Descendant1(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Descendant1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Descendant1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1_Derived1)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Descendant1)
	};
	class CClass3_Inner1_Descendant2 : public CClass3_Inner1_Derived2
	{
	public:
		CClass3_Inner1_Descendant2(void);
		~CClass3_Inner1_Descendant2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Descendant2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Descendant2)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1_Derived2)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Descendant2)
	};
	class CClass3_Inner1_Descendant3 : public CClass3_Inner1_Derived1, public CClass3_Inner1_Derived2
	{
	public:
		CClass3_Inner1_Descendant3(void);
		~CClass3_Inner1_Descendant3(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Descendant3)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Descendant3)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1_Derived1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1_Derived2)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Descendant3)
	};
	class CClass3_Inner1_Descendant4 : public CClass3_Inner1_Descendant2
	{
	public:
		CClass3_Inner1_Descendant4(void);
		~CClass3_Inner1_Descendant4(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Descendant4)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Descendant4)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1_Descendant2)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Descendant4)
	};
	class CClass3_Inner1_Descendant5 : public CClass3_Inner1_Descendant3
	{
	public:
		CClass3_Inner1_Descendant5(void);
		~CClass3_Inner1_Descendant5(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(CClass3_Inner1_Descendant5)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3_Inner1_Descendant5)
		MD_CLASS_TYPE_BASE_CLASS_DEF(CClass3_Inner1_Descendant3)
	MD_CLASS_TYPE_DECLARE_END(CClass3_Inner1_Descendant5)
	};

MD_CLASS_TYPE_DECLARE_BEGIN(CClass3)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CClass3)
MD_CLASS_TYPE_DECLARE_END(CClass3)
};

namespace NameSpace1{
	//Declare NameSpace1
	MD_NAME_SPACE_DECLARE(NameSpace1)

	class NS1_CClass1
	{
	public:
		NS1_CClass1(void);
		~NS1_CClass1(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1)
	};

	class NS1_CClass1_Derived1 : public NS1_CClass1
	{
	public:
		NS1_CClass1_Derived1(void);
		~NS1_CClass1_Derived1(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Derived1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Derived1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Derived1)
	};

	class NS1_CClass1_Derived2 : public NS1_CClass1
	{
	public:
		NS1_CClass1_Derived2(void);
		~NS1_CClass1_Derived2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Derived2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Derived2)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Derived2)
	};


	class NS1_CClass1_Descendant1 : public NS1_CClass1_Derived1
	{
	public:
		NS1_CClass1_Descendant1(void);
		~NS1_CClass1_Descendant1(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Descendant1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Descendant1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1_Derived1)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Descendant1)
	};

	class NS1_CClass1_Descendant2 : public NS1_CClass1_Derived2
	{
	public:
		NS1_CClass1_Descendant2(void);
		~NS1_CClass1_Descendant2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Descendant2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Descendant2)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1_Derived2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Descendant2)
	};

	class NS1_CClass1_Descendant3 : public NS1_CClass1_Derived1, public NS1_CClass1_Derived2
	{
	public:
		NS1_CClass1_Descendant3(void);
		~NS1_CClass1_Descendant3(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Descendant3)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Descendant3)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1_Derived1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1_Derived2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Descendant3)
	};

	class NS1_CClass1_Descendant4 : public NS1_CClass1_Descendant2
	{
	public:
		NS1_CClass1_Descendant4(void);
		~NS1_CClass1_Descendant4(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Descendant4)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Descendant4)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1_Descendant2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Descendant4)
	};

	class NS1_CClass1_Descendant5 : public NS1_CClass1_Descendant3
	{
	public:
		NS1_CClass1_Descendant5(void);
		~NS1_CClass1_Descendant5(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass1_Descendant5)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass1_Descendant5)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass1_Descendant3)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass1_Descendant5)
	};

	class NS1_CClass2
	{
	public:
		NS1_CClass2(void);
		virtual ~NS1_CClass2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2)
	};

	class NS1_CClass2_Derived1 : public NS1_CClass2
	{
	public:
		NS1_CClass2_Derived1(void);
		virtual ~NS1_CClass2_Derived1(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Derived1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Derived1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Derived1)
	};

	class NS1_CClass2_Derived2 : public NS1_CClass2
	{
	public:
		NS1_CClass2_Derived2(void);
		virtual ~NS1_CClass2_Derived2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Derived2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Derived2)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Derived2)
	};

	class NS1_CClass2_Descendant1 : public NS1_CClass2_Derived1
	{
	public:
		NS1_CClass2_Descendant1(void);
		virtual ~NS1_CClass2_Descendant1(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Descendant1)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Descendant1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2_Derived1)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Descendant1)
	};

	class NS1_CClass2_Descendant2 : public NS1_CClass2_Derived2
	{
	public:
		NS1_CClass2_Descendant2(void);
		virtual ~NS1_CClass2_Descendant2(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Descendant2)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Descendant2)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2_Derived2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Descendant2)
	};

	class NS1_CClass2_Descendant3 : public NS1_CClass2_Derived1, public NS1_CClass2_Derived2
	{
	public:
		NS1_CClass2_Descendant3(void);
		virtual ~NS1_CClass2_Descendant3(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Descendant3)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Descendant3)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2_Derived1)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2_Derived2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Descendant3)
	};

	class NS1_CClass2_Descendant4 : public NS1_CClass2_Descendant2
	{
	public:
		NS1_CClass2_Descendant4(void);
		virtual ~NS1_CClass2_Descendant4(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Descendant4)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Descendant4)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2_Descendant2)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Descendant4)
	};

	class NS1_CClass2_Descendant5 : public NS1_CClass2_Descendant3
	{
	public:
		NS1_CClass2_Descendant5(void);
		virtual ~NS1_CClass2_Descendant5(void);

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass2_Descendant5)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass2_Descendant5)
		MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass2_Descendant3)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass2_Descendant5)
	};

	class NS1_CClass3
	{
	public:
		NS1_CClass3(void);
		~NS1_CClass3(void);
	public:
		class NS1_CClass3_Inner1
		{
		public:
			NS1_CClass3_Inner1(void);
			~NS1_CClass3_Inner1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1)
		};
		class NS1_CClass3_Inner2
		{
		public:
			NS1_CClass3_Inner2(void);
			virtual ~NS1_CClass3_Inner2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner2)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner2)
		};
		class NS1_CClass3_Inner3
		{
		public:
			NS1_CClass3_Inner3(void);
			~NS1_CClass3_Inner3(void);
		public:
			class NS1_CClass3_Inner3_Inner1
			{
			public:
				NS1_CClass3_Inner3_Inner1(void);
				~NS1_CClass3_Inner3_Inner1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner3_Inner1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner3_Inner1)
			MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner3_Inner1)
			};
			class NS1_CClass3_Inner3_Inner2
			{
			public:
				NS1_CClass3_Inner3_Inner2(void);
				~NS1_CClass3_Inner3_Inner2(void);
			public:
				class NS1_CClass3_Inner3_Inner2_Inner1
				{
				public:
					NS1_CClass3_Inner3_Inner2_Inner1(void);
					~NS1_CClass3_Inner3_Inner2_Inner1(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner3_Inner2_Inner1)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner3_Inner2_Inner1)
				MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner3_Inner2_Inner1)
				};

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner3_Inner2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner3_Inner2)
			MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner3_Inner2)
			};
		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner3)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner3)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner3)
		};
		class NS1_CClass3_Inner1_Derived1 : public NS1_CClass3_Inner1
		{
		public:
			NS1_CClass3_Inner1_Derived1(void);
			~NS1_CClass3_Inner1_Derived1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Derived1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Derived1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Derived1)
		};
		class NS1_CClass3_Inner1_Derived2 : public NS1_CClass3_Inner1
		{
		public:
			NS1_CClass3_Inner1_Derived2(void);
			~NS1_CClass3_Inner1_Derived2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Derived2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Derived2)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Derived2)
		};
		class NS1_CClass3_Inner1_Descendant1 : public NS1_CClass3_Inner1_Derived1
		{
		public:
			NS1_CClass3_Inner1_Descendant1(void);
			~NS1_CClass3_Inner1_Descendant1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Descendant1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Descendant1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1_Derived1)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Descendant1)
		};
		class NS1_CClass3_Inner1_Descendant2 : public NS1_CClass3_Inner1_Derived2
		{
		public:
			NS1_CClass3_Inner1_Descendant2(void);
			~NS1_CClass3_Inner1_Descendant2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Descendant2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Descendant2)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1_Derived2)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Descendant2)
		};
		class NS1_CClass3_Inner1_Descendant3 : public NS1_CClass3_Inner1_Derived1, public NS1_CClass3_Inner1_Derived2
		{
		public:
			NS1_CClass3_Inner1_Descendant3(void);
			~NS1_CClass3_Inner1_Descendant3(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Descendant3)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Descendant3)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1_Derived1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1_Derived2)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Descendant3)
		};
		class NS1_CClass3_Inner1_Descendant4 : public NS1_CClass3_Inner1_Descendant2
		{
		public:
			NS1_CClass3_Inner1_Descendant4(void);
			~NS1_CClass3_Inner1_Descendant4(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Descendant4)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Descendant4)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1_Descendant2)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Descendant4)
		};
		class NS1_CClass3_Inner1_Descendant5 : public NS1_CClass3_Inner1_Descendant3
		{
		public:
			NS1_CClass3_Inner1_Descendant5(void);
			~NS1_CClass3_Inner1_Descendant5(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3_Inner1_Descendant5)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3_Inner1_Descendant5)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_CClass3_Inner1_Descendant3)
		MD_CLASS_TYPE_DECLARE_END(NS1_CClass3_Inner1_Descendant5)
		};

	MD_CLASS_TYPE_DECLARE_BEGIN(NS1_CClass3)
	MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_CClass3)
	MD_CLASS_TYPE_DECLARE_END(NS1_CClass3)
	};
	namespace NameSpace1_Sub1
	{
		//Declare NameSpace1_Sub1
		MD_NAME_SPACE_DECLARE(NameSpace1_Sub1)

		class NS1_Sub1_CClass1
		{
		public:
			NS1_Sub1_CClass1(void);
			~NS1_Sub1_CClass1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1)
		};

		class NS1_Sub1_CClass1_Derived1 : public NS1_Sub1_CClass1
		{
		public:
			NS1_Sub1_CClass1_Derived1(void);
			~NS1_Sub1_CClass1_Derived1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Derived1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Derived1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Derived1)
		};

		class NS1_Sub1_CClass1_Derived2 : public NS1_Sub1_CClass1
		{
		public:
			NS1_Sub1_CClass1_Derived2(void);
			~NS1_Sub1_CClass1_Derived2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Derived2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Derived2)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Derived2)
		};


		class NS1_Sub1_CClass1_Descendant1 : public NS1_Sub1_CClass1_Derived1
		{
		public:
			NS1_Sub1_CClass1_Descendant1(void);
			~NS1_Sub1_CClass1_Descendant1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Descendant1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Descendant1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1_Derived1)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Descendant1)
		};

		class NS1_Sub1_CClass1_Descendant2 : public NS1_Sub1_CClass1_Derived2
		{
		public:
			NS1_Sub1_CClass1_Descendant2(void);
			~NS1_Sub1_CClass1_Descendant2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Descendant2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Descendant2)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1_Derived2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Descendant2)
		};

		class NS1_Sub1_CClass1_Descendant3 : public NS1_Sub1_CClass1_Derived1, public NS1_Sub1_CClass1_Derived2
		{
		public:
			NS1_Sub1_CClass1_Descendant3(void);
			~NS1_Sub1_CClass1_Descendant3(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Descendant3)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Descendant3)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1_Derived1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1_Derived2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Descendant3)
		};

		class NS1_Sub1_CClass1_Descendant4 : public NS1_Sub1_CClass1_Descendant2
		{
		public:
			NS1_Sub1_CClass1_Descendant4(void);
			~NS1_Sub1_CClass1_Descendant4(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Descendant4)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Descendant4)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1_Descendant2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Descendant4)
		};

		class NS1_Sub1_CClass1_Descendant5 : public NS1_Sub1_CClass1_Descendant3
		{
		public:
			NS1_Sub1_CClass1_Descendant5(void);
			~NS1_Sub1_CClass1_Descendant5(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass1_Descendant5)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass1_Descendant5)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass1_Descendant3)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass1_Descendant5)
		};

		class NS1_Sub1_CClass2
		{
		public:
			NS1_Sub1_CClass2(void);
			virtual ~NS1_Sub1_CClass2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2)
		};

		class NS1_Sub1_CClass2_Derived1 : public NS1_Sub1_CClass2
		{
		public:
			NS1_Sub1_CClass2_Derived1(void);
			virtual ~NS1_Sub1_CClass2_Derived1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Derived1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Derived1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Derived1)
		};

		class NS1_Sub1_CClass2_Derived2 : public NS1_Sub1_CClass2
		{
		public:
			NS1_Sub1_CClass2_Derived2(void);
			virtual ~NS1_Sub1_CClass2_Derived2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Derived2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Derived2)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Derived2)
		};

		class NS1_Sub1_CClass2_Descendant1 : public NS1_Sub1_CClass2_Derived1
		{
		public:
			NS1_Sub1_CClass2_Descendant1(void);
			virtual ~NS1_Sub1_CClass2_Descendant1(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Descendant1)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Descendant1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2_Derived1)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Descendant1)
		};

		class NS1_Sub1_CClass2_Descendant2 : public NS1_Sub1_CClass2_Derived2
		{
		public:
			NS1_Sub1_CClass2_Descendant2(void);
			virtual ~NS1_Sub1_CClass2_Descendant2(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Descendant2)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Descendant2)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2_Derived2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Descendant2)
		};

		class NS1_Sub1_CClass2_Descendant3 : public NS1_Sub1_CClass2_Derived1, public NS1_Sub1_CClass2_Derived2
		{
		public:
			NS1_Sub1_CClass2_Descendant3(void);
			virtual ~NS1_Sub1_CClass2_Descendant3(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Descendant3)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Descendant3)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2_Derived1)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2_Derived2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Descendant3)
		};

		class NS1_Sub1_CClass2_Descendant4 : public NS1_Sub1_CClass2_Descendant2
		{
		public:
			NS1_Sub1_CClass2_Descendant4(void);
			virtual ~NS1_Sub1_CClass2_Descendant4(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Descendant4)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Descendant4)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2_Descendant2)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Descendant4)
		};

		class NS1_Sub1_CClass2_Descendant5 : public NS1_Sub1_CClass2_Descendant3
		{
		public:
			NS1_Sub1_CClass2_Descendant5(void);
			virtual ~NS1_Sub1_CClass2_Descendant5(void);

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass2_Descendant5)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass2_Descendant5)
			MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass2_Descendant3)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass2_Descendant5)
		};

		class NS1_Sub1_CClass3
		{
		public:
			NS1_Sub1_CClass3(void);
			~NS1_Sub1_CClass3(void);
		public:
			class NS1_Sub1_CClass3_Inner1
			{
			public:
				NS1_Sub1_CClass3_Inner1(void);
				~NS1_Sub1_CClass3_Inner1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1)
			};
			class NS1_Sub1_CClass3_Inner2
			{
			public:
				NS1_Sub1_CClass3_Inner2(void);
				virtual ~NS1_Sub1_CClass3_Inner2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner2)
			};
			class NS1_Sub1_CClass3_Inner3
			{
			public:
				NS1_Sub1_CClass3_Inner3(void);
				~NS1_Sub1_CClass3_Inner3(void);
			public:
				class NS1_Sub1_CClass3_Inner3_Inner1
				{
				public:
					NS1_Sub1_CClass3_Inner3_Inner1(void);
					~NS1_Sub1_CClass3_Inner3_Inner1(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner3_Inner1)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner3_Inner1)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner3_Inner1)
				};

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner3)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner3)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner3)
			};
			class NS1_Sub1_CClass3_Inner1_Derived1 : public NS1_Sub1_CClass3_Inner1
			{
			public:
				NS1_Sub1_CClass3_Inner1_Derived1(void);
				~NS1_Sub1_CClass3_Inner1_Derived1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Derived1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Derived1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Derived1)
			};
			class NS1_Sub1_CClass3_Inner1_Derived2 : public NS1_Sub1_CClass3_Inner1
			{
			public:
				NS1_Sub1_CClass3_Inner1_Derived2(void);
				~NS1_Sub1_CClass3_Inner1_Derived2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Derived2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Derived2)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Derived2)
			};
			class NS1_Sub1_CClass3_Inner1_Descendant1 : public NS1_Sub1_CClass3_Inner1_Derived1
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant1(void);
				~NS1_Sub1_CClass3_Inner1_Descendant1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Descendant1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Descendant1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1_Derived1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Descendant1)
			};
			class NS1_Sub1_CClass3_Inner1_Descendant2 : public NS1_Sub1_CClass3_Inner1_Derived2
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant2(void);
				~NS1_Sub1_CClass3_Inner1_Descendant2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Descendant2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Descendant2)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1_Derived2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Descendant2)
			};
			class NS1_Sub1_CClass3_Inner1_Descendant3 : public NS1_Sub1_CClass3_Inner1_Derived1, public NS1_Sub1_CClass3_Inner1_Derived2
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant3(void);
				~NS1_Sub1_CClass3_Inner1_Descendant3(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Descendant3)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Descendant3)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1_Derived1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1_Derived2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Descendant3)
			};
			class NS1_Sub1_CClass3_Inner1_Descendant4 : public NS1_Sub1_CClass3_Inner1_Descendant2
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant4(void);
				~NS1_Sub1_CClass3_Inner1_Descendant4(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Descendant4)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Descendant4)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1_Descendant2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Descendant4)
			};
			class NS1_Sub1_CClass3_Inner1_Descendant5 : public NS1_Sub1_CClass3_Inner1_Descendant3
			{
			public:
				NS1_Sub1_CClass3_Inner1_Descendant5(void);
				~NS1_Sub1_CClass3_Inner1_Descendant5(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3_Inner1_Descendant5)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3_Inner1_Descendant5)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_CClass3_Inner1_Descendant3)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3_Inner1_Descendant5)
			};

		MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_CClass3)
		MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_CClass3)
		MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_CClass3)
		};

		namespace NameSpasce1_Sub1_Sub1
		{
			//Declare NameSpasce1_Sub1_Sub1
			MD_NAME_SPACE_DECLARE(NameSpasce1_Sub1_Sub1)

			class NS1_Sub1_Sub1_CClass1
			{
			public:
				NS1_Sub1_Sub1_CClass1(void) {}
				NS1_Sub1_Sub1_CClass1(int i, float f) : mem_i(i), mem_f(f) {}
				~NS1_Sub1_Sub1_CClass1(void) {}
			public:
				bool func1(float f, int i);
			public:
				virtual long vfunc1(int i);
			public:
				static bool sfunc1(bool b, short sh);
			public:
				int mem_i;
				float mem_f;
			public:
				static long mem_long;
				static double mem_double;

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1)
				MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(0)
				MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(1)
				MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(func1, 0)
				MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(vfunc1, 0)
				MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(sfunc1, 0)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1)
				MD_CLASS_TYPE_CONSTRUCTOR_DEF(0)
				MD_CLASS_TYPE_CONSTRUCTOR_DEF(1)
					MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(i, int, MD_NO_ASTERISK)
					MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(f, float, MD_NO_ASTERISK)
				MD_CLASS_TYPE_MEMBER_FUNC_DEF(func1, 0)
					MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(f, float, MD_NO_ASTERISK)
					MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(i, int, MD_NO_ASTERISK)
					MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(bool, MD_NO_ASTERISK)
				MD_CLASS_TYPE_MEMBER_FUNC_DEF(vfunc1, 0)
					MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(i, int, MD_NO_ASTERISK)
					MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(long, MD_NO_ASTERISK)
				MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(sfunc1, 0)
					MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(b, bool, MD_NO_ASTERISK)
					MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(sh, short, MD_NO_ASTERISK)
					MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(bool, MD_NO_ASTERISK)
				MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_i, int, MD_NO_ASTERISK)
				MD_CLASS_TYPE_MEMBER_VAR_DEF(mem_f, float, MD_NO_ASTERISK)
				MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(mem_long, long, MD_NO_ASTERISK)
				MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(mem_double, double, MD_NO_ASTERISK)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1)
			};

			class NS1_Sub1_Sub1_CClass1_Derived1 : public NS1_Sub1_Sub1_CClass1
			{
			public:
				NS1_Sub1_Sub1_CClass1_Derived1(void);
				~NS1_Sub1_Sub1_CClass1_Derived1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Derived1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Derived1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Derived1)
			};

			class NS1_Sub1_Sub1_CClass1_Derived2 : public NS1_Sub1_Sub1_CClass1
			{
			public:
				NS1_Sub1_Sub1_CClass1_Derived2(void);
				~NS1_Sub1_Sub1_CClass1_Derived2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Derived2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Derived2)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Derived2)
			};


			class NS1_Sub1_Sub1_CClass1_Descendant1 : public NS1_Sub1_Sub1_CClass1_Derived1
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant1(void);
				~NS1_Sub1_Sub1_CClass1_Descendant1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Descendant1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Descendant1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1_Derived1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Descendant1)
			};

			class NS1_Sub1_Sub1_CClass1_Descendant2 : public NS1_Sub1_Sub1_CClass1_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant2(void);
				~NS1_Sub1_Sub1_CClass1_Descendant2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Descendant2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Descendant2)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1_Derived2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Descendant2)
			};

			class NS1_Sub1_Sub1_CClass1_Descendant3 : public NS1_Sub1_Sub1_CClass1_Derived1, public NS1_Sub1_Sub1_CClass1_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant3(void);
				~NS1_Sub1_Sub1_CClass1_Descendant3(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Descendant3)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Descendant3)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1_Derived1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1_Derived2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Descendant3)
			};

			class NS1_Sub1_Sub1_CClass1_Descendant4 : public NS1_Sub1_Sub1_CClass1_Descendant2
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant4(void);
				~NS1_Sub1_Sub1_CClass1_Descendant4(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Descendant4)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Descendant4)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1_Descendant2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Descendant4)
			};

			class NS1_Sub1_Sub1_CClass1_Descendant5 : public NS1_Sub1_Sub1_CClass1_Descendant3
			{
			public:
				NS1_Sub1_Sub1_CClass1_Descendant5(void);
				~NS1_Sub1_Sub1_CClass1_Descendant5(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass1_Descendant5)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass1_Descendant5)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass1_Descendant3)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass1_Descendant5)
			};

			class NS1_Sub1_Sub1_CClass2
			{
			public:
				NS1_Sub1_Sub1_CClass2(void);
				virtual ~NS1_Sub1_Sub1_CClass2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2)
			};

			class NS1_Sub1_Sub1_CClass2_Derived1 : public NS1_Sub1_Sub1_CClass2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Derived1(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Derived1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Derived1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Derived1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Derived1)
			};

			class NS1_Sub1_Sub1_CClass2_Derived2 : public NS1_Sub1_Sub1_CClass2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Derived2(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Derived2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Derived2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Derived2)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Derived2)
			};

			class NS1_Sub1_Sub1_CClass2_Descendant1 : public NS1_Sub1_Sub1_CClass2_Derived1
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant1(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant1(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Descendant1)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Descendant1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2_Derived1)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Descendant1)
			};

			class NS1_Sub1_Sub1_CClass2_Descendant2 : public NS1_Sub1_Sub1_CClass2_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant2(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant2(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Descendant2)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Descendant2)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2_Derived2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Descendant2)
			};

			class NS1_Sub1_Sub1_CClass2_Descendant3 : public NS1_Sub1_Sub1_CClass2_Derived1, public NS1_Sub1_Sub1_CClass2_Derived2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant3(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant3(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Descendant3)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Descendant3)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2_Derived1)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2_Derived2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Descendant3)
			};

			class NS1_Sub1_Sub1_CClass2_Descendant4 : public NS1_Sub1_Sub1_CClass2_Descendant2
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant4(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant4(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Descendant4)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Descendant4)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2_Descendant2)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Descendant4)
			};

			class NS1_Sub1_Sub1_CClass2_Descendant5 : public NS1_Sub1_Sub1_CClass2_Descendant3
			{
			public:
				NS1_Sub1_Sub1_CClass2_Descendant5(void);
				virtual ~NS1_Sub1_Sub1_CClass2_Descendant5(void);

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass2_Descendant5)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass2_Descendant5)
				MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass2_Descendant3)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass2_Descendant5)
			};

			class NS1_Sub1_Sub1_CClass3
			{
			public:
				NS1_Sub1_Sub1_CClass3(void);
				~NS1_Sub1_Sub1_CClass3(void);
			public:
				class NS1_Sub1_Sub1_CClass3_Inner1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1(void);
					~NS1_Sub1_Sub1_CClass3_Inner1(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1)
				};
				class NS1_Sub1_Sub1_CClass3_Inner2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner2(void);
					virtual ~NS1_Sub1_Sub1_CClass3_Inner2(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner2)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner2)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner2)
				};
				class NS1_Sub1_Sub1_CClass3_Inner3
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner3(void);
					~NS1_Sub1_Sub1_CClass3_Inner3(void);
				public:
					class NS1_Sub1_Sub1_CClass3_Inner3_Inner1
					{
					public:
						NS1_Sub1_Sub1_CClass3_Inner3_Inner1(void);
						~NS1_Sub1_Sub1_CClass3_Inner3_Inner1(void);

					MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner3_Inner1)
					MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner3_Inner1)
					MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner3_Inner1)
					};

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner3)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner3)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner3)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Derived1 : public NS1_Sub1_Sub1_CClass3_Inner1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Derived1(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Derived1(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Derived1)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Derived1)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Derived1)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Derived2 : public NS1_Sub1_Sub1_CClass3_Inner1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Derived2(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Derived2(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Derived2)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Derived2)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Derived2)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant1 : public NS1_Sub1_Sub1_CClass3_Inner1_Derived1
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant1(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant1(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Descendant1)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Descendant1)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1_Derived1)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Descendant1)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant2 : public NS1_Sub1_Sub1_CClass3_Inner1_Derived2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant2(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant2(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Descendant2)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Descendant2)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1_Derived2)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Descendant2)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant3 : public NS1_Sub1_Sub1_CClass3_Inner1_Derived1, public NS1_Sub1_Sub1_CClass3_Inner1_Derived2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant3(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant3(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Descendant3)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Descendant3)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1_Derived1)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1_Derived2)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Descendant3)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant4 : public NS1_Sub1_Sub1_CClass3_Inner1_Descendant2
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant4(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant4(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Descendant4)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Descendant4)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1_Descendant2)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Descendant4)
				};
				class NS1_Sub1_Sub1_CClass3_Inner1_Descendant5 : public NS1_Sub1_Sub1_CClass3_Inner1_Descendant3
				{
				public:
					NS1_Sub1_Sub1_CClass3_Inner1_Descendant5(void);
					~NS1_Sub1_Sub1_CClass3_Inner1_Descendant5(void);

				MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3_Inner1_Descendant5)
				MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3_Inner1_Descendant5)
					MD_CLASS_TYPE_BASE_CLASS_DEF(NS1_Sub1_Sub1_CClass3_Inner1_Descendant3)
				MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3_Inner1_Descendant5)
				};

			MD_CLASS_TYPE_DECLARE_BEGIN(NS1_Sub1_Sub1_CClass3)
			MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(NS1_Sub1_Sub1_CClass3)
			MD_CLASS_TYPE_DECLARE_END(NS1_Sub1_Sub1_CClass3)
			};
		} //NameSpasce1_Sub1_Sub1
	} //NameSpace1_Sub1
} //NameSpasce1

namespace NS1
{
	//Declare NS1
	MD_NAME_SPACE_DECLARE(NS1)
	namespace NS1_Sub1
	{
		//Declare NS1_Sub1
		MD_NAME_SPACE_DECLARE(NS1_Sub1)
		namespace NS1_Sub1_Sub1
		{
			//Declare NS1_Sub1_Sub1
			MD_NAME_SPACE_DECLARE(NS1_Sub1_Sub1)
		}
	}
}

extern int global_A;
MD_GLOBAL_VARIABLE_DECLARE(global_A)

extern int global_func(int a);
MD_GLOBAL_FUNCTION_DECLARE(global_func)

#endif //__META_DATA_DEMO__