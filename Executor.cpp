#include "Executor.h"
using std::vector;

Executor::Executor(void* testFunction, vector<void*> functionParams, void* functionAssert) 
    : testFunction(testFunction), functionParams(functionParams), functionAssert(functionAssert) 
{}

void Executor::execute() {
    
}

void Executor::assess() {

}

ResultLog Executor::packageResults() {
    return ResultLog();
}