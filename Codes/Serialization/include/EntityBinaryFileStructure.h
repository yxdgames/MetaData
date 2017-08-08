#pragma once

//definition of atom type
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_NONE		(0x00000000)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_OBJECT		(0x00000001)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_STRING		(0x00000002)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_CUSTOM		(0x00000003)

#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_USER_BASE	(0x00010000)

//类型定义
typedef TDUIntPtr TypeBaseUnit;
typedef unsigned char TypeByte;

//容器
struct SAtom
{
	TypeBaseUnit type;
	TypeBaseUnit size;
};

//文件头
struct SFileHeader
{
	TypeByte file_tag[10];
	TypeByte version[4];
	char endian[4];
};

//对象描述项
struct SFileEntityItem
{
	TypeBaseUnit name_addr;
	TypeBaseUnit type_name_addr;
	TypeBaseUnit tag;
	TypeBaseUnit value_type;
	TypeBaseUnit value[3];
	TypeBaseUnit children_count;
};