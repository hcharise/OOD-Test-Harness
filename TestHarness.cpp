#include "TestHarness.h"
using std::vector;

TestHarness::TestHarness() {}

TestHarness::TestHarness(vector< vector< void* > > functionParams, vector< void* > functionExpects, int logLevel)
    : functionParams(functionParams), functionExpects(functionExpects), logLevel(logLevel) {}

void TestHarness::createTestClass() {

}  

void TestHarness::runAllTests() {

}

void TestHarness::printOutResults() {

}