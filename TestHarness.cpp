#include "TestHarness.h"
#include "ResultLog.h"
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
using std::vector;
using std::thread;
using std::cout;

// Constructor - checks that vector is non-empty
TestHarness::TestHarness(vector<std::function<bool()>> tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");
    for(auto test : tests) {
        Executor executor(test);
        executors.push_back(executor);
        testResults.push_back(ResultLog(false, "NuLL")); // create empty space for thread to reach
    }
}

void TestHarness::theadExecute(int arrayIndex) {
    executors[arrayIndex].execute(arrayIndex);
    testResults[arrayIndex] = (executors[arrayIndex].packageResults());
}

// Creates and runs executor for each lambda in tests vector
void TestHarness::runAllTests() {
    vector<thread> workers;
    int arrayIndex = 0; // each thread has a executor and memory spot assinged to it
    for (Executor executor : executors) {
        // create individual threads
        workers.push_back(thread([this, arrayIndex]()  {
            theadExecute(arrayIndex);
        }));
        arrayIndex += 1;
    }

    // join all threads together
    std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
        t.join();
    });
}

// Prints header/footer and the result log for each test run
void TestHarness::printOutResults(LogLevel logLevel) {
    int i = 1;
    std::cout << "------------ TEST RESULTS ------------\n" << std::endl;
    for(ResultLog resultLog : testResults) {
        cout << "Test " << i++ << ":\t" << resultLog.getLogDetails(logLevel) << "\n";
    } 
    std::cout << "------ All tests have been run. ------\n" << std::endl;

}