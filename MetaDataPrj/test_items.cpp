#include "stdafx.h"
#include "test_items.h"

#include "..\Codes\MetaData\include\Demo.h"
#include "..\Codes\Serialization\include\ISerializer.h"

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

void test_item_serial_bin(char *pFileName)
{
	g_test_items_derived1.mem_s = 102;
	g_test_items_derived1.mem_cls1.mem_i = 51;
	g_test_items_derived1.mem_cls1.mem_char = 'W';
	g_test_items_derived1.mem_cls1.mem_short = 351;
	g_test_items_derived1.mem_cls1.mem_d = 294654.8108492;
	g_test_items_derived1.mem_cls1.mem_f = 83921498.8395014f;
	g_test_items_derived1.mem_cls1.mem_u_i = 5630;
	g_test_items_derived1.mem_cls1.mem_long = 9023;
	g_test_items_derived1.mem_cls1.p_mem_long = new long;
	*g_test_items_derived1.mem_cls1.p_mem_long = 9284;
	g_test_items_derived1.mem_string.SetValue("");
	g_test_items_derived1.mem_char = 'U';
	g_test_items_derived1.mem_float = -83231.84920832f;
	g_test_items_derived1.mem_bool = true;
	g_test_items_derived1.mem_cls2.mem_a = 10;
	g_test_items_derived1.mem_cls2.mem_b = 84904;

	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
	pSerial->SetStructInStream(sisBin);
	Ser->SetSerial(pSerial);
	if (!Ser->Serialize(&g_test_items_derived1, "cls3_inner1_derived1"))
	{
		printf("Ser->Serialize error.\n");
		return;
	}
	if (pSerial->SaveToFile(pFileName))
	{
		printf("save seuccessful.\n");
	}
	else
	{
		printf("save failure.\n");
	}
}

void test_item_serial_xml(char *pFileName)
{
	g_test_items_derived1.mem_s = 102;
	g_test_items_derived1.mem_cls1.mem_i = 51;
	g_test_items_derived1.mem_cls1.mem_char = 'W';
	g_test_items_derived1.mem_cls1.mem_short = 351;
	g_test_items_derived1.mem_cls1.mem_d = 294654.8108492;
	g_test_items_derived1.mem_cls1.mem_f = 83921498.8014f;
	g_test_items_derived1.mem_cls1.mem_u_i = 5630;
	g_test_items_derived1.mem_cls1.mem_long = 9023;
	g_test_items_derived1.mem_cls1.p_mem_long = new long;
	*g_test_items_derived1.mem_cls1.p_mem_long = 9284;
	g_test_items_derived1.mem_string.SetValue("ssssssssssssssssssss");
	g_test_items_derived1.mem_char = 'U';
	g_test_items_derived1.mem_float = -10008.200011f;
	g_test_items_derived1.CClass3_Inner1::mem_bool = true;
	g_test_items_derived1.mem_cls2.mem_a = 10;
	g_test_items_derived1.mem_cls2.mem_b = 84904;

	ISerializer *Ser(ISerializer::CreateSerializerIntf());
	ISerial *pSerial(ISerial::CreateSerialIntf());
	pSerial->SetStructInStream(sisXml);
	Ser->SetSerial(pSerial);
	if (!Ser->Serialize(&g_test_items_derived1, "cls3_inner1_derived1"))
	{
		printf("Ser->Serialize error.\n");
		return;
	}
	if (pSerial->SaveToFile(pFileName))
	{
		printf("save seuccessful.\n");
	}
	else
	{
		printf("save failure.\n");
	}
}