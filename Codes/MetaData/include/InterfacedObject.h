#pragma once

#include "IInterface.h"
#include "MetaDataClassType.h"

class CInterfacedObject : public IInterface
{
public:
	CInterfacedObject(void);
	virtual ~CInterfacedObject(void);
public:
	//IInterface
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf);
protected:
	template<typename T>
	bool DoQueryInterface(T *pObj, char *pIntfName, IInterface **outIntf)
	{
		CMetaDataClassType *pMDClassType(pObj->GetMetaData());
		if (pMDClassType)
			return pMDClassType->QueryInterface(pObj, pIntfName, outIntf);
		return false;
	}

/*Meta Data Definition*/
MD_CLASS_TYPE_DECLARE_BEGIN(CInterfacedObject)
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(CInterfacedObject, 0)
MD_CLASS_TYPE_DECLARE_DETAIL(CInterfacedObject)
	MD_CLASS_TYPE_CONSTRUCTOR_DEF(CInterfacedObject, 0)
	MD_CLASS_TYPE_INTERFACE_DEF(CInterfacedObject, IInterface)
MD_CLASS_TYPE_DECLARE_END(CInterfacedObject)
};

