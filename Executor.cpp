#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <random>
#include <sstream>
#include <mutex>
#include <chrono>
#include "Executor.h"

extern std::vector<bool> results;
std::mutex results_mutex;

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
    
    std::lock_guard<std::mutex> lock(results_mutex);
    results.push_back(result);
    std::cout << "The above has been pushed!" << std::endl;

    /*msg << "Test " << testIndex << " has ended.\n";
    std::cout << msg.str();*/

}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    std::stringstream msg;

    msg << "IN PACKAGING - Result: " << result << " Error Message: " << errorMessage << "\n";
    std::cout << msg.str();
    return ResultLog(result, errorMessage);
}