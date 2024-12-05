#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <mutex>

#include "Executor.h"

extern std::vector<ResultLog> results; // Shared vector that holds results from executors
std::mutex results_mutex; // Mutually exclusive access to results vector

int Executor::numOfTests = 0; // Overall count of tests

// Initializes executor test with test number
Executor::Executor(std::function<bool()> test)
    : test(test) {
    numOfTests++;
    testID = numOfTests;
}

// Attempts to run given test, stores result on results vector
void Executor::execute() {

    try {
        result = this->test();
        errorMessage = "No errors.";
    } catch(const std::exception& e) {
        errorMessage = e.what();
        result = 0;
    }
    
    std::lock_guard<std::mutex> lock(results_mutex);
    results.push_back(packageResults());
}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    return ResultLog(result, errorMessage, testID);
}