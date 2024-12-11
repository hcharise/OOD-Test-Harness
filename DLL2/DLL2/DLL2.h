// DLL2.h - Contains declarations of math functions
#pragma once
#ifdef DLL2_EXPORTS
#define DLL2_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" DLL2_API bool testDriver();