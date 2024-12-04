#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <random>
#include <sstream>
#include <chrono>
#include "Executor.h"

// Initializes executor test with test number
Executor::Executor(std::function<bool()> test)
    : test(test) {
}

// Attempts to run given test, stores result if successful
void Executor::execute(int testIndex) {

    std::stringstream msg;

    try {
        result = this->test();
    } catch(const std::exception& e) {
        errorMessage = e.what();
        result = 0;
    }
    /*msg << "Test " << testIndex << " has ended.\n";
    std::cout << msg.str();*/

}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    std::stringstream msg;

    msg << "Result: " << result << "   |||   Error Message: " << errorMessage << ".\n";
    std::cout << msg.str();
    return ResultLog(result, errorMessage);
}