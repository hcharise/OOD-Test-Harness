#include <iostream>
#include "Executor.h"
using std::vector;

Executor::Executor(void* testFunction, vector<void*> functionParams, void* functionAssert) 
    : testFunction(testFunction), functionParams(functionParams), functionAssert(functionAssert) 
{}

void Executor::execute() {
    try {
        testFunction();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    // need to save results of testFunction and call assess?
}

void Executor::assess() {
    // compare results to asserts
    // call ResultLog?
}

ResultLog Executor::packageResults() {
    return ResultLog();
}