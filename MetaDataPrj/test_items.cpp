#include "stdafx.h"
#include "test_items.h"

#include "..\Codes\MetaData\include\Demo.h"
#include "..\Codes\Serialization\include\ISerializer.h"
#include "..\Codes\MetaData\include\MetaDataSupport.h"

static CClass3::CClass3_Inner1_Derived1 g_test_items_derived1;

static void do_print_metadata_tree(const CMetaData *pMD, int space_num)
{
	static char FullNameBuffer[256];
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
		do_print_metadata_tree(pMD->GetChild(i), space_num + 1);
	}
}

void test_item_print_metadata_tree(void)
{
	do_print_metadata_tree(&META_DATA_MODULE(), 0);
}

void test_item_serial_bin(char *pFileName, char flag)
{
	if (flag)
	{
		g_test_items_derived1.mem_s = 105;
		g_test_items_derived1.mem_cls1.mem_i = 51;
		g_test_items_derived1.mem_cls1.mem_char = 11;
		g_test_items_derived1.mem_cls1.mem_short = 351;
		g_test_items_derived1.mem_cls1.mem_d = 3324654.112;
		g_test_items_derived1.mem_cls1.mem_f = 391008.8014f;
		g_test_items_derived1.mem_cls1.mem_u_i = 5630;
		g_test_items_derived1.mem_cls1.mem_long = 9023;
		g_test_items_derived1.mem_cls1.p_mem_long = new long;
		*g_test_items_derived1.mem_cls1.p_mem_long = 9284;
		g_test_items_derived1.mem_string.SetValue("abdlewov中文测试。中英文字符串!！");
		g_test_items_derived1.mem_char = 22;
		g_test_items_derived1.mem_float = -10908.20011f;
		g_test_items_derived1.CClass3_Inner1::mem_bool = true;
		g_test_items_derived1.mem_cls2.mem_a = 10;
		g_test_items_derived1.mem_cls2.mem_b = 84904;
	}
	else
	{
		g_test_items_derived1.mem_s = 102;
		g_test_items_derived1.mem_cls1.mem_i = 51;
		g_test_items_derived1.mem_cls1.mem_char = 69;
		g_test_items_derived1.mem_cls1.mem_short = 351;
		g_test_items_derived1.mem_cls1.mem_d = 2964.80092;
		g_test_items_derived1.mem_cls1.mem_f = 83198.83014f;
		g_test_items_derived1.mem_cls1.mem_u_i = 563013;
		g_test_items_derived1.mem_cls1.mem_long = 902633;
		g_test_items_derived1.mem_cls1.p_mem_long = new long;
		*g_test_items_derived1.mem_cls1.p_mem_long = 923384;
		g_test_items_derived1.mem_string.SetValue("中文测试。中英文字符串!！abdlewov~");
		g_test_items_derived1.mem_char = 89;
		g_test_items_derived1.mem_float = -8331.84032f;
		g_test_items_derived1.CClass3_Inner1::mem_bool = false;
		g_test_items_derived1.mem_cls2.mem_a = 1880;
		g_test_items_derived1.mem_cls2.mem_b = 5433904;
	}
	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
	pSerial->SetStructInStream(sisBin);
	Ser->SetSerial(pSerial);
	if (!Ser->Serialize(&g_test_items_derived1, "cls3_inner1_derived1"))
	{
		printf(" Ser->Serialize error.\n");
		return;
	}
	if (pSerial->SaveToFile(pFileName))
	{
		printf(" save seuccessful.\n");
	}
	else
	{
		printf(" save failure.\n");
	}
	delete Ser;
	delete pSerial;
}

void test_item_unserial_bin(char *pFileName)
{
	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
	pSerial->SetStructInStream(sisBin);
	CClass3::CClass3_Inner1_Derived1 *pObj;
	if (pSerial->LoadFromFile(pFileName))
	{
		printf("\n\n");
		pSerial->DebugPrintSelf();
		printf("\n\n");
	}
	else
	{
		printf(" load error.\n");
		return;
	}
	pObj = &g_test_items_derived1;
	Ser->SetSerial(pSerial);
	if (Ser->Unserialize("cls3_inner1_derived1", &pObj))
	{
		printf(" load successful.\n");
	}
	else
	{
		printf(" load failure.\n");
	}
	delete Ser;
	delete pSerial;
}

void test_item_serial_xml(char *pFileName, char flag)
{
	if (flag)
	{
		g_test_items_derived1.mem_s = 105;
		g_test_items_derived1.mem_cls1.mem_i = 51;
		g_test_items_derived1.mem_cls1.mem_char = 11;
		g_test_items_derived1.mem_cls1.mem_short = 351;
		g_test_items_derived1.mem_cls1.mem_d = 3324654.112;
		g_test_items_derived1.mem_cls1.mem_f = 391008.8014f;
		g_test_items_derived1.mem_cls1.mem_u_i = 5630;
		g_test_items_derived1.mem_cls1.mem_long = 9023;
		g_test_items_derived1.mem_cls1.p_mem_long = new long;
		*g_test_items_derived1.mem_cls1.p_mem_long = 9284;
		g_test_items_derived1.mem_string.SetValue("ssssssssssssssssssss");
		g_test_items_derived1.mem_char = 22;
		g_test_items_derived1.mem_float = -10908.20011f;
		g_test_items_derived1.CClass3_Inner1::mem_bool = true;
		g_test_items_derived1.mem_cls2.mem_a = 10;
		g_test_items_derived1.mem_cls2.mem_b = 84904;
	}
	else
	{
		g_test_items_derived1.mem_s = 102;
		g_test_items_derived1.mem_cls1.mem_i = 51;
		g_test_items_derived1.mem_cls1.mem_char = 69;
		g_test_items_derived1.mem_cls1.mem_short = 351;
		g_test_items_derived1.mem_cls1.mem_d = 2964.80092;
		g_test_items_derived1.mem_cls1.mem_f = 83198.83014f;
		g_test_items_derived1.mem_cls1.mem_u_i = 563013;
		g_test_items_derived1.mem_cls1.mem_long = 902633;
		g_test_items_derived1.mem_cls1.p_mem_long = new long;
		*g_test_items_derived1.mem_cls1.p_mem_long = 923384;
		g_test_items_derived1.mem_string.SetValue("aaaaaaaaaaaaaaaa");
		g_test_items_derived1.mem_char = 89;
		g_test_items_derived1.mem_float = -8331.84032f;
		g_test_items_derived1.CClass3_Inner1::mem_bool = false;
		g_test_items_derived1.mem_cls2.mem_a = 1880;
		g_test_items_derived1.mem_cls2.mem_b = 5433904;
	}
	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
	pSerial->SetStructInStream(sisXml);
	Ser->SetSerial(pSerial);
	if (!Ser->Serialize(&g_test_items_derived1, "cls3_inner1_derived1"))
	{
		printf(" Ser->Serialize error.\n");
		return;
	}
	if (pSerial->SaveToFile(pFileName))
	{
		printf(" save seuccessful.\n");
	}
	else
	{
		printf(" save failure.\n");
	}
}

void test_item_unserial_xml(char *pFileName)
{
	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
	pSerial->SetStructInStream(sisXml);
	CClass3::CClass3_Inner1_Derived1 *pObj;
	if (pSerial->LoadFromFile(pFileName))
	{
		printf("\n\n");
		pSerial->DebugPrintSelf();
		printf("\n\n");
	}
	else
	{
		printf(" load error.\n");
		return;
	}
	pObj = &g_test_items_derived1;
	Ser->SetSerial(pSerial);
	if (Ser->Unserialize("cls3_inner1_derived1", &pObj))
	{
		printf(" load successful.\n");
	}
	else
	{
		printf(" load failure.\n");
	}
	delete Ser;
	delete pSerial;
}

void test_item_metadata_function_call(void)
{
	const CMetaData *pMD;
	const CMetaDataClassType *pClsType;
	const CMetaDataFunction *pFunc;
	pMD = META_DATA_MODULE().FindChildMetaData(D_META_DATA_TYPE_ID_CLASS_TYPE, "");
	if (pMD)
		pClsType = reinterpret_cast<const CMetaDataClassType*>(pMD);
	else return;
	pFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, ""));
	if (pFunc)
	{
		//pFunc->CallFuction(0);
	}
	else return;
}