#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include "Executor.h"
#include "ResultLog.h"

class TestHarness {
    ResultLog testResult;

    public:
        TestHarness();
        void createTestClass();
        void runAllTests();
        void printOutResults();
};

#endif 