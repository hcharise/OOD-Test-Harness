#include <stdexcept>
#include "TestHarness.h"
using std::vector;

// Constructor - checks that vector is non-empty
TestHarness::TestHarness(vector<std::function<bool()>> tests)
    : tests(tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");
}

// Creates and runs executor for each lambda in tests vector
void TestHarness::runAllTests() {
    for(auto test : tests) {
        Executor tester(test);
        tester.execute();
        tester.packageResults(); // Need to push the results into a vector of restResults?
    } 
}

// NOT DONE - should take results from all exectors and print to output file?
void TestHarness::printOutResults() {
    for(ResultLog resultLog : testResults) {
        
    } 
}