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

   /* std::stringstream msg;
    msg << "Test " << testIndex << " has started.\n";
    std::cout << msg.str();*/

    try {
        result = test();
        std::cout << "TEST # " << testIndex << ": RESULT = " << result << std::endl;

    } catch(const std::exception& e) {
        errorMessage = e.what();
        std::cout << "TEST # " << testIndex << ": Failed" << std::endl;

    }
    /*msg << "Test " << testIndex << " has ended.\n";
    std::cout << msg.str();*/

}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    return ResultLog(result, errorMessage);
}