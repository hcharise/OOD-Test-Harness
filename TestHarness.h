#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <vector> 
#include "Executor.h"
#include "ResultLog.h"

using std::vector;

class TestHarness {
    public:
        TestHarness();
        TestHarness(vector< vector< void* > > functionParams, vector< void* > functionExpects, int logLevel);
        void createTestClass();
        void runAllTests();
        void printOutResults();
    private:
        Executor executor;
        ResultLog resultLog;
        vector< vector< void* > > functionParams;
        vector< void* > functionExpects;
        int logLevel;
};

#endif 