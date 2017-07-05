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
	do_print_metadata_tree(&META_DATA_GLOBALSPACE(), 0);
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
	CMetaDataClassType *pClsType;
	const CMetaDataFunction *pTmpFunc;
	CMetaDataFunction *pFunc;
	
	pMD = META_DATA_GLOBALSPACE().FindChildMetaData(D_META_DATA_TYPE_ID_CLASS_TYPE, "::CClass1");
	if (!pMD) return;
	
	pClsType = const_cast<CMetaDataClassType*>(reinterpret_cast<const CMetaDataClassType*>(pMD));
	void *pObj(pClsType->NewObject());

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::cls1_func1"));
	if (pTmpFunc)
	{
		pFunc = const_cast<CMetaDataFunction *>(pTmpFunc);
		int a = 100;
		double d = 11.22;
		int ret;
		pFunc->CallFuction(3, pObj, a, d, &ret);
		printf(" ret: %d\n", ret);
	}

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::cls1_func2"));
	if (pTmpFunc)
	{
		pFunc = const_cast<CMetaDataFunction *>(pTmpFunc);
		unsigned char c(134);
		double d(13998.321);
		int ret;
		pFunc->CallFuction(3, pObj, c, d, &ret);
		printf(" ret: %d\n", ret);

		printf("ClassType call\n");
		pClsType->CallMemberFuction("cls1_func2", 3, pObj, c, d, &ret);
		printf("ClassType call ret: %d\n", ret);
	}

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::cls1_vir_func1"));
	if (pTmpFunc)
	{
		pFunc = const_cast<CMetaDataFunction *>(pTmpFunc);
		float f(83.892f);
		unsigned long l(914);
		double ret;

		CParamVector param_vector;
		param_vector.push_back(new CMetaDataVarBase("this", NULL, TypeTraits<CClass1>::GetMetaDataType(), 1));
		param_vector.push_back(new CMetaDataVarBase("f", NULL, TypeTraits<float>::GetMetaDataType(), 0));
		param_vector.push_back(new CMetaDataVarBase("l", NULL, TypeTraits<unsigned long>::GetMetaDataType(), 0));
		pFunc->CallFuction(&param_vector, pObj, f, l, &ret);
		printf(" ret: %f\n", ret);

		pFunc->CallFuction(3, pObj, f, l, &ret);
		printf(" ret: %f\n", ret);
	}

	std::vector<CMetaData*> vec_metadata;
	if (pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "CClass1::cls1_static_func1", vec_metadata))
	{
		for (unsigned int i = 0; i < vec_metadata.size(); ++i)
		{
			pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(vec_metadata[i]);
			if (pTmpFunc)
			{
				pFunc = const_cast<CMetaDataFunction *>(pTmpFunc);
				if (pFunc->GetParamCount() > 0)
				{
					int p_x(99);
					double p_d(89523.82319);
					float ret;
					pFunc->CallFuction(2, p_x, p_d, &ret);
					printf(" ret: %f\n", ret);
				}
				else
				{
					pFunc->CallFuction(0);
				}
			}
		}
	}

	pClsType->DeleteObject(pObj);
}