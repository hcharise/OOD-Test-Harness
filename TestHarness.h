#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <vector>
#include <thread>
#include <functional>

#include "Executor.h"

using std::vector;
using std::thread;

class TestHarness {
    public:
        TestHarness(vector<const wchar_t*> libraries);
        void runAllTests();
        void printOutResults(LogLevel logLevel);
       //  void theadExecute(int i);
    private:
        vector<thread> threads;
        vector<Executor> executors;
        vector<ResultLog> testResults;
};

#endif