#include "stdafx.h"
#include "..\include\TreeSerial.h"
#include "..\include\ISerialStream.h"
#include <fstream>

static const ESerialStreamIntfType gTreeSerialSerialStreamIntfType[ssiMax] = {
	ssitNone,
	ssitBin,
	ssitXml
};

static ISerialEntity *NewSerialEntiry(void)
{
	ISerialEntity *pEnt(ISerialEntity::CreateSerialEntityIntf());
	pEnt->SetName("SerialEntityRoot");
	return pEnt;
}

static ISerialStream *NewSerialStream(ESerialStreamIntfType IntfType, std::iostream *pStream, bool hold_stream)
{
	return ISerialStream::CreateSerialStreamIntf(IntfType, pStream, hold_stream);
}

//CTreeSerial
CTreeSerial::CTreeSerial(void)
	:m_pSerialEntiry(NewSerialEntiry()), m_StructInStream(sisNone),
	m_pBlobCreater(nullptr)
{
}


CTreeSerial::~CTreeSerial(void)
{
	if (m_pSerialEntiry) delete m_pSerialEntiry;
}

bool CTreeSerial::SaveToStream(std::iostream &stream)
{
	bool ret;
	ISerialStream *pSerialStream(NewSerialStream(gTreeSerialSerialStreamIntfType[m_StructInStream], &stream, false));
	if (!pSerialStream) return false;
	try
	{
		ret = pSerialStream->Serialize(this);
	}
	catch (...)
	{
		delete pSerialStream;
		throw;
	}
	delete pSerialStream;
	return ret;
}

bool CTreeSerial::LoadFromStream(std::iostream &stream)
{
	bool ret;
	ISerialStream *pSerialStream(NewSerialStream(gTreeSerialSerialStreamIntfType[m_StructInStream], &stream, false));
	if (!pSerialStream) return false;
	try
	{
		ret = pSerialStream->Unserialize(this);
	}
	catch (...)
	{
		delete pSerialStream;
		throw;
	}
	delete pSerialStream;
	return ret;
}

bool CTreeSerial::SaveToFile(const char *pFileName)
{
	bool ret;
	std::fstream file_stream(pFileName, std::fstream::out | std::fstream::binary);
	ISerialStream *pSerialStream(NewSerialStream(gTreeSerialSerialStreamIntfType[m_StructInStream], &file_stream, false));
	if (!pSerialStream) return false;
	try
	{
		ret = pSerialStream->Serialize(this);
	}
	catch (...)
	{
		delete pSerialStream;
		throw;
	}
	delete pSerialStream;
	file_stream.close();
	return ret;
}

bool CTreeSerial::LoadFromFile(const char *pFileName)
{
	bool ret;
	std::fstream file_stream(pFileName, std::fstream::in | std::fstream::binary);
	if (!file_stream.is_open()) return false;
	ISerialStream *pSerialStream(NewSerialStream(gTreeSerialSerialStreamIntfType[m_StructInStream], &file_stream, false));
	if (!pSerialStream) return false;
	try
	{
		ret = pSerialStream->Unserialize(this);
	}
	catch (...)
	{
		delete pSerialStream;
		throw;
	}
	delete pSerialStream;
	file_stream.close();
	return ret;
}

void CTreeSerial::Clear(void)
{
	this->Root()->ClearChildren();
}

void CTreeSerial::DebugPrintSelf(void)
{
	DoDebugPrintSelf(this->Root(), 0);
}

EStructureInStream CTreeSerial::GetStructInStream(void)
{
	return m_StructInStream;
}

void CTreeSerial::SetStructInStream(EStructureInStream value)
{
	m_StructInStream = value;
}

ISerialEntity *CTreeSerial::Root(void)
{
	return m_pSerialEntiry;
}

void CTreeSerial::DoDebugPrintSelf(ISerialEntity *pEnt, unsigned int level)
{
	if (!pEnt) return;
	unsigned int i;
	if (pEnt->GetChildrenCount() > 0)
	{
		for (i = 0; i < level; ++i)
		{
			//printf("\t");
			printf("  ");
		}
		switch(pEnt->GetValue().type)
		{
#ifdef CO_PLATFORM_WIN_X64
		case vtBOOL:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%d\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._b);
			break;
		case vtINT:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%d\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._i);
			break;
		case vtFLOAT:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%f\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._d);
			break;
		case vtLONGLONG:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%lld\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._ll);
			break;
		case vtCSTR_PTR:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%s\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._pcstr);
			break;
		default:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
			break;
#else
		case vtBOOL:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._b);
			break;
		case vtINT:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._i);
			break;
		case vtFLOAT:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%f\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._d);
			break;
		case vtLONGLONG:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%lld\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._ll);
			break;
		case vtCSTR_PTR:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%s\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._pcstr);
			break;
		default:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"\">\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
			break;
#endif
		}

		for (i = 0; i < pEnt->GetChildrenCount(); ++i)
		{
			DoDebugPrintSelf(pEnt->GetChildren(i), level + 1);
		}

		for (i = 0; i < level; ++i)
		{
			//printf("\t");
			printf("  ");
		}
		printf("</%s>\n", pEnt->GetName());
	}
	else
	{
		for (i = 0; i < level; ++i)
		{
			//printf("\t");
			printf("  ");
		}
		switch(pEnt->GetValue().type)
		{
#ifdef CO_PLATFORM_WIN_X64
		case vtBOOL:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%d\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._b);
			break;
		case vtINT:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%d\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._i);
			break;
		case vtFLOAT:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%f\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._d);
			break;
		case vtLONGLONG:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%lld\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._ll);
			break;
		case vtCSTR_PTR:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"%s\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._pcstr);
			break;
		default:
			printf("<%s type_name=\"%s\" tag=\"%lld\" value_type=\"%d\" value=\"\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
			break;
#else
		case vtBOOL:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._b);
			break;
		case vtINT:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%d\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._i);
			break;
		case vtFLOAT:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%f\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._d);
			break;
		case vtLONGLONG:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%lld\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._ll);
			break;
		case vtCSTR_PTR:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"%s\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type, pEnt->GetValue().value._pcstr);
			break;
		default:
			printf("<%s type_name=\"%s\" tag=\"%d\" value_type=\"%d\" value=\"\"/>\n", pEnt->GetName(), pEnt->GetEntTypeName(), pEnt->GetTag(), pEnt->GetValue().type);
			break;
#endif
		}
	}
}

void * CTreeSerial::AsTypeEx(void * pObj, const SAsTypeExTypeParam &AsTypeExParam)
{
	CTreeSerial *pTreeSerial(reinterpret_cast<CTreeSerial*>(pObj));
	switch (AsTypeExParam.ParamKind)
	{
	case SAsTypeExTypeParam::EParamKind::pkMDType:
		if (TypeTraits<IBlobCreater>::GetMetaDataType()->Compare(AsTypeExParam.Param.pType))
			return pTreeSerial->m_pBlobCreater;
		break;
	case SAsTypeExTypeParam::EParamKind::pkTypeGUID:
		if (TypeTraits<IBlobCreater>::GetMetaDataType()->Compare(AsTypeExParam.Param.ptype_guid))
			return pTreeSerial->m_pBlobCreater;
		break;
	case SAsTypeExTypeParam::EParamKind::pkTypeFullNameStr:
		if (TypeTraits<IBlobCreater>::GetMetaDataType()->Compare(AsTypeExParam.Param.pTypeFullName))
			return pTreeSerial->m_pBlobCreater;
		break;
	default:
		break;
	}
	
	return nullptr;
}
