#include <string>
#include <iostream>
#include <thread>
#include <algorithm>

#include "ThreadPool.h"
#include "Sockets.h"
#include "TestHarness.h"
#include "ResultLog.h"

using std::vector;
using std::thread;
using std::cout;
using std::endl;

std::vector<ResultLog> results; // Shared vector that holds results from executors

// Constructor - checks that vector is non-empty, creates executor object for each test
TestHarness::TestHarness(vector<std::function<bool()>> tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");

    for (auto test : tests) {
        Executor executor(test);
        executors.push_back(executor);
    }
}

// Creates threadpool and passes in all tests to be run
void TestHarness::runAllTests() {

    // Create threadpool
    ThreadPool<3> trpl;

    cout << "-------- Threadpool started.. --------\n";

    // Declare a callable object for each executor
    for (auto executor : executors) {
        ThreadPool<3>::CallObj co = [&trpl, executor]() mutable ->bool {
            // Threadsafe message indicating which test is being run by which thread
            std::stringstream msg;
            msg << "Thread " << Utilities::Converter<thread::id>::toString(std::this_thread::get_id()) << " running test " << executor.testID << "\n";
            std::cout << msg.str();

            // Run the test
            executor.execute();

            return true; // True tells the thread to continue taking tasks
        };

        // Add new callable object to blocking queue that threads pull tasks from
        trpl.workItem(co);
    }

    // Send "exit" task and wait for all tasks in threadpool to complete
    ThreadPool<3>::CallObj exit = []() ->bool { return false; };
    trpl.workItem(exit);
    trpl.wait();

    cout << "-------- Threadpool complete! --------\n\n";

}

// Prints header/footer and the result log for each test run
void TestHarness::printOutResults(LogLevel logLevel) {

    cout << "------------ TEST RESULTS ------------\n" << endl;

    for (auto result : results) {
        cout << result.getLogDetails(logLevel, Executor::numOfTests);
    }

    cout << "----------- End of Results -----------" << endl;
}