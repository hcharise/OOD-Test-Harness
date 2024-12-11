// DLL4.h - Contains declarations of math functions
#pragma once
#ifdef DLL4_EXPORTS
#define DLL4_API __declspec(dllexport)
#else
#define DLL4_API __declspec(dllimport)
#endif

#include <stdexcept>
#include <iostream>

#include "iTest.h"

extern "C" DLL4_API bool testDriver();