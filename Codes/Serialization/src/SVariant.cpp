#include "stdafx.h"
#include "..\include\SVariant.h"

SVariant::SVariant(void)
	: type(vtNone), release_string(true)
{
	memset(&value, 0x00, sizeof(value));
}

SVariant::SVariant(SVariant &src)
{
	this->operator=(src);
}

SVariant::~SVariant(void)
{
	FreeStr();
}

void SVariant::SetValue(SVariant &src)
{
	FreeStr();
	this->type = src.type;
	this->release_string = src.release_string;
	if (this->type != vtCSTR_PTR || !(this->release_string))
	{
		this->value = src.value;
	}
	else
	{
		if (src.value._pcstr)
		{
			value._pcstr = new char [strlen(src.value._pcstr) + 1];
			strcpy(const_cast<char*>(value._pcstr), src.value._pcstr);
		}
		else
		{
			value._pcstr = nullptr;
		}
	}
}

void SVariant::SetValue(const char * const pStr)
{
	FreeStr();
	type = vtCSTR_PTR;
	if (release_string)
	{
		if (pStr)
		{
			value._pcstr = new char [strlen(pStr) + 1];
			strcpy(const_cast<char*>(value._pcstr), pStr);
		}
		else value._pcstr = nullptr;
	}
	else
	{
		value._pcstr = pStr;
	}
}

void SVariant::SetReleaseStringFlag(bool flag)
{
	FreeStr();
	release_string = flag;
}

void SVariant::FreeStr(void)
{
	if (type == vtCSTR_PTR && value._pcstr && release_string)
	{
		delete [] value._pcstr;
		value._pcstr = nullptr;
	}
}
