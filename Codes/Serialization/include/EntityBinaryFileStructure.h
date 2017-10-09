#pragma once

//definition of atom type
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_NONE		(0x00000000)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_ENTITY		(0x00000001)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_STRING		(0x00000002)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_BINARY		(0x00000003)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_CUSTOM		(0x00000004)

#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_USER_BASE	(0x00010000)

//文件头
struct SFileHeader
{
	TDByte file_tag[10];
	TDByte version[4];
	char endian[4];
};

//类型定义
typedef TDUIntPtr TDBinBaseUnit;

//容器
struct SAtom
{
	TDBinBaseUnit type;
	TDBinBaseUnit size;
};

//对象描述项
struct SFileEntityItem
{
	TDBinBaseUnit name_addr;
	TDBinBaseUnit type_name_addr;
	TDBinBaseUnit tag;
	TDBinBaseUnit value_type;
	TDBinBaseUnit value[3];
	TDBinBaseUnit children_count;
};