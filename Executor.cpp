#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <mutex>

#include "Executor.h"
#include "sender.h"
#include "Message.h

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
    // THIS NEEDS the message data from results to be serialized and sent
    // const char* message = "The executor sent this!";
    // sendMessage(message);
        // const char* message = "message";
    // sendMessage(message);

    Message msg(
        "Executor",       
        "TestHarness",       
        "TestResult",        
        "Executor",          
        packageResults().serialize()
    );

    std::string srlmsg = msg.serialize();
    sendMessage(srlmsg.c_str());
}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    return ResultLog(result, errorMessage, testID);
}