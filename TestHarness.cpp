#include <stdexcept>
#include "TestHarness.h"
using std::vector;

TestHarness::TestHarness(vector<std::function<bool()>> tests)
    : tests(tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");

}


void TestHarness::runAllTests() {
    for(auto test : tests) {
        Executor tester(test);
        tester.execute();
        //testResults.push_back(test.packageResults());
    } 
}

void TestHarness::printOutResults() {
    //for(ResultLog resultLog : testResults) {
        
    //} 
}