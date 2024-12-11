// DLL2.h - Contains declarations of math functions
#pragma once
#ifdef DLL2_EXPORTS
#define DLL2_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

#include <stdexcept>
#include <iostream>

#include "iTest.h"

extern "C" DLL2_API bool testDriver();