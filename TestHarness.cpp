#include <stdexcept>
#include "TestHarness.h"
using std::vector;

TestHarness::TestHarness(vector<vector<void*>> paramVectors, vector<void*> assertVector, int logLevel)
    : paramVectors(paramVectors), assertVector(assertVector), logLevel(logLevel) {
    tests = 0;
    int check = 0;
    for (auto i: paramVectors) tests += 1;
    for (auto i: assertVector) check += 1;
    if (tests != check) throw std::invalid_argument("Paramitors and asserst vectors are not equal");
}

void TestHarness::createTests() {
    for(int i = 0; i < tests; i++) {
        testers.push_back(Executor(paramVectors[i], assertVector[i]));
    }  
}  

void TestHarness::runAllTests() {
    for(Executor tester : testers) {
        tester.execute();
        testResults.push_back(tester.packageResults());
    } 
}

void TestHarness::printOutResults() {
    for(ResultLog resultLog : testResults) {
        
    } 
}