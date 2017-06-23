#pragma once

#include "IInterface.h"
#include "MetaDataClassType.h"

class CLASS_DESCRIPT CInterfacedObject : public IInterface
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
	MD_CLASS_TYPE_CONSTRUCTOR_WRAPPER_DECLARE(0)
MD_CLASS_TYPE_DECLARE_DETAIL_KERNEL(CInterfacedObject)
	MD_CLASS_TYPE_INTERFACE_DEF(IInterface)	
	MD_CLASS_TYPE_CONSTRUCTOR_DEF(0)
MD_CLASS_TYPE_DECLARE_END(CInterfacedObject)
};

//类实现IInterface接口宏
#define D_IMPLEMENT_IINTERFACE_MEMBER \
public: \
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf) \
	{ \
		return __DoQueryInterface(this, pIntfName, outIntf); \
	} \
private: \
	template<typename T> \
	bool __DoQueryInterface(T *pObj, char *pIntfName, IInterface **outIntf) \
	{ \
		CMetaDataClassType *pMDClassType(pObj->GetMetaData()); \
		if (pMDClassType) \
			return pMDClassType->QueryInterface(pObj, pIntfName, outIntf); \
		return false; \
	}