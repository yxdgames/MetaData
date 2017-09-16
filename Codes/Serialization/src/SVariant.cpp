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

void SVariant::SetValue(const char *pStr)
{
	FreeStr();
	type = vtSTR_PTR;
	if (release_string)
	{
		if (pStr)
		{
			value._pstr = new char [strlen(pStr) + 1];
			strcpy(value._pstr, pStr);
		}
		else value._pstr = nullptr;
	}
	else
	{
		value._pstr = const_cast<char*>(pStr);
	}
}

SVariant &SVariant::operator=(SVariant &src)
{
	FreeStr();
	this->type = src.type;
	this->release_string = src.release_string;
	if (this->type != vtSTR_PTR || !(this->release_string))
	{
		this->value = src.value;
	}
	else
	{
		if (src.value._pstr)
		{
			value._pstr = new char [strlen(src.value._pstr) + 1];
			strcpy(value._pstr, src.value._pstr);
		}
		else
		{
			value._pstr = nullptr;
		}
	}
	return *this;
}

void SVariant::SetReleaseStringFlag(bool flag)
{
	FreeStr();
	release_string = flag;
}

void SVariant::FreeStr(void)
{
	if (type == vtSTR_PTR && value._pstr && release_string)
	{
		delete [] value._pstr;
		value._pstr = nullptr;
	}
}
