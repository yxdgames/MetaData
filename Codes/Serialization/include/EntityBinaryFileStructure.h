#pragma once

//definition of atom type
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_NONE		(0x00000000)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_OBJECT		(0x00000001)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_STRING		(0x00000002)
#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_CUSTOM		(0x00000003)

#define D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_USER_BASE	(0x00010000)

//�ļ�ͷ
struct SFileHeader
{
	TDBYTE file_tag[10];
	TDBYTE version[4];
	char endian[4];
};

//���Ͷ���
typedef TDUIntPtr TDBinBaseUnit;

//����
struct SAtom
{
	TDBinBaseUnit type;
	TDBinBaseUnit size;
};

//����������
struct SFileEntityItem
{
	TDBinBaseUnit name_addr;
	TDBinBaseUnit type_name_addr;
	TDBinBaseUnit tag;
	TDBinBaseUnit value_type;
	TDBinBaseUnit value[3];
	TDBinBaseUnit children_count;
};