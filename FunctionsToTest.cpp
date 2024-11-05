#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "TestHarness.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void hello(int val1, int val2, string name) {
    std::cout << "Hello, " << name << std::endl;
}

int main() {
    /*
    // Vector of lambdas to be passed to TestHarness()
    vector<function<bool()>> functors;

    // Testing functions
    auto addLamPass = [x = 1, y = 2, z = 3]() {
        return (add(x, y, z) == 6);
    };

    */


    auto lam_Pos_Num_1 = [a = 3]() {
        PositiveNumber num(a);
        return (num.test());
        };

    cout << std::boolalpha;
    cout << "lam_Pos_Num_1 = " << lam_Pos_Num_1() << endl;

    auto lam_Pos_Num_2 = [a = -4]() {
        PositiveNumber num(a);
        return (num.test());
        };

    cout << std::boolalpha;
    cout << "lam_Pos_Num_2 = " << lam_Pos_Num_2() << endl;


    /*
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

    */
    return 0;
}