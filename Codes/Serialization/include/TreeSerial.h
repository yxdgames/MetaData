#pragma once

#include "ITreeSerial.h"
#include "..\..\MetaData\include\IInterfaceDefaultImp.h"

class CTreeSerial : public ITreeSerial
{
public:
	CTreeSerial(void);
	virtual ~CTreeSerial(void);
public:
	//IInterface
	D_IMPLEMENT_IINTERFACE_MEMBER
	//ISerial
	//method
	virtual bool SaveToStream(std::iostream &stream);
	virtual bool LoadFromStream(std::iostream &stream);
	virtual bool SaveToFile(char *pFileName);
	virtual bool LoadFromFile(char *pFileName);
	virtual void DebugPrintSelf(void);
	//attribute
	virtual EStructureInStream GetStructInStream(void);
	virtual void SetStructInStream(EStructureInStream value);
	//ITreeSerial
	virtual ISerialEntity *Root(void);
private:
	void DoDebugPrintSelf(ISerialEntity *pEnt, unsigned int level);
private:
	ISerialEntity *m_pSerialEntiry;
	EStructureInStream m_StructInStream;

/*Meta Data Definition*/
MD_CLASS_TYPE_DECLARE_BEGIN(CTreeSerial)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CTreeSerial)
	MD_CLASS_TYPE_INTERFACE_DEF(ISerial)
	MD_CLASS_TYPE_INTERFACE_DEF(ITreeSerial)
MD_CLASS_TYPE_DECLARE_END(CTreeSerial)
};

