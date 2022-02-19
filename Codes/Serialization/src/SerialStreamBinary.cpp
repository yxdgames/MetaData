#include "stdafx.h"
#include "../include/SerialStreamBinary.h"
#include "../include/ITreeSerial.h"
#include "../include/IBlobCreater.h"
#include "../include/ExceptionSerialization.h"
#include "../include/ExceptionIDSerialization.h"
#include "../../include/TArray.h"

#define D_ENT_BIN_SERIALIZER_FILE_TAG	"OBBINSER\0"

#define D_ENT_BIN_SERIALIZER_ENDIAN_BIG		"EB\0\0"
#define D_ENT_BIN_SERIALIZER_ENDIAN_LITTLE	"EL\0\0"

#define D_CLASS_MEMBER_VARIABLE_OFFSET(cls, mem_var)	(reinterpret_cast<TDUIntPtr>(&(reinterpret_cast<cls*>(0)->mem_var)))

#define D_BLOB_BUFFER_SIZE_MAX		(10 * 1024 * 1024) //10M

//CSerialStreamBinary::SStringFilePositionList
inline CSerialStreamBinary::SStringFilePositionList::SStringFilePositions *CSerialStreamBinary::SStringFilePositionList::FindItem(const char *pString, bool bNew)
{
	SStringFilePositions *pStringFilePos(nullptr);
	for (size_t i = 0; i < this->info_vector.size(); ++i)
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

inline CSerialStreamBinary::SBlobFilePositionList::SBlobFilePosition *CSerialStreamBinary::SBlobFilePositionList::FindItem(IBlob *pBlob, bool bNew)
{
	SBlobFilePosition *pBlobFilePosition(nullptr);
	for (size_t i = 0; i < this->info_vector.size(); ++i)
	{
		if (pBlob && pBlob == this->info_vector.at(i).pBlob)
		{
			pBlobFilePosition = &info_vector.at(i);
			break;
		}
	}
	if (!pBlobFilePosition && bNew)
	{
		SBlobFilePosition value;
		value.pBlob = pBlob;
		info_vector.push_back(value);
		pBlobFilePosition = &info_vector.back();
	}
	return pBlobFilePosition;
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
	if (!pTreeSerial) return false;

	ISerialEntity *pEnt(pTreeSerial->Root());
	if (!pEnt) return false;

	SerialInit();

	SFileHeader file_header;
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_ENTITY, 0 };
	TDBinBaseUnit atom_size_pos;

	memcpy(&file_header.file_tag, D_ENT_BIN_SERIALIZER_FILE_TAG, sizeof(file_header.file_tag));
	file_header.version[0] = (TDByte)1;
	file_header.version[1] = (TDByte)0;
	file_header.version[2] = (TDByte)0;
	file_header.version[3] = (TDByte)0;
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
	atom.size = SerializeEntity(pEnt);
	atom.size += sizeof(atom);
	m_pStream->seekp(atom_size_pos);
	m_pStream->write((char*)&atom.size, sizeof(atom.size));
	m_pStream->seekp(m_StreamPosition);

	//持久化字符串表
	if (!SerializeStringTable())
	{
		return false;
	}
	//持久化Blob
	if (!SerializeBlob())
	{
		return false;
	}

	return true;
}

bool CSerialStreamBinary::Unserialize(ISerial *pSerial)
{
	if (!m_pStream || !pSerial) return false;

	ITreeSerial *pTreeSerial(pSerial->AsType<ITreeSerial>());
	if (!pTreeSerial) return false;

	ISerialEntity *pEnt(pTreeSerial->Root());
	if (!pEnt) return false;

	UnserialInit();
	pEnt->ClearChildren();

	SFileHeader file_header;
	SAtom atom;

	memset(&file_header, 0x00, sizeof(file_header));
	m_pStream->read((char*)&file_header, sizeof(file_header));
	m_StreamPosition += sizeof(file_header);

	if (memcmp(file_header.file_tag, D_ENT_BIN_SERIALIZER_FILE_TAG, sizeof(file_header.file_tag)) != 0)
		return false;
	if (file_header.version[0] != 1 || file_header.version[1] != 0 || file_header.version[2] != 0 || file_header.version[3] != 0)
		return false;
	if (memcmp(file_header.endian, D_ENT_BIN_SERIALIZER_ENDIAN_LITTLE, sizeof(file_header.endian)) != 0)
		return false;
	
	memset(&atom, 0x00, sizeof(atom));
	m_pStream->read((char*)&atom, sizeof(atom));
	m_StreamPosition += sizeof(atom);

	if (atom.type == D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_ENTITY)
		return UnserializeEntity(pEnt, pSerial) + sizeof(atom) == atom.size;
	else return false;
}

void CSerialStreamBinary::SerialInit(void)
{
	if (m_pStream)
	{
		m_pStream->seekp(0);
	}
	m_StreamPosition = 0;
	m_StringFilePositionList.info_vector.clear();
	m_BlobFilePositionList.info_vector.clear();
}

size_t CSerialStreamBinary::SerializeEntity(ISerialEntity *pEnt)
{
	size_t ent_size;
	SFileEntityItem file_ent_item;
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_ENTITY, 0 };
	TDBinBaseUnit atom_size_pos;
	SStringFilePositionList::SStringFilePositions *pStringFilePos;
	SBlobFilePositionList::SBlobFilePosition *pBlobFilePos;

	pStringFilePos = this->m_StringFilePositionList.FindItem(pEnt->GetName(), true);
	pStringFilePos->positions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, name_addr));
	pStringFilePos = this->m_StringFilePositionList.FindItem(pEnt->GetEntTypeName(), true);
	pStringFilePos->positions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, type_name_addr));

	memset(&file_ent_item, 0x00, sizeof(file_ent_item));
	file_ent_item.tag = static_cast<TDBinBaseUnit>(pEnt->GetTag());
	file_ent_item.value_type = static_cast<TDBinBaseUnit>(pEnt->GetValue().type);
	memcpy(file_ent_item.value, &(pEnt->GetValue().value), sizeof(file_ent_item.value));
	file_ent_item.children_count = pEnt->GetChildrenCount();
	if (pEnt->GetValue().type == vtCSTR_PTR)
	{
		pStringFilePos = this->m_StringFilePositionList.FindItem(pEnt->GetValue().value._pcstr, true);
		pStringFilePos->positions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, value[0]));
	}
	else if (pEnt->GetValue().type == vtIntfBlob)
	{
		if (pEnt->GetValue().value._pblob)
		{
			pBlobFilePos = this->m_BlobFilePositionList.FindItem(pEnt->GetValue().value._pblob, true);
			pBlobFilePos->posistions.push_back(m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SFileEntityItem, value[0]));
		}
	}

	m_pStream->write((char*)&file_ent_item, sizeof(file_ent_item));
	m_StreamPosition += sizeof(file_ent_item);
	ent_size = sizeof(file_ent_item);

	for (unsigned long i = 0; i < file_ent_item.children_count; ++i)
	{
		atom_size_pos = m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SAtom, size);

		m_pStream->write((char*)&atom, sizeof(atom));
		m_StreamPosition += sizeof(atom);

		atom.size = this->SerializeEntity(pEnt->GetChildren(i));
		atom.size += sizeof(atom);
		ent_size += atom.size;

		m_pStream->seekp(atom_size_pos);
		m_pStream->write((char*)&atom.size, sizeof(atom.size));
		m_pStream->seekp(m_StreamPosition);
	}

	return ent_size;
}

bool CSerialStreamBinary::SerializeStringTable(void)
{
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_STRING, 0 };
	TDBinBaseUnit atom_size_pos;
	size_t size;
	size_t i, j;

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

bool CSerialStreamBinary::SerializeBlob(void)
{
	SAtom atom = { D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_BINARY, 0 };
	TDBinBaseUnit atom_size_pos;
	size_t read_size;
	TDByteArray Buffer(D_BLOB_BUFFER_SIZE_MAX);
	
	for (size_t i = 0; i < m_BlobFilePositionList.info_vector.size(); ++i)
	{
		for (size_t j = 0; j < m_BlobFilePositionList.info_vector.at(i).posistions.size(); ++j)
		{
			m_pStream->seekp(m_BlobFilePositionList.info_vector.at(i).posistions.at(j));
			m_pStream->write((char*)&m_StreamPosition, sizeof(m_StreamPosition));
		}
		m_pStream->seekp(m_StreamPosition);

		atom_size_pos = m_StreamPosition + D_CLASS_MEMBER_VARIABLE_OFFSET(SAtom, size);
		m_pStream->write((char*)&atom, sizeof(atom));
		m_StreamPosition += sizeof(atom);

		m_BlobFilePositionList.info_vector.at(i).pBlob->BeginRead();
		try
		{
			atom.size = sizeof(atom);
			while (true)
			{
				read_size = m_BlobFilePositionList.info_vector.at(i).pBlob->Read(Buffer.array(), Buffer.array_size());
				if (read_size)
				{
					m_pStream->write((char*)Buffer.array(), read_size);
					m_StreamPosition += read_size;
					atom.size += read_size;
				}
				else break;
			}
			m_pStream->seekp(atom_size_pos);
			m_pStream->write((char*)&atom.size, sizeof(atom.size));
			m_pStream->seekp(m_StreamPosition);
		}
		catch (...)
		{
			m_BlobFilePositionList.info_vector.at(i).pBlob->EndRead();
			throw;
		}
		m_BlobFilePositionList.info_vector.at(i).pBlob->EndRead();
	}

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

size_t CSerialStreamBinary::UnserializeEntity(ISerialEntity *pEnt, ISerial *pSerial)
{
	size_t ent_size;
	SFileEntityItem ent_item;
	SAtom atom;
	TDBinBaseUnit size;
	TDCharArray char_array(0);
	
	m_pStream->read((char*)&ent_item, sizeof(ent_item));
	m_StreamPosition += sizeof(ent_item);
	ent_size = sizeof(ent_item);

	//name
	m_pStream->seekg(ent_item.name_addr);
	m_pStream->read((char*)&size, sizeof(size));
	char_array.Reset(size + 1);
	m_pStream->read(char_array.array(), size);
	char_array[size] = '\0';
	pEnt->SetName(char_array.array());

	//type name
	m_pStream->seekg(ent_item.type_name_addr);
	m_pStream->read((char*)&size, sizeof(size));
	char_array.Reset(size + 1, true);
	m_pStream->read(char_array.array(), size);
	char_array[size] = '\0';
	pEnt->SetEntTypeName(char_array.array());

	//tag
	pEnt->SetTag(ent_item.tag);

	//value
	switch (ent_item.value_type)
	{
	case vtBOOL:
		pEnt->SetValue(*reinterpret_cast<bool*>(ent_item.value));
		break;
	case vtINT:
		pEnt->SetValue(*reinterpret_cast<int*>(ent_item.value));
		break;
	case vtLONGLONG:
		pEnt->SetValue(*reinterpret_cast<long long*>(ent_item.value));
		break;
	case vtFLOAT:
		pEnt->SetValue(*reinterpret_cast<double*>(ent_item.value));
		break;
	case vtLONGFLOAT:
		pEnt->SetValue(*reinterpret_cast<long double*>(ent_item.value));
		break;
	case vtCSTR_PTR:
		m_pStream->seekg(*reinterpret_cast<TDBinBaseUnit*>(ent_item.value));
		m_pStream->read((char*)&size, sizeof(size));
		char_array.Reset(size + 1, true);
		m_pStream->read(char_array.array(), size);
		char_array[size] = '\0';
		pEnt->SetValue(char_array.array());
		break;
	case vtIntfBlob:
		{
			IBlobCreater *pBlobCreater(pSerial->AsType<IBlobCreater>());
			IBlob *pBlob(nullptr);
			if (pBlobCreater)
			{
				size_t read_size;
				TDByteArray Buffer(D_BLOB_BUFFER_SIZE_MAX);
				pBlob = pBlobCreater->CreateBlob();
				if (!pBlob) throw ExceptionSerialization(D_E_ID_SERIAL_ERROR, "错误：IBlob接口创建失败！", true);
				m_pStream->seekg(*reinterpret_cast<TDBinBaseUnit*>(ent_item.value));
				m_pStream->read((char*)&atom, sizeof(atom));
				atom.size -= sizeof(atom);
				pBlob->BeginWrite();
				try
				{
					do {
						read_size = atom.size > Buffer.array_size() ? Buffer.array_size() : atom.size;
						m_pStream->read((char*)Buffer.array(), read_size);
						pBlob->Write(Buffer.array(), read_size);
						atom.size -= read_size;
					} while (atom.size > 0);
				}
				catch (...)
				{
					pBlob->EndWrite();
					throw;
				}
				pBlob->EndWrite();
			}
			pEnt->SetValue(pBlob, true);
		}
		break;
	case vtNone:
	default:
		break;
	}

	m_pStream->seekg(m_StreamPosition);

	//children
	for (TDBinBaseUnit i = 0; i < ent_item.children_count; ++i)
	{
		memset(&atom, 0x00, sizeof(atom));
		m_pStream->read((char*)&atom, sizeof(atom));
		if (atom.type == D_ENT_BIN_FILE_STRUCT_ATOM_TYPE_ENTITY)
		{
			m_StreamPosition += sizeof(atom);
			if (UnserializeEntity(pEnt->NewChild(), pSerial) + sizeof(atom) == atom.size)
				ent_size += atom.size;
			else return 0;
		}
		else
		{
			m_StreamPosition += atom.size;
			m_pStream->seekg(m_StreamPosition);
		}
	}

	return ent_size;
}