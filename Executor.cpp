#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <random>
#include <chrono>
#include "Executor.h"

// Initializes executor test with test number
Executor::Executor(std::function<bool()> test)
    : test(test) {
}

// Attempts to run given test, stores result if successful
void Executor::execute(int testIndex) {

    // This section is only to show that it is multi threaded
    // the test index value is not truely needed for the program
    std::mt19937_64 eng{std::random_device{}()};
    std::uniform_int_distribution<> dist{100, 10000};
    std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
    std::cout << "Test " << testIndex << " has started\n";

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