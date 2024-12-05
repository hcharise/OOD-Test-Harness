#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <random>
#include <sstream>
#include <mutex>
#include <chrono>
#include "Executor.h"

extern std::vector<ResultLog> results;
std::mutex results_mutex;

int Executor::numOfTests = 0;

// Initializes executor test with test number
Executor::Executor(std::function<bool()> test)
    : test(test) {
    numOfTests++;
    testID = numOfTests;
}

// Attempts to run given test, stores result if successful
void Executor::execute(int testIndex) {

    std::stringstream msg;

    try {
        result = this->test();
        errorMessage = "No errors.";
    } catch(const std::exception& e) {
        errorMessage = e.what();
        result = 0;
    }
    
    std::lock_guard<std::mutex> lock(results_mutex);
    results.push_back(packageResults());

    /*msg << "Test " << testIndex << " has ended.\n";
    std::cout << msg.str();*/

}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    return ResultLog(result, errorMessage, testID);
}