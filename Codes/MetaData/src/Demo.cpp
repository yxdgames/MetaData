#include "stdafx.h"
#include "..\include\Demo.h"

#ifdef __META_DATA_DEMO__
////////////////////////////////////////////////
//                  Demo                      //
////////////////////////////////////////////////
/*.cpp part*/
double FuncDemo(double x, int y)
{
	return x + y;
}

double NTest::CClsInNS1::CClsInCL2::static_var = 11.203;

NTest::CClsInNS1 GetNone(int ax, double bx)
{
	NTest::CClsInNS1 ret;
	ret.uab.ax = ax;
	ret.uab.bx = bx;
	return ret;
}

#endif //__META_DATA_DEMO__