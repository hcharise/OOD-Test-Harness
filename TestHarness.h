#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <vector>
#include <functional>
#include "Executor.h"

using std::vector;

class TestHarness {
    public:
        TestHarness(vector<std::function<bool()>> tests);
        void runAllTests();
        void printOutResults();
    private:
        vector<std::function<bool()>> tests;
        vector<ResultLog> testResults;
};

#endif 