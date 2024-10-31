#include <iostream>
#include <vector>
#include <string>
#include "TestHarness.h"

using std::vector;
using std::string;

void hello(int val1, int val2, string name) {
    std::cout << "Hello, " << name << std::endl;
}

int main() {
    vector<vector<void*>> params;
    int num1 = 10;
    int num2 = 5;
    string name = "Steve";

    vector<void*> temp;
    temp.push_back(&num1);
    temp.push_back(&num2);
    temp.push_back(&name);
    params.push_back(temp);

    vector<void*> asserts;
    int output = 10;
    asserts.push_back(&output);

    hello(num1, num2, name);
    TestHarness testHarness = TestHarness((void*)hello, params, asserts, 1);
    testHarness.runAllTests();
    testHarness.printOutResults();
    return 0;
}