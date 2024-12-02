#include "TestHarness.h"
#include "ResultLog.h"
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include "ThreadPool.h"

using std::vector;
using std::thread;
using std::cout;

// Constructor - checks that vector is non-empty
TestHarness::TestHarness(vector<std::function<bool()>> tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");

    ThreadPool<3> trpl;
    int testNum = 0;

    for (auto test : tests) {
        testNum++;

        Executor executor(test);
        executors.push_back(executor);

        ThreadPool<3>::CallObj co = [&trpl, &executor, testNum]() ->bool {
            std::stringstream msg;
            msg << "--------------------  Thread " << Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id()) << " : \n";
            std::cout << msg.str();

            executor.execute(testNum);
            
            return true;
        };
        trpl.workItem(co);
    }

    ThreadPool<3>::CallObj exit = []() ->bool { return false; };
    trpl.workItem(exit);
    trpl.wait();
    
    testResults.push_back(ResultLog(false, "NuLL")); // create empty space for thread to reach

}

//void TestHarness::theadExecute(int arrayIndex) {
//    executors[arrayIndex].execute(arrayIndex);
//    testResults[arrayIndex] = (executors[arrayIndex].packageResults());
//}

// Creates and runs executor for each lambda in tests vector
//void TestHarness::runAllTests() {
//    vector<thread> workers;
//    int arrayIndex = 0; // each thread has a executor and memory spot assinged to it
//    for (Executor executor : executors) {
//        // create individual threads
//        workers.push_back(thread([this, arrayIndex]()  { // push into blocking queue instead
//            theadExecute(arrayIndex);
//        }));
//        arrayIndex += 1;
//    }
//
//    // join all threads together
//    std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
//        t.join();
//    });
//}

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
    std::cout << "------ All tests have been run. ------\n" << std::endl;

}