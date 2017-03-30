#pragma once

#include "..\include\MetaDataSupport.h"
#include "..\include\MetaDataClassType.h"
#include "..\include\TypeTraits.h"
#include "..\include\SimpleString.h"

//#define	__META_DATA_DEMO2__

#ifdef __META_DATA_DEMO2__
////////////////////////////////////////////////
//                  Demo                      //
////////////////////////////////////////////////
class CNone
{
public:
	void PrintSelf(void)
	{
		printf("ax:%d, bx:%f, str:%s\n", ax, bx, str.GetValue());
	}
public:
	int ax;
	double bx;
	SimpleString str;
public:
	CNone(void)	: str("UTF-8 Testing...~!") {}
	CNone(int a, double x):ax(a), bx(x)	{}
	~CNone(void)	{}
public:
	double Memfunc1(int o, double u)
	{
		return o * u;
	}
	static float SMFunc1(long a, float b)
	{
		return b != 0 ? a / b : 0;
	}
public:
	class CClsInCL1
	{
	public:
		int XXX;
		double u;
		float z;
	public:
		class CLSInCL2
		{
		public:
			int XXX;
			double u;
			float z;
		public:
			class CClsInCL3
			{
			public:
				CClsInCL3(void) : XXX(0)		{}
				CClsInCL3(char c, CClsInCL1 obj) : XXX(obj.XXX)	{}
				CClsInCL3(CClsInCL1 o, CClsInCL3 *obj) : XXX(obj ? obj->XXX : -98)	{}
				~CClsInCL3(void)	{}
			public:
				void PrintSelfStr(void)		{ printf("obj - CClsInCL3::PrintSelfStr. XXX = %d\n", XXX); }
			public:
				int XXX;
				double u;
				float z;
			MD_CLASS_TYPE_DECLARE_BEGIN(CClsInCL3)
				MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(CClsInCL3, 0)
				MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(CClsInCL3, 1)
				MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(CClsInCL3, 2)
			MD_CLASS_TYPE_DECLARE_DETAIL(CClsInCL3)
				MD_CLASS_TYPE_CONSTRUCTOR_DEF(CClsInCL3, 0)
				MD_CLASS_TYPE_CONSTRUCTOR_DEF(CClsInCL3, 1)
					MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(c, *TypeTraits<char>::GetMetaDataType(), 0)
					MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(obj, *TypeTraits<CClsInCL1>::GetMetaDataType(), 0)
				MD_CLASS_TYPE_CONSTRUCTOR_DEF(CClsInCL3, 2)
					MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(o, *TypeTraits<CClsInCL1>::GetMetaDataType(), 0)
					MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(obj, *TypeTraits<CClsInCL3>::GetMetaDataType(), 1)
			MD_CLASS_TYPE_DECLARE_END(CClsInCL3)
			};
		MD_CLASS_TYPE_DECLARE_BEGIN(CLSInCL2)
		MD_CLASS_TYPE_DECLARE_DETAIL(CLSInCL2)
		MD_CLASS_TYPE_DECLARE_END(CLSInCL2)
		};
	MD_CLASS_TYPE_DECLARE_BEGIN(CClsInCL1)
	MD_CLASS_TYPE_DECLARE_DETAIL(CClsInCL1)
	MD_CLASS_TYPE_DECLARE_END(CClsInCL1)
	};
MD_CLASS_TYPE_DECLARE_BEGIN(CNone)
   MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(CNone, 0)
   MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(CNone, 1)
   MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(CNone, Memfunc1, 0)
   MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(CNone, SMFunc1, 0)
MD_CLASS_TYPE_DECLARE_DETAIL(CNone)
   MD_CLASS_TYPE_CONSTRUCTOR_DEF(CNone, 0)
   MD_CLASS_TYPE_CONSTRUCTOR_DEF(CNone, 1)
       MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(a, *TypeTraits<int>::GetMetaDataType(), 0)
       MD_CLASS_TYPE_CONSTRUCTOR_PARAM_DEF(x, *TypeTraits<double>::GetMetaDataType(), 0)
   MD_CLASS_TYPE_MEMBER_FUNC_DEF(CNone, Memfunc1, 0)
       MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(o, *TypeTraits<int>::GetMetaDataType(), 0)
       MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(u, *TypeTraits<double>::GetMetaDataType(), 0)
       MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<double>::GetMetaDataType(), 0)
   MD_CLASS_TYPE_MEMBER_VAR_DEF(CNone, ax, (*TypeTraits<int>::GetMetaDataType()), 0)
   MD_CLASS_TYPE_MEMBER_VAR_DEF(CNone, bx, (*TypeTraits<double>::GetMetaDataType()), 0)
   MD_CLASS_TYPE_MEMBER_VAR_DEF(CNone, str, (*TypeTraits<SimpleString>::GetMetaDataType()), 0)
   MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(CNone, SMFunc1, 0)
       MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(a, *TypeTraits<long>::GetMetaDataType(), 0)
       MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(b, *TypeTraits<float>::GetMetaDataType(), 0)
       MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(*TypeTraits<float>::GetMetaDataType(), 0)
MD_CLASS_TYPE_DECLARE_END(CNone)
};

class CNone_2
{
public:
	CNone_2(void):u(13), d(8.3)	{}
public:
	void PrintSelf(void)
	{
		printf("a:%d, u:%d, d:%f\n", a, u, d);
	}
	double GetCalc(float a)	{ return u * d + a; }
	int a;
public:
	int u;
	double d;
MD_CLASS_TYPE_DECLARE_BEGIN(CNone_2)
MD_CLASS_TYPE_DECLARE_DETAIL(CNone_2)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(CNone_2, a, (*TypeTraits<int>::GetMetaDataType()), 0)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(CNone_2, u, (*TypeTraits<int>::GetMetaDataType()), 0)
	MD_CLASS_TYPE_MEMBER_VAR_DEF(CNone_2, d, (*TypeTraits<double>::GetMetaDataType()), 0)
MD_CLASS_TYPE_DECLARE_END(CNone_2)
};

MD_GLOBAL_FUNCTION_DECLARE(FuncDemo)
double FuncDemo(double x, int y);

namespace NTest
{
	class CClsInNS1 : public CNone, public CNone_2
	{
	public:
		void PrintSelf(void)
		{
			this->CNone::PrintSelf();
			this->CNone_2::PrintSelf();
			uab.PrintSelf();
			printf("x:%f, b:%f, z:%d, a:%d\n", x, b, z, a);
		}
	public:
		CNone uab;
		double x;
		float b;
		long z;
		int a;
	public:
		class CClsInCL2
		{
		private:
			float cbd;
			unsigned long xudb;
			static double static_var;
			CNone_2 func1(int a)
			{
				CNone_2 n_2;
				n_2.a = a;
				return n_2;
			}
			static double sfunc_1(int a, float b) { return a * b; }

		MD_CLASS_TYPE_DECLARE_BEGIN(CClsInCL2)
			MD_CLASS_TYPE_MEMBER_FUNC_WRAPPER_DECLARE(CClsInCL2, func1, 0)
			MD_CLASS_TYPE_STATIC_MEMBER_FUNC_WRAPPER_DECLARE(CClsInCL2, sfunc_1, 0)
		MD_CLASS_TYPE_DECLARE_DETAIL(CClsInCL2)
			MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInCL2, cbd, META_DATA_INNER_TYPE(float), 0)
			MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInCL2, xudb, META_DATA_INNER_TYPE(unsigned long), 0)
			MD_CLASS_TYPE_STATIC_MEMBER_VAR_DEF(CClsInCL2, static_var, META_DATA_INNER_TYPE(double), 0)
			MD_CLASS_TYPE_MEMBER_FUNC_DEF(CClsInCL2, func1, 0)
				MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(this, *TypeTraits<CClsInCL2>::GetMetaDataType(), 1)
				MD_CLASS_TYPE_MEMBER_FUNC_PARAM_DEF(a, *TypeTraits<int>::GetMetaDataType(), 0)
				MD_CLASS_TYPE_MEMBER_FUNC_RETURN_DEF(*TypeTraits<CNone_2>::GetMetaDataType(), 0)
			MD_CLASS_TYPE_STATIC_MEMBER_FUNC_DEF(CClsInCL2, sfunc_1, 0)
				MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(a, *TypeTraits<int>::GetMetaDataType(), 0)
				MD_CLASS_TYPE_STATIC_MEMBER_FUNC_PARAM_DEF(b, *TypeTraits<float>::GetMetaDataType(), 0)
				MD_CLASS_TYPE_STATIC_MEMBER_FUNC_RETURN_DEF(*TypeTraits<double>::GetMetaDataType(), 0)
		MD_CLASS_TYPE_DECLARE_END(CClsInCL2)
		};
	MD_CLASS_TYPE_DECLARE_BEGIN(CClsInNS1)
	MD_CLASS_TYPE_DECLARE_DETAIL(CClsInNS1)
	   MD_CLASS_TYPE_BASE_CLASS_DEF(CClsInNS1, CNone)
	   MD_CLASS_TYPE_BASE_CLASS_DEF(CClsInNS1, CNone_2)
	   MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInNS1, uab, *TypeTraits<CNone>::GetMetaDataType(), 0)
	   MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInNS1, x, *TypeTraits<double>::GetMetaDataType(), 0)
	   MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInNS1, b, *TypeTraits<float>::GetMetaDataType(), 0)
	   MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInNS1, z, *TypeTraits<long>::GetMetaDataType(), 0)
	   MD_CLASS_TYPE_MEMBER_VAR_DEF(CClsInNS1, a, *TypeTraits<int>::GetMetaDataType(), 0)
	MD_CLASS_TYPE_DECLARE_END(CClsInNS1)
	};

	namespace NTst2
	{
		class CClsInNS2
		{
		MD_CLASS_TYPE_DECLARE_BEGIN(CClsInNS2)
		MD_CLASS_TYPE_DECLARE_DETAIL(CClsInNS2)
		MD_CLASS_TYPE_DECLARE_END(CClsInNS2)
		};
		namespace NTst3
		{
			class CClsInNS3
			{
			MD_CLASS_TYPE_DECLARE_BEGIN(CClsInNS3)
			MD_CLASS_TYPE_DECLARE_DETAIL(CClsInNS3)
			MD_CLASS_TYPE_DECLARE_END(CClsInNS3)
			}; 
		}
	}
}

MD_GLOBAL_FUNCTION_DECLARE(GetNone)
extern NTest::CClsInNS1 GetNone(int ax, double bx);

#endif //__META_DATA_DEMO2__