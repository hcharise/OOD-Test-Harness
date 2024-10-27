#include <iostream>
#include "Executor.h"
using std::vector;

Executor::Executor(void* testFunction, vector<void*> functionParams, void* functionAssert) 
    : testFunction(testFunction), functionParams(functionParams), functionAssert(functionAssert) 
{}

void Executor::execute() {
    try {
        // call function here
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}

void Executor::assess() {

}

ResultLog Executor::packageResults() {
    return ResultLog();
}