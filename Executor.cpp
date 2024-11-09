#include <iostream>
#include <iomanip>
#include <string>
#include "Executor.h"

// Initializes executor test with test number
Executor::Executor(std::function<bool()> test)
    : test(test) {
}

// Attempts to run given test, stores result if successful
void Executor::execute() {
    try {
        result = test();
    } catch(const std::exception& e) {
        errorMessage = e.what();
    }
}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    return ResultLog(result, errorMessage);
}