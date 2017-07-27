#pragma once

//类实现IInterface接口宏
#define D_IMPLEMENT_IINTERFACE_MEMBER \
public: \
	virtual bool QueryInterface(char *pIntfName, IInterface **outIntf) \
	{ \
		return this->GetType()->QueryInterface(this->GetTrueSelf(), pIntfName, outIntf); \
	}
