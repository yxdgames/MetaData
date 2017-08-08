#include "stdafx.h"
#include "..\include\SerialStreamBinary.h"
#include "..\include\ITreeSerial.h"

#define D_ENT_BIN_SERIALIZER_FILE_TAG	"OBBINSER\0"

#define D_ENT_BIN_SERIALIZER_ENDIAN_BIG		"EB\0\0"
#define D_ENT_BIN_SERIALIZER_ENDIAN_LITTLE	"EL\0\0"

#define D_CLASS_MEMBER_VARIABLE_OFFSET(cls, mem_var)	(reinterpret_cast<TDUIntPtr>(&(reinterpret_cast<cls*>(0)->mem_var)))

//CSerialStreamBinary::SStringFilePositionList
CSerialStreamBinary::SStringFilePositionList::SStringFilePositions *CSerialStreamBinary::SStringFilePositionList::FindItem(const char *pString, bool bNew)
{
	SStringFilePositions *pStringFilePos(nullptr);
	for (unsigned long i = 0; i < this->info_vector.size(); ++i)
	{
		if ((pString && info_vector.at(i).str && strcmp(info_vector.at(i).str, pString) == 0)
			|| (!pString && info_vector.at(i).str == pString))
		{
			pStringFilePos = &info_vector.at(i);
			break;
		}
	}
	if (!pStringFilePos && bNew)
	{
		SStringFilePositions value;
		value.str = pString;
		info_vector.push_back(value);
		pStringFilePos = &info_vector.back();
	}
	return pStringFilePos;
}

//CSerialStreamBinary
CSerialStreamBinary::CSerialStreamBinary(std::iostream *pStream, bool hold_stream)
	:m_HoldStream(hold_stream), m_pStream(pStream), m_StreamPosition(0)
{
}


CSerialStreamBinary::~CSerialStreamBinary(void)
{
	if (m_HoldStream && m_pStream) delete m_pStream;
}

bool CSerialStreamBinary::Serialize(ISerial *pSerial)
{
	if (!m_pStream || !pSerial) return false;

	ITreeSerial *pTreeSerial(pSerial->AsType<ITreeSerial>());
	ISerialEntity *pEnt;

	if (!pTreeSerial) return false;

	pEnt = pTreeSerial->Root();

	if (!pEnt) return false;

	SerialInit();

	SFileHeader file_header;
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_OBJECT, 0 };
	TypeBaseUnit atom_size_pos;

	memcpy(&file_header.file_tag, D_ENT_BIN_SERIALIZER_FILE_TAG, sizeof(file_header.file_tag));
	file_header.version[0] = (TypeByte)1;
	file_header.version[1] = (TypeByte)0;
	file_header.version[2] = (TypeByte)0;
	file_header.version[3] = (TypeByte)0;
	file_header.endian[0] = 'E';
	file_header.endian[1] = 'L';
	file_header.endian[2] = '\0';
	file_header.endian[3] = '\0';

	m_pStream->write((char*)&file_header, sizeof(file_header));
	m_StreamPosition += sizeof(file_header);
	atom_size_pos = m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SAtom, size);

	m_pStream->write((char*)&atom, sizeof(atom));
	m_StreamPosition += sizeof(atom);

	//持久化对象
	if (!SerializeEntity(pEnt, atom.size))
	{
		return false;
	}
	atom.size += sizeof(atom);
	m_pStream->seekp(atom_size_pos);
	m_pStream->write((char*)&atom.size, sizeof(atom.size));
	m_pStream->seekp(m_StreamPosition);

	//持久化字符串表
	if (!SerializeStringTable())
	{
		return false;
	}

	return true;
}

bool CSerialStreamBinary::Unserialize(ISerial *pSerial)
{
	if (!m_pStream || !pSerial) return false;

	SFileHeader file_header;
	TypeBaseUnit ent_size;
	ITreeSerial *pTreeSerial(pSerial->AsType<ITreeSerial>());
	ISerialEntity *pEnt;

	if (!pTreeSerial) return false;

	pEnt = pTreeSerial->Root();

	if (!pEnt) return false;

	UnserialInit();
	m_pStream->read((char*)&file_header, sizeof(file_header));
	m_StreamPosition += sizeof(file_header);

	if (memcmp(file_header.file_tag, D_ENT_BIN_SERIALIZER_FILE_TAG, sizeof(file_header.file_tag)) != 0)
	{
		return false;
	}
	if (file_header.version[0] != 1 || file_header.version[1] != 0 || file_header.version[2] != 0 || file_header.version[3] != 0)
	{
		return false;
	}
	if (memcmp(file_header.endian, D_ENT_BIN_SERIALIZER_ENDIAN_LITTLE, sizeof(file_header.endian)) != 0)
	{
		return false;
	}
	
	pEnt->ClearChildren();
	
	return UnserializeEntity(pEnt, ent_size);
}

void CSerialStreamBinary::SerialInit(void)
{
	if (m_pStream)
	{
		m_pStream->seekp(0);
	}
	m_StreamPosition = 0;
	m_StringFilePositionList.info_vector.clear();
}

bool CSerialStreamBinary::SerializeEntity(ISerialEntity *pEnt, TDUIntPtr &EntSize)
{
	SFileEntityItem file_ent_item;
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_OBJECT, 0 };
	TypeBaseUnit atom_size_pos;
	SStringFilePositionList::SStringFilePositions *pStringFilePos;

	pStringFilePos = this->m_StringFilePositionList.FindItem(pEnt->GetName(), true);
	pStringFilePos->positions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, name_addr));
	pStringFilePos = this->m_StringFilePositionList.FindItem(pEnt->GetEntTypeName(), true);
	pStringFilePos->positions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, type_name_addr));

	memset(&file_ent_item, 0x00, sizeof(file_ent_item));
	file_ent_item.tag = (unsigned long)pEnt->GetTag();
	file_ent_item.value_type = (unsigned long)pEnt->GetValue().type;
	memcpy(file_ent_item.value, &(pEnt->GetValue().value), sizeof(file_ent_item.value));
	file_ent_item.children_count = pEnt->GetChildrenCount();
	if (pEnt->GetValue().type == vtSTR_PTR)
	{
		pStringFilePos = this->m_StringFilePositionList.FindItem(pEnt->GetValue().value._pstr, true);
		pStringFilePos->positions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, value[0]));
	}

	m_pStream->write((char*)&file_ent_item, sizeof(file_ent_item));
	m_StreamPosition += sizeof(file_ent_item);
	EntSize = sizeof(file_ent_item);

	if (file_ent_item.children_count != 0)
	{
		for (unsigned long i = 0; i < file_ent_item.children_count; ++i)
		{
			atom_size_pos = m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SAtom, size);
			atom.size = 0;
			m_pStream->write((char*)&atom, sizeof(atom));
			m_StreamPosition += sizeof(atom);
			if (!this->SerializeEntity(pEnt->GetChildren(i), atom.size))
			{
				return false;
			}
			atom.size += sizeof(atom);
			EntSize += atom.size;
			m_pStream->seekp(atom_size_pos);
			m_pStream->write((char*)&atom.size, sizeof(atom.size));
			m_pStream->seekp(m_StreamPosition);
		}
	}

	return true;
}

bool CSerialStreamBinary::SerializeStringTable(void)
{
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_STRING, 0 };
	TypeBaseUnit atom_size_pos;
	TDUIntPtr size;
	unsigned long i, j;

	atom_size_pos = m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SAtom, size);
	m_pStream->write((char*)&atom, sizeof(atom));
	m_StreamPosition += sizeof(atom);

	for (i = 0; i < m_StringFilePositionList.info_vector.size(); ++i)
	{
		for (j = 0; j < m_StringFilePositionList.info_vector.at(i).positions.size(); ++j)
		{
			m_pStream->seekp(m_StringFilePositionList.info_vector.at(i).positions.at(j));
			m_pStream->write((char*)&m_StreamPosition, sizeof(m_StreamPosition));
		}
		m_pStream->seekp(m_StreamPosition);

		if (m_StringFilePositionList.info_vector.at(i).str)
		{
			size = strlen(m_StringFilePositionList.info_vector.at(i).str);
			m_pStream->write((char*)&size, sizeof(size));
			m_pStream->write(m_StringFilePositionList.info_vector.at(i).str, size);
		}
		else
		{
			size = 1;
			m_pStream->write((char*)&size, sizeof(size));
			m_pStream->write("\0", size);
		}
		m_StreamPosition += size + sizeof(size);
		atom.size += size + sizeof(size);
	}

	atom.size += sizeof(atom);
	m_pStream->seekp(atom_size_pos);
	m_pStream->write((char*)&atom.size, sizeof(atom.size));
	m_pStream->seekp(m_StreamPosition);

	return true;
}

void CSerialStreamBinary::UnserialInit(void)
{
	if (m_pStream)
	{
		m_pStream->seekg(0);
	}
	m_StreamPosition = 0;
}

bool CSerialStreamBinary::UnserializeEntity(ISerialEntity *pEnt, TDUIntPtr &EntSize)
{
	SAtom atom;
	TypeBaseUnit child_ent_size;
	SFileEntityItem ent_item;
	TypeBaseUnit str_size1, str_size2;
	char *pStr;

	EntSize = 0;

	m_pStream->read((char*)&atom, sizeof(atom));
	m_StreamPosition += sizeof(atom);
	EntSize += sizeof(atom);

	if (atom.type == D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_OBJECT)
	{
		m_pStream->read((char*)&ent_item, sizeof(ent_item));
		m_StreamPosition += sizeof(ent_item);
		EntSize += sizeof(ent_item);

		//name
		m_pStream->seekg(ent_item.name_addr);
		m_pStream->read((char*)&str_size1, sizeof(str_size1));
		pStr = new char [str_size1 + 1];
		m_pStream->read(pStr, str_size1);
		pStr[str_size1] = '\0';
		pEnt->SetName(pStr);

		//type name
		m_pStream->seekg(ent_item.type_name_addr);
		m_pStream->read((char*)&str_size2, sizeof(str_size2));
		if (str_size2 > str_size1)
		{
			delete [] pStr;
			pStr = new char [str_size2 + 1];
		}
		m_pStream->read(pStr, str_size2);
		pStr[str_size2] = '\0';
		pEnt->SetEntTypeName(pStr);

		//tag
		pEnt->SetTag(ent_item.tag);

		//value
		switch(ent_item.value_type)
		{
		case vtBOOL:
			pEnt->SetValue(*((bool*)ent_item.value));
			break;
		case vtINT:
			pEnt->SetValue(*((int*)ent_item.value));
			break;
		case vtFLOAT:
			pEnt->SetValue(*((long double*)ent_item.value));
			break;
		case vtLONGLONG:
			pEnt->SetValue(*((long long*)ent_item.value));
			break;
		case vtSTR_PTR:
			m_pStream->seekg(*((TypeBaseUnit*)ent_item.value));
			m_pStream->read((char*)&str_size1, sizeof(str_size1));
			if (str_size1 > str_size2)
			{
				delete [] pStr;
				pStr = new char [str_size1 + 1];
			}
			m_pStream->read(pStr, str_size1);
			pStr[str_size1] = '\0';
			pEnt->SetValue(pStr);
			break;
		case vtNone:
		default:
			break;
		}
		delete [] pStr;

		m_pStream->seekg(m_StreamPosition);

		//children
		for (TypeBaseUnit i = 0; i < ent_item.children_count; ++i)
		{
			if (!UnserializeEntity(pEnt->NewChild(), child_ent_size))
			{
				return false;
			}
			EntSize += child_ent_size;
		}
	}

	return EntSize == atom.size;
}