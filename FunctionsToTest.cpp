#include <iostream>
#include <vector>
#include <string>
#include "TestHarness.cpp"

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
    params[0].push_back(&num1);
    params[0].push_back(&num2);
    params[0].push_back(&name);

    vector<void*> asserts;
    int output = 10;
    asserts.push_back(&output);
    TestHarness testHarness = TestHarness((void*)hello, params, asserts, 1);
    return 0;
}