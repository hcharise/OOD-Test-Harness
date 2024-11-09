#include <iostream>
#include <iomanip>
#include "Executor.h"

int Executor::totalNumTests = 1;

// Initializes executor test with test number
Executor::Executor(std::function<bool()> test)
    : test(test), testNum(totalNumTests) {
    totalNumTests++;
}

// Attempts to run given test, stores result if successful
void Executor::execute() {
    try {
        result = test();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

// NOT DONE - need to modify to pass result to resultLog once built out
// Currently just prints out test num and result
ResultLog Executor::packageResults() {
    return ResultLog(result, "Error"); //DO TO:  fill in with error from execute
}