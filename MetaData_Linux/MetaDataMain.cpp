#include "../Codes/MetaData/include/MetaDataObjects.h"

extern "C" __attribute__((visibility("default"))) const void * __stdcall GetMetaDataGlobalSpace(void)
{
	return _MD__GLOBALSPACE__GetMetaData();
}