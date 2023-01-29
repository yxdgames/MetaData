#pragma once
#include <assert.h>

#ifndef _MD_ASSERT_
#ifdef _DEBUG
#define _MD_ASSERT_(expr)      assert(expr)
#else
#define _MD_ASSERT_(expr)
#endif //_DEBUG
#endif //_MD_ASSERT_