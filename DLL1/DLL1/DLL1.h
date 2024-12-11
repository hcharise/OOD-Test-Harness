// DLL1.h - Contains declarations of math functions
#pragma once
#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

#include <stdexcept>
#include <iostream>

#include "iTest.h"

extern "C" DLL1_API bool testDriver();