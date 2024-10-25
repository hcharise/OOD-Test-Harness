#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <string>


class TestHarness {
    public:
        TestHarness();
        void createTestClass();
        void runAllTests();
        void printOutResults();
};

#endif 