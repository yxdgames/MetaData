#include "stdafx.h"
#include "Test.h"

CTest CTest::Intance;

CTest::CTest(void)
{
	if (TypeTraits<int>::GetMetaDataType())
		printf("MetaData of int is OK.\n");
}
