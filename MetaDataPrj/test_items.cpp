#include "stdafx.h"
#include "test_items.h"

#include "..\Codes\MetaData\include\Demo.h"
//#include "..\Codes\Serialization\include\ISerializer.h"

#if 0
static void do_print_metadata_tree(const CMetaData *pMD, int space_num)
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
#endif

void test_item_print_metadata_tree(void)
{
}

void test_item_serial_bin(void)
{
}

void test_item_serial_xml(void)
{
}