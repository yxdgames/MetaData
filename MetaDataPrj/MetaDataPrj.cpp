// MetaDataPrj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "..\Codes\MetaData\include\Demo2.h"
//#include "..\Codes\MetaData\include\MetaData.h"
//#include "..\Codes\MetaData\include\MetaDataSupport.h"
//#include "..\Codes\MetaData\include\MetaDataObjects.h"
//#include "..\Codes\MetaData\include\TypeTraits.h"
#include "..\Codes\Serialization\include\ISerializer.h"

#include <stdarg.h>
#include <iostream>
#include <fstream>

void PrintMetaDataTree(const CMetaData *pMD, int space_num)
{
	char FullNameBuffer[256];
	if (space_num > 1)
	{
		printf("  ");
		for (int i = 0; i < space_num - 1; ++i)
		{
			printf("| ");
		}
		printf("|-");
	}
	else if (space_num == 1)
	{
		printf("  |-");
	}
	else //if (space_num == 0)
	{
		printf("--");
		printf("Module_None\n");
	}
	if (space_num > 0)
	{
		if (pMD->GetFullName(FullNameBuffer, 256))
		{
			printf("%s [%s]\n", FullNameBuffer, pMD->GetTypeCaption());
		}
		else printf("__None__\n");
	}
	for (unsigned int i = 0; i < pMD->GetChildrenCount(); ++i)
	{
		PrintMetaDataTree(pMD->GetChild(i), space_num + 1);
	}
}

void tst(int num, ...)
{
	int a;
	double b;
	int cnt(0);
	va_list pList;
	va_start(pList, num);
	for (int i = 0; i < num; ++i)
	{
		if (cnt % 2)
		{
			b = va_arg(pList, double);
			printf("b = %f\n", b);
		}
		else
		{
			a = va_arg(pList, int);
			printf("a = %d\n", a);
		}
		++cnt;
	}
	va_end(pList);
}

class CTst
{
public:
	template <typename T>
	T *AsType(void)
	{
		return reinterpret_cast<T*>(0);
	}
};

//#define D_SERIAL_TEST
//#define D_XML_TEST

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef D_SERIAL_TEST
	NTest::CClsInNS1 cins, *pCINS(NULL);
	cins.CNone::ax = -12;
	cins.CNone::bx = -81.102;
	cins.CNone::str.SetValue("test string....!");
	//cins.CNone::str.SetValue("中文二进制文件测试！！！~。。");
	cins.CNone_2::a = 5950;
	cins.CNone_2::u = 9011;
	cins.CNone_2::d = -5208.62;
	cins.uab.ax = 18559;
	cins.uab.bx = -9328.3011343;
	cins.uab.str.SetValue("var string. test~~");
	//cins.uab.str.SetValue("一帆风顺！中文测试字符串。");
	cins.x = -651013.22;
	cins.b = 10008.200011f;
	cins.z = 89556110;
	cins.a = 3001123;

	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
#ifdef D_XML_TEST
	pSerial->SetStructInStream(sisXml);
#else
	pSerial->SetStructInStream(sisBin);
#endif
	Ser->SetSerial(pSerial);
	if (!Ser->Serialize(&cins, "cins"))
	{
		printf("Ser->Serialize error.\n");
		return 0;
	}
#ifdef D_XML_TEST
	if (pSerial->SaveToFile("E:\\Obj01.xml"))
#else
	if (pSerial->SaveToFile("E:\\Obj01.bin"))
#endif
	{
		printf("save seuccessful.\n");
	}
	else
	{
		printf("save failure.\n");
	}

	//test load
#ifdef D_XML_TEST
	if (pSerial->LoadFromFile("E:\\Obj02.xml"))
#else
	//if (pSerial->LoadFromFile("E:\\Obj02_en.bin"))
	if (pSerial->LoadFromFile("E:\\Obj02_ch.bin"))
#endif
	{
		printf("\n\n");
		pSerial->DebugPrintSelf();
		printf("\n\n");
		pCINS = &cins;
		Ser->SetSerial(pSerial);
		if (Ser->Unserialize("cins", &pCINS))
		{
			printf("load successful.\n");
		}
		else
		{
			printf("load failure.\n");
		}
	}
	else
	{
		printf("load error.\n");
	}
	delete Ser;
	delete pSerial;
#else
	try
	{
		try
		{
			//tst(5, 11, 22.45, 123, 9.80, 8);

			PrintMetaDataTree(&META_DATA_MODULE(), 0);

			double x(10.5);
			int y(3);
			double ret;
			if (META_DATA_GLOBAL_FUNCTION(FuncDemo).CallFuction(2, x, y, &ret))
				printf("x=%f, y=%d, ret=%f\n", x, y, ret);

			CMetaDataFunction *pMDFunc((CMetaDataFunction*)META_DATA_MODULE().FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::NTest::CClsInNS1::CClsInCL2::func1"));
			if (pMDFunc)
			{
				//NTest::CB::CINB obj;
				::NTest::CClsInNS1::CClsInCL2 objCIC2;
				int a = -130;
				float b = 3.98f;
				CNone_2 ret;
				//double *pR = &ret;
		
				if (pMDFunc->CallFuction(2, &objCIC2, a, &ret))
					printf("ok: ret = %d\n", ret.a);
					//printf("ok\n");
				else printf("error\n");
			}

			CMetaDataClassType *pMDClass((CMetaDataClassType*)META_DATA_MODULE().FindChildMetaData(D_META_DATA_TYPE_ID_CLASS_TYPE, "::CNone::CClsInCL1::CLSInCL2::CClsInCL3"));
			if (pMDClass)
			{
				::CNone::CClsInCL1::CLSInCL2::CClsInCL3 *pCIC3;
				::NTest::CClsInNS1 obj_b;
				CNone_2 *pCX;
				//CParamVector PV;
				::CNone::CClsInCL1 oCIC1;
				::CNone::CClsInCL1::CLSInCL2::CClsInCL3 oCIC3;
				oCIC1.XXX = -1;
				oCIC3.XXX = -4;
				if (obj_b.IsTypeOf<CNone_2>())
				{
					pCX = obj_b.AsType<CNone_2>();
					if (pCX)
					{
						printf("IsTypeOf TRUE. u = %d, d = %f\n", pCX->u, pCX->d);
					}
					else printf("IsTypeOf TRUE\n");
				}
				else printf("IsTypeOf FALSE\n");
				//D_PARAM_VECTOR_ADD_ELE(PV, ::CNone::CClsInCL1, 0);
				//D_PARAM_VECTOR_ADD_ELE(PV, ::CNone::CClsInCL1::CLSInCL2::CClsInCL3, 1);
				//pCIC3 = pMDClass->CreateObject<::CNone::CClsInCL1::CLSInCL2::CClsInCL3>(&PV, oCIC1, (::CNone::CClsInCL1::CLSInCL2::CClsInCL3*)NULL);
				pCIC3 = pMDClass->CreateObject<::CNone::CClsInCL1::CLSInCL2::CClsInCL3>();
				if (pCIC3)
				{
					pCIC3->PrintSelfStr();
				}
				else printf("pCIC3 is NULL.\n");
				if (pMDClass->QueryBaseType(&obj_b, "::CNone_2", (void**)&pCX))
				{
					double ret(pCX->GetCalc(6.5f));
					printf("Query base type: ret = %f\n", ret);
				}
		//		pMDClass->CreateObject<NTest::CClsInNS1>(Params);
			}

			//CMetaDataType *pType(TypeTraits<void*>::GetMetaDataType());

			//throw new ExceptionMetaData(-1, "异常机制测试！");
		}
		catch(ExceptionMetaData*)
		{
			throw;
		}
	}
	catch (ExceptionMetaData *pE_MD)
	{
		if (pE_MD->GetCaption() != NULL)
			printf("\n-----------------------Exception-----------------------\n"\
				   "MetaData Exception: ID[%d], Message[%s]\n"\
				   "-----------------------Exception-----------------------\n\n", pE_MD->GetID(), pE_MD->GetCaption());
		else printf("MetaData Exception: ID[%d]\n", pE_MD->GetID());
		delete pE_MD;
	}
#endif
	getchar();
	return 0;
}

