// DLL3.h - Contains declarations of math functions
#pragma once
#ifdef DLL3_EXPORTS
#define DLL3_API __declspec(dllexport)
#else
#define DLL3_API __declspec(dllimport)
#endif

#include <stdexcept>
#include <iostream>

#include "iTest.h"

extern "C" DLL3_API bool testDriver();