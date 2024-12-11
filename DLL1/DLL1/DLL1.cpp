// DLL1.cpp : Defines the exported functions for the DLL.


#include "pch.h"
#include "framework.h"
#include "DLL1.h"

// TEST DRIVER
// Calls iTest functions to be tested and returns overall result

DLL1_API bool testDriver() {

    // Should pass
    Pos_Num posNum(3);

    // Should pass
    Equal_Num eqNum(3, 3);

    // Should pass
    E_Divide_Ten divTen(10);

    return (posNum.test() && eqNum.test() && divTen.test());
}
