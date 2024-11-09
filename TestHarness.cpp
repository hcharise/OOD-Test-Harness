#include "TestHarness.h"
#include "ResultLog.h"
#include <string>
#include <iostream>
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
        testResults.push_back(tester.packageResults());
    } 
}

// Prints header/footer and the result log for each test run
void TestHarness::printOutResults() {
    int i = 0;
    std::cout << "------------ TEST RESULTS ------------\n" << std::endl;
    for(ResultLog resultLog : testResults) {
        std::cout << "Test " << i++ << "\t" << resultLog.getLogDetails(LogLevel::TEST_SPECIFIC) << "\n";
    } 
    std::cout << "------ All tests have been run. ------\n" << std::endl;

}