// DLL2.h - Contains declarations of math functions
#pragma once
#ifdef DLL2_EXPORTS
#define DLL2_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
extern "C" DLL2_API double Add(double a, double b);
extern "C" DLL2_API double Multiply(double a, double b);
extern "C" DLL2_API double AddMultiply(double a, double b);
extern "C" DLL2_API bool testDriver();