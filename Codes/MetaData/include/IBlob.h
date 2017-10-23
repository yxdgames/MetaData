#pragma once

#include "IInterface.h"

//BLOB - Binary large object
class CLASS_DESCRIPT IBlob : public IInterface
{
public:
	IBlob(void) {}
	virtual ~IBlob(void) = 0 {}
public:
	virtual void BeginRead(void) = 0;
	virtual void EndRead(void) = 0;
	virtual size_t Read(void *pBuffer, size_t BufferSize) = 0;
	virtual void BeginWrite(void) = 0;
	virtual void EndWrite(void) = 0;
	virtual size_t Write(void *pBuffer, size_t BufferSize) = 0;
public:
	virtual IBlob &operator =(IBlob &src) = 0;

/*Meta Data Definition*/
MD_INTERFACE_DECLARE_BEGIN(IBlob)
MD_INTERFACE_DECLARE_DETAIL_KERNEL(IBlob)
	// { 90540308-F44F-4365-BCDA-2D635C4564C9 }
	MD_INTERFACE_GUID_DEF(0x90540308, 0xf44f, 0x4365, 0xbc, 0xda, 0x2d, 0x63, 0x5c, 0x45, 0x64, 0xc9)
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IBlob)
};
