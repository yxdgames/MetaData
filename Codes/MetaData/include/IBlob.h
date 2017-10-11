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
	MD_INTERFACE_INTERFACE_DEF(IInterface)
MD_INTERFACE_DECLARE_END(IBlob)
};
