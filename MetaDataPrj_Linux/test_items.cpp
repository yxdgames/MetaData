#include "test_items.h"
#include "../Codes/MetaData/include/Demo/Demo.h"
#include "../Codes/Serialization/include/ISerializer.h"
#include "../Codes/MetaData/include/MetaDataSupport.h"

#ifdef __META_DATA_DEMO__
static CClass3::CClass3_Inner1_Derived1 g_test_items_derived1;
#endif //__META_DATA_DEMO__

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
	for (size_t i = 0; i < pMD->GetChildrenCount(); ++i)
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
#ifdef __META_DATA_DEMO__
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
#endif //__META_DATA_DEMO__
}

void test_item_unserial_bin(char *pFileName)
{
#ifdef __META_DATA_DEMO__
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
#endif //__META_DATA_DEMO__
}

void test_item_serial_xml(char *pFileName, char flag)
{
#ifdef __META_DATA_DEMO__
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
#endif //__META_DATA_DEMO__
}

void test_item_unserial_xml(char *pFileName)
{
#ifdef __META_DATA_DEMO__
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
#endif //__META_DATA_DEMO__
}

void test_item_metadata_function_call(void)
{
#ifdef __META_DATA_DEMO__
	const CMetaData *pMD;
	const CMetaDataClassType *pClsType;
	const CMetaDataFunction *pTmpFunc;
	const CMetaDataFunction *pFunc;
	
	pMD = META_DATA_GLOBALSPACE().FindChildMetaData(D_META_DATA_TYPE_ID_CLASS_TYPE, "::CClass1");
	if (!pMD) return;
	
	pClsType = reinterpret_cast<const CMetaDataClassType*>(pMD);
	void *pObj(pClsType->CreateObject<CClass1>());

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::cls1_func1"));
	if (pTmpFunc)
	{
		pFunc = pTmpFunc;
		int a = 100;
		double d = 11.22;
		int ret;
		pFunc->CallFunction(3, pObj, a, d, &ret);
		printf(" ret: %d\n\n", ret);
	}

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::cls1_func2"));
	if (pTmpFunc)
	{
		pFunc = pTmpFunc;
		unsigned char c(134);
		double d(13998.321);
		int ret;
		pFunc->CallFunction(3, pObj, c, d, &ret);
		printf(" ret: %d\n", ret);

		printf("ClassType call\n");
		CFuncParamMDVector param_vector;
		D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, CClass1, 1)
		D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, unsigned char, 0)
		D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, double, 0)
		ret = 0;
		if (!pClsType->CallMemberFuction("cls1_func2", &param_vector, pObj, c, d, &ret))
		{
			printf("ClassType call Error!\n");
		}
		printf("ClassType call ret: %d\n\n", ret);
	}

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::SetParam"));
	if (pTmpFunc)
	{
		pFunc = pTmpFunc;
		SParam param;
		TDByte ret;
		param.Data[0] = 10;
		param.Data[1] = 11;
		param.Data[2] = 32;
		pFunc->CallFunction(4, pObj, param, 20.813, 19, &ret);
		printf(" ret: %d\n\n", ret);
	}

	pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "::CClass1::cls1_vir_func1"));
	if (pTmpFunc)
	{
		pFunc = pTmpFunc;
		float f(83.892f);
		unsigned long l(914);
		double ret;

		CFuncParamMDVector param_vector;
		D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, CClass1, 1)
		D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, float, 0)
		D_FUNC_PARAM_MD_VECTOR_ADD_ELE(param_vector, unsigned long, 0)
		pFunc->CallFunction(&param_vector, pObj, f, l, &ret);
		printf(" ret: %f\n", ret);

		pFunc->CallFunction(3, pObj, f, l, &ret);
		printf(" ret: %f\n\n", ret);
	}

	std::vector<const CMetaData*> vec_metadata;
	if (pClsType->FindChildMetaData(D_META_DATA_TYPE_ID_FUNCTION, "CClass1::cls1_static_func1", vec_metadata))
	{
		for (size_t i = 0; i < vec_metadata.size(); ++i)
		{
			pTmpFunc = reinterpret_cast<const CMetaDataFunction*>(vec_metadata[i]);
			if (pTmpFunc)
			{
				pFunc = pTmpFunc;
				if (pFunc->GetParamCount() > 0)
				{
					int p_x(99);
					double p_d(89523.82319);
					float ret;
					pFunc->CallFunction(2, p_x, p_d, &ret);
					printf(" ret: %f\n\n", ret);
				}
				else
				{
					pFunc->CallFunction(static_cast<size_t>(0));
				}
			}
		}
	}

	pClsType->DeleteObject(pObj);
#endif //__META_DATA_DEMO__
}

void test_item_metadata_property(void)
{
#ifdef __META_DATA_DEMO__
	CClass1 cls1;
	printf("cls1.MemI value:%d\n", static_cast<int>(cls1.MemI));
	cls1.MemI = 107;
	int i = cls1.MemI;
	printf("cls1.MemI value:%d %d\n", static_cast<int>(cls1.MemI), i);
#endif //__META_DATA_DEMO__
}

void test_item_metadata_other(void)
{
	SimpleString *pStr;
	CFuncParamMDVector PVector;
	pStr = reinterpret_cast<SimpleString*>(
		reinterpret_cast<const CMetaDataClassType*>(TypeTraits<SimpleString>::GetMetaDataType())->CreateObject<SimpleString>()
	);
	if (pStr)
	{
		std::cout << pStr->GetValue();
		delete pStr;
	}
	D_FUNC_PARAM_MD_VECTOR_ADD_ELE(PVector, char, 1);
	pStr = reinterpret_cast<SimpleString*>(
		reinterpret_cast<const CMetaDataClassType*>(TypeTraits<SimpleString>::GetMetaDataType())->CreateObject<SimpleString>(&PVector, "字符串指针\n")
	);
	if (pStr)
	{
		std::cout << pStr->GetValue();
		delete pStr;
	}
	SimpleString str("SimpleString对象\n");
	PVector.clear();
	D_FUNC_PARAM_MD_VECTOR_ADD_ELE(PVector, SimpleString, 1);
	pStr = reinterpret_cast<SimpleString*>(
		reinterpret_cast<const CMetaDataClassType*>(TypeTraits<SimpleString>::GetMetaDataType())->CreateObject<SimpleString>(&PVector, &str)
	);
	if (pStr)
	{
		std::cout << pStr->GetValue();
		delete pStr;
	}
}

void test_item_iunkwn_obj_template(void)
{
#ifdef __META_DATA_DEMO__
	IUnkwn *pUnkwn(new TUnkwnObject<CUnkwn>);
	printf("Unkwn Object AddRef:%d\n", pUnkwn->AddRef());
	printf("Unkwn Object AddRef:%d\n", pUnkwn->AddRef());
	printf("Unkwn Object AddRef:%d\n", pUnkwn->AddRef());
	printf("Unkwn Object AddRef:%d\n", pUnkwn->AddRef());
	printf("Unkwn Object AddRef:%d\n", pUnkwn->AddRef());

	printf("Unkwn Object Release:%d\n", pUnkwn->Release());
	printf("Unkwn Object Release:%d\n", pUnkwn->Release());
	printf("Unkwn Object Release:%d\n", pUnkwn->Release());
	printf("Unkwn Object Release:%d\n", pUnkwn->Release());
	IID iid = {
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00,
		0x00, 0x00,
		0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46
	}; //{ 0x00000000, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
	void *outUnkwn(nullptr);
	if (pUnkwn->QueryInterface(iid, &outUnkwn) == 0)
	{
		printf("QueryInterface successfully:%p - %p\n", pUnkwn, outUnkwn);
		reinterpret_cast<IUnkwn*>(outUnkwn)->Release();
	}
	else printf("QueryInterface failure:%p - %p\n", pUnkwn, outUnkwn);
	printf("Unkwn Object Release:%d\n", pUnkwn->Release());
#endif //__META_DATA_DEMO__
}
