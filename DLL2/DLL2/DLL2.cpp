// DLL2.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "framework.h"
#include "DLL2.h"
DLL2_API double Add(double a, double b) { return a + b; }
DLL2_API double Multiply(double a, double b) { return a * b; }
DLL2_API double AddMultiply(double a, double b) { return a + (a * b); }
DLL2_API bool testDriver() { return TRUE; }