#include "stdafx.h"
#include "..\include\SerialStreamXml.h"
#include "..\include\ITreeSerial.h"
#include "..\include\ExceptionSerialization.h"
#include "..\include\ExceptionIDSerialization.h"
#include "..\..\include\CharArray.h"
#include "..\..\lib_h\expat.h"

#define D_SERIAL_ENTITY_XML_ELE_ATTR_TYPE_NAME		"type_name"
#define D_SERIAL_ENTITY_XML_ELE_ATTR_TAG			"tag"
#define D_SERIAL_ENTITY_XML_ELE_ATTR_VALUE_TYPE		"value_type"
#define D_SERIAL_ENTITY_XML_ELE_ATTR_VALUE			"value"

#define D_SERIAL_ENTITY_XML_BUFF_SIZE_DIFF			(256)

struct SSerialEntItemXml
{
	ISerialEntity *pEnt;
	int level;
};

struct SSpecialCharInfo
{
	unsigned int index;
	const char *pStr;
};

static const char gXmlEscapeChar[][7] = {
	"&lt;",
	"&gt;",
	"&amp;",
	"&apos;",
	"&quot;",
};

static void ParseSpecialChar(const char *pStr, SSpecialCharInfo **pSpecialCharInfo, unsigned int *pCount)
{
	if (!pStr || !pSpecialCharInfo) return;
	
	unsigned int i(0);
	unsigned int capacity(10);
	const char *pEscapeStr;
	char Char;
	SSpecialCharInfo *pSCI;

	*pSpecialCharInfo = new SSpecialCharInfo[capacity];
	*pCount = 0;
	while(pStr[i])
	{
		pEscapeStr = nullptr;
		Char = pStr[i];
		switch(Char)
		{
		case '<':
			pEscapeStr = gXmlEscapeChar[0];
			++(*pCount);
			break;
		case '>':
			pEscapeStr = gXmlEscapeChar[1];
			++(*pCount);
			break;
		case '&':
			pEscapeStr = gXmlEscapeChar[2];
			++(*pCount);
			break;
		case '\'':
			pEscapeStr = gXmlEscapeChar[3];
			++(*pCount);
			break;
		case '\"':
			pEscapeStr = gXmlEscapeChar[4];
			++(*pCount);
			break;
		default:
			break;
		}
		if (pEscapeStr)
		{
			if ((*pCount) > capacity)
			{
				pSCI = new SSpecialCharInfo[capacity * 2];
				memcpy(pSCI, *pSpecialCharInfo, sizeof(SSpecialCharInfo) * capacity);
				delete [] (*pSpecialCharInfo);
				*pSpecialCharInfo = pSCI;
				capacity *= 2;
			}
			(*pSpecialCharInfo)[(*pCount) - 1].index = i;
			(*pSpecialCharInfo)[(*pCount) - 1].pStr = pEscapeStr;
		}
		++i;
	}
}

void XMLCALL XmlElementStart(void *userData, const XML_Char *name, const XML_Char **atts)
{
	SSerialEntItemXml *pEntItem = reinterpret_cast<SSerialEntItemXml*>(userData);
	
	if (!pEntItem) return;

	int name_len(strlen(name));
	ISerialEntity *pEnt;
	EVarType var_type;
	bool bValueSet(false);
	const char *pValue(nullptr);
	unsigned int ValueStrLen(0);
	bool attr_comp[4] = { false, false, false, false };
	
	if (pEntItem->level > 0)
	{
		pEnt = pEntItem->pEnt->NewChild();
	}
	else
	{
		pEnt = pEntItem->pEnt;
	}
	pEnt->SetName(name);

	for (int i = 0; atts[i]; i += 2)
	{
		if (strcmp(atts[i], D_SERIAL_ENTITY_XML_ELE_ATTR_TYPE_NAME) == 0)
		{
			pEnt->SetEntTypeName(atts[i + 1]);
			attr_comp[0] = true;
		}
		else if (strcmp(atts[i], D_SERIAL_ENTITY_XML_ELE_ATTR_VALUE_TYPE) == 0)
		{
			var_type = static_cast<EVarType>(atoi(atts[i + 1]));
			attr_comp[1] = true;
		}
		else if (strcmp(atts[i], D_SERIAL_ENTITY_XML_ELE_ATTR_VALUE) == 0)
		{
			pValue = atts[i + 1];
			attr_comp[2] = true;
		}
		else if (strcmp(atts[i], D_SERIAL_ENTITY_XML_ELE_ATTR_TAG) == 0)
		{
			pEnt->SetTag(atoi(atts[i + 1]));
			attr_comp[3] = true;
		}

		if (attr_comp[1] && attr_comp[2] && (!bValueSet))
		{
			switch (var_type)
			{
			case vtBOOL:
				pEnt->SetValue(atoi(pValue) != 0);
				break;
			case vtINT:
				pEnt->SetValue(atoi(pValue));
				break;
			case vtFLOAT:
				pEnt->SetValue(static_cast<long double>(strtod(pValue, nullptr)));
				break;
			case vtLONGLONG:
				pEnt->SetValue(_strtoi64(pValue, nullptr, 10));
				break;
			case vtSTR_PTR:
				pEnt->SetValue(pValue);
				break;
			default:
				pEnt->GetValue().SetValueEmpty();
				break;
			}
			bValueSet = true;
		}

		if (attr_comp[0] && attr_comp[1] && attr_comp[2] && attr_comp[3])
			break;
	}
	pEntItem->pEnt = pEnt;
	++pEntItem->level;
}

void XMLCALL XmlElementEnd(void *userData, const XML_Char *name)
{
	SSerialEntItemXml *pEntItem = reinterpret_cast<SSerialEntItemXml*>(userData);
	if (!pEntItem) return;
	pEntItem->pEnt = pEntItem->pEnt->GetParent();
	--pEntItem->level;
}

//CSerialStreamXml
CSerialStreamXml::CSerialStreamXml(std::iostream *pStream, bool hold_stream)
	:m_pStream(pStream), m_HoldStream(hold_stream)
{
}


CSerialStreamXml::~CSerialStreamXml(void)
{
	if (m_HoldStream && m_pStream) delete m_pStream;
}

bool CSerialStreamXml::Serialize(ISerial *pSerial)
{
	if (!pSerial || !m_pStream) return false;

	CCharArray buffer(BUFSIZ);
	ITreeSerial *pTreeSerial(pSerial->AsType<ITreeSerial>());
	ISerialEntity *pEnt;

	if (!pTreeSerial) return false;
	pEnt = pTreeSerial->Root();
	if (!pEnt ) return false;

	m_pStream->seekp(0);
	(*m_pStream)<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	return DoSerialize(pEnt, buffer.char_array());
}

bool CSerialStreamXml::Unserialize(ISerial *pSerial)
{
	if (!pSerial || !m_pStream) return false;

	ITreeSerial *pTreeSerial(pSerial->AsType<ITreeSerial>());
	SSerialEntItemXml EntItemXml;

	if (!pTreeSerial) return false;
	EntItemXml.pEnt = pTreeSerial->Root();
	if (!EntItemXml.pEnt) return false;

	XML_Parser xml_parser;
	std::streamsize len;
	int done;
	CCharArray buffer(BUFSIZ);

	EntItemXml.level = 0;
	EntItemXml.pEnt->ClearChildren();
	xml_parser = XML_ParserCreate(nullptr);
	try
	{
		XML_SetUserData(xml_parser, &EntItemXml);
		XML_SetElementHandler(xml_parser, XmlElementStart, XmlElementEnd);
		m_pStream->seekg(0);
		do
		{
			m_pStream->read(buffer.char_array(), BUFSIZ);
			len = m_pStream->gcount();
			done = len < BUFSIZ;
			if (XML_Parse(xml_parser, buffer.char_array(), (int)len, done) == XML_STATUS_ERROR) {
				throw new ExceptionSerialization(D_E_ID_SERIAL_ERROR, "Xml·ÖÎö³ö´í£¡");
			}
		} while (!done);
	}
	catch (...)
	{
		XML_ParserFree(xml_parser);
		throw;
	}
	XML_ParserFree(xml_parser);
	
	return true;
}

bool CSerialStreamXml::DoSerialize(ISerialEntity *pEnt, char *pBuff)
{
	if (!pBuff || !pEnt->GetName()) return false;

	bool ret(false);
	int write_buff_len;
	int str_len;
	SSpecialCharInfo *pSCI;
	unsigned int Count;
	unsigned int i;
	unsigned int pre_index;
	unsigned int cpy_size;
	char *pLocalBuffer(nullptr), *pChildBuffer(pBuff);

	if (pEnt->GetChildrenCount() > 0)
	{
		switch(pEnt->GetValue().type)
		{
		case vtBOOL:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._b);
			break;
		case vtINT:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._i);
			break;
		case vtFLOAT:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%f\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._d);
			break;
		case vtLONGLONG:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%lld\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._ll);
			break;
		case vtSTR_PTR:
			str_len = strlen(pEnt->GetValue().value._pstr);
			if (str_len > BUFSIZ - D_SERIAL_ENTITY_XML_BUFF_SIZE_DIFF)
			{
				pBuff = pLocalBuffer = new char[str_len + D_SERIAL_ENTITY_XML_BUFF_SIZE_DIFF + 1];
			}
			ParseSpecialChar(pEnt->GetValue().value._pstr, &pSCI, &Count);
			try
			{
				if (Count == 0)
				{
					sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%s\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._pstr);
				}
				else
				{
					write_buff_len = sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
					pre_index = 0;
					for (i = 0; i < Count; ++i)
					{
						cpy_size = pSCI[i].index - pre_index;
						memcpy(pBuff + write_buff_len, pEnt->GetValue().value._pstr + pre_index, cpy_size);
						
						pre_index = pSCI[i].index + 1;
						write_buff_len += cpy_size;

						cpy_size = strlen(pSCI[i].pStr);
						memcpy(pBuff + write_buff_len, pSCI[i].pStr, cpy_size);
						write_buff_len += cpy_size;
					}
					cpy_size = strlen(pEnt->GetValue().value._pstr) - pre_index;
					memcpy(pBuff + write_buff_len, pEnt->GetValue().value._pstr + pre_index, cpy_size);
					write_buff_len += cpy_size;
					strcpy(pBuff + write_buff_len, "\">\n");
				}
			}
			catch(...)
			{
				delete [] pSCI;
				throw;
			}
			delete [] pSCI;
			break;
		default:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"0\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
			break;
		}
		(*m_pStream)<<pBuff;
		
		for (unsigned int i = 0; i < pEnt->GetChildrenCount(); ++i)
		{
			if (!DoSerialize(pEnt->GetChildren(i), pChildBuffer)) goto flag_return;
		}

		sprintf(pBuff, "</%s>\n", pEnt->GetName());
		(*m_pStream)<<pBuff;
	}
	else
	{
		switch(pEnt->GetValue().type)
		{
		case vtBOOL:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._b);
			break;
		case vtINT:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._i);
			break;
		case vtFLOAT:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%f\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._d);
			break;
		case vtLONGLONG:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%lld\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._ll);
			break;
		case vtSTR_PTR:
			str_len = strlen(pEnt->GetValue().value._pstr);
			if (str_len > BUFSIZ - D_SERIAL_ENTITY_XML_BUFF_SIZE_DIFF)
			{
				pBuff = pLocalBuffer = new char[str_len + D_SERIAL_ENTITY_XML_BUFF_SIZE_DIFF + 1];
			}
			ParseSpecialChar(pEnt->GetValue().value._pstr, &pSCI, &Count);
			try
			{
				if (Count == 0)
				{
					sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%s\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._pstr);
				}
				else
				{
					write_buff_len = sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
					pre_index = 0;
					for (i = 0; i < Count; ++i)
					{
						cpy_size = pSCI[i].index - pre_index;
						memcpy(pBuff + write_buff_len, pEnt->GetValue().value._pstr + pre_index, cpy_size);
						
						pre_index = pSCI[i].index + 1;
						write_buff_len += cpy_size;

						cpy_size = strlen(pSCI[i].pStr);
						memcpy(pBuff + write_buff_len, pSCI[i].pStr, cpy_size);
						write_buff_len += cpy_size;
					}
					cpy_size = strlen(pEnt->GetValue().value._pstr) - pre_index;
					memcpy(pBuff + write_buff_len, pEnt->GetValue().value._pstr + pre_index, cpy_size);
					write_buff_len += cpy_size;
					strcpy(pBuff + write_buff_len, "\"/>\n");
				}
			}
			catch(...)
			{
				delete [] pSCI;
				throw;
			}
			delete [] pSCI;
			break;
		default:
			sprintf(pBuff, "<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"0\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
			break;
		}
		(*m_pStream)<<pBuff;
	}
	ret = true;
	goto flag_return;

flag_return:
	if (pLocalBuffer)
	{
		delete [] pLocalBuffer;
	}
	return ret;
}