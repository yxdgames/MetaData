#include "test_items.h"
#include <iostream>
#include <string.h>

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
		<<" unkwn_object_template : test UnkwnObject Template."<<std::endl \
		<<" other : ..."<<std::endl \
		<<" exit : exit application."<<std::endl<<std::endl; \
	}
#define D_INPUT_LOGO	(" >")

int main(int argn, const char **argv)
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
		else if (strcmp(input_string, "unkwn_object_template") == 0)
		{
			test_item_iunkwn_obj_template();
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