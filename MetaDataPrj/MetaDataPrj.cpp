// MetaDataPrj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test_items.h"

#include <stdarg.h>
#include <iostream>

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

#define D_COMMAND_HELP	{ \
		std::cout<<" >>>>>>>>>>>>>>>>>>>test console<<<<<<<<<<<<<<<<<<<"<<std::endl \
		<<" metadata_tree : print tree of meta data."<<std::endl \
		<<" serial_bin 0 : save tested object to binary file."<<std::endl \
		<<" serial_bin 1 : save tested object to binary file."<<std::endl \
		<<" unserial_bin : save tested object to binary file."<<std::endl \
		<<" serial_xml 0 : save tested object to xml file."<<std::endl \
		<<" serial_xml 1 : save tested object to xml file."<<std::endl \
		<<" unserial_xml : save tested object to xml file."<<std::endl \
		<<" func_call : call function."<<std::endl \
		<<" property : test property."<<std::endl \
		<<" other : ..."<<std::endl \
		<<" exit : exit application."<<std::endl<<std::endl; \
	}
#define D_INPUT_LOGO	(" >")

int _tmain(int argc, _TCHAR* argv[])
{
	char input_string[128];

	D_COMMAND_HELP
	std::cout<<D_INPUT_LOGO;
	while (true)
	{
		std::cin.getline(input_string, 128);
		if (strcmp(input_string, "exit") == 0)
		{
			break;
		}
		else if (strcmp(input_string, "help") == 0)
		{
			std::cout<<std::endl;
			D_COMMAND_HELP
		}
		else if (strcmp(input_string, "metadata_tree") == 0)
		{
			test_item_print_metadata_tree();
		}
		else if (strcmp(input_string, "serial_bin 1") == 0)
		{
			std::cout<<" input destination: ";
			std::cin.getline(input_string, 128);
			test_item_serial_bin(input_string, 1);
		}
		else if (strcmp(input_string, "serial_bin 0") == 0)
		{
			std::cout<<" input destination: ";
			std::cin.getline(input_string, 128);
			test_item_serial_bin(input_string, 0);
		}
		else if (strcmp(input_string, "unserial_bin") == 0)
		{
			std::cout<<" input destination: ";
			std::cin.getline(input_string, 128);
			test_item_unserial_bin(input_string);
		}
		else if (strcmp(input_string, "serial_xml 1") == 0)
		{
			std::cout<<" input destination: ";
			std::cin.getline(input_string, 128);
			test_item_serial_xml(input_string, 1);
		}
		else if (strcmp(input_string, "serial_xml 0") == 0)
		{
			std::cout<<" input destination: ";
			std::cin.getline(input_string, 128);
			test_item_serial_xml(input_string, 0);
		}
		else if (strcmp(input_string, "unserial_xml") == 0)
		{
			std::cout<<" input destination: ";
			std::cin.getline(input_string, 128);
			test_item_unserial_xml(input_string);
		}
		else if (strcmp(input_string, "func_call") == 0)
		{
			test_item_metadata_function_call();
		}
		else if (strcmp(input_string, "property") == 0)
		{
			test_item_metadata_property();
		}
		else if (strcmp(input_string, "other") == 0)
		{
			test_item_metadata_other();
		}
		else
		{
			if (input_string[0] != '\0')
			{
				std::cout<<" error command!"<<std::endl;
			}
		}
		std::cout<<D_INPUT_LOGO;
	}
	std::cout<<" Application has exit."<<std::endl;

	return 0;
}

