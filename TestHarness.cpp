#include "TestHarness.h"
#include "ResultLog.h"
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include "ThreadPool.h"
#include "Sockets.h"

using std::vector;
using std::thread;
using std::cout;

// Constructor - checks that vector is non-empty
TestHarness::TestHarness(vector<std::function<bool()>> tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");

    for (auto test : tests) {
        Executor executor(test);
        executors.push_back(executor);
    }
    
}
// Creates and runs executor for each lambda in tests vector
void TestHarness::runAllTests() {
    ThreadPool<3> trpl;
    int testNum = 0;

    // set up socket? SocketSystem socketSystem;

    for (auto executor : executors) {
        testNum++;

        ThreadPool<3>::CallObj co = [&trpl, &executor, testNum]() ->bool {
            std::stringstream msg;
            msg << "Thread " << Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id()) << " running test " << testNum << "\n";
            std::cout << msg.str();

            executor.execute(testNum);

            return true;
        };
        trpl.workItem(co);
    }

    ThreadPool<3>::CallObj exit = []() ->bool { return false; };
    trpl.workItem(exit);
    trpl.wait();
}

// Prints header/footer and the result log for each test run
void TestHarness::printOutResults(LogLevel logLevel) {

    for (Executor executor : executors) {
        testResults.push_back(executor.packageResults());
    }
    int i = 1;
    std::cout << "------------ TEST RESULTS ------------\n" << std::endl;
    for(ResultLog resultLog : testResults) {
        cout << "Test " << i++ << ":\t" << resultLog.getLogDetails(logLevel) << "\n";
    } 
    std::cout << "------ All results have been printed. ------\n" << std::endl;

}