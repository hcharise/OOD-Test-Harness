// DLL1.cpp : Defines the exported functions for the DLL.

#include "pch.h"
#include "framework.h"
#include "DLL1.h"

DLL1_API double Add(double a, double b) { return a + b; }

DLL1_API double Multiply(double a, double b) { return a * b; }

DLL1_API double AddMultiply(double a, double b) { return a + (a * b); }
