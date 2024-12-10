// DLL1.h

#pragma once
#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)

#else
#define DLL1_API __declspec(dllimport)
#endif

extern "C" DLL1_API double Add(double a, double b);
extern "C" DLL1_API double Multiply(double a, double b);
extern "C" DLL1_API double AddMultiply(double a, double b);