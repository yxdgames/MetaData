#include "stdafx.h"
#include "..\include\SVariant.h"

SVariant::SVariant(void)
	: type(vtNone), release_flag(false)
{
	memset(&value, 0x00, sizeof(value));
}

SVariant::SVariant(SVariant &src)
{
	this->SetValue(src);
}

SVariant::~SVariant(void)
{
	FreeResource();
}

void SVariant::SetValue(SVariant &src)
{
	FreeResource();
	this->type = src.type;
	this->release_flag = false;
	this->value = src.value;
}

void SVariant::SetValue(const char * const pStr, bool release_flag)
{
	FreeResource();
	this->type = vtCSTR_PTR;
	this->release_flag = release_flag;
	if (this->release_flag)
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

