#ifndef ITEST_H
#define ITEST_H

#include <string>
#include <iostream>

class iTest {
public:
    bool Pos_Num(int n) {
        return n > 0;
    }

    // Checks if two numbers are equal
    bool Equal_Num(int a, int b) {
        return a == b;
    }

    // Checks if the input string is non-empty
    bool Empty_String(const std::string& str) {
        return !str.empty();
    }
};

#endif // ITEST_H
