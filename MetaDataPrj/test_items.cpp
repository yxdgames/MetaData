#include "stdafx.h"
#include "test_items.h"

#include "..\Codes\MetaData\include\Demo2.h"
#include "..\Codes\Serialization\include\ISerializer.h"

void test_item_serial_bin(void)
{
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
		return;
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
}

void test_item_serial_xml(void)
{
}