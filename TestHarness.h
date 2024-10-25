#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <vector> 
#include "Executor.h"
#include "ResultLog.h"

using std::vector;

class TestHarness {
    public:
        TestHarness(vector<vector<void*>> paramVectors, vector<void*> assertVector, int logLevel);
        void createTests();
        void runAllTests();
        void printOutResults();
    private:
        vector<Executor> testers;
        vector<ResultLog> testResults;
        vector<vector<void*>> paramVectors;
        vector<void*> assertVector;
        int logLevel;
        int tests = 0;
};

#endif 