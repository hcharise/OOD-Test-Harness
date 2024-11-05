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

    */

    // Move to test harness later!
    cout << std::boolalpha;

    // TESTING FUNCTIONS
    
    // Positive Number
    // Should pass
    auto lam_Pos_Num_Pass = [a = 3]() {
        Positive_Number num(a);
        return (num.test());
        };
    cout << "lam_Pos_Num_Pass = " << lam_Pos_Num_Pass() << endl;
    // Should fail
    auto lam_Pos_Num_Fail = [a = -4]() {
        Positive_Number num(a);
        return (num.test());
        };
    cout << "lam_Pos_Num_Fail = " << lam_Pos_Num_Fail() << endl;

    // Empty String
    // Should pass
    auto lam_Empty_Str_Pass = [s = "happy"]() {
        Empty_String str(s);
        return (str.test());
        };
    cout << "lam_Empty_Str_Pass = " << lam_Empty_Str_Pass() << endl;
    // Should fail
    auto lam_Empty_Str_Fail = [s = ""]() {
        Empty_String str(s);
        return (str.test());
        };
    cout << "lam_Empty_Str_Fail = " << lam_Empty_Str_Fail() << endl;


    // Equal Num
    // Should pass
    auto lam_Eq_Num_Pass = [x = 5, y = 5]() {
        Equal_Num nums(x, y);
        return (nums.test());
        };
    cout << "lam_Eq_Num_Pass = " << lam_Eq_Num_Pass() << endl;
    // Should fail
    auto lam_Eq_Num_Fail = [x = 5, y = 8]() {
        Equal_Num nums(x, y);
        return (nums.test());
        };
    cout << "lam_Eq_Num_Fail = " << lam_Eq_Num_Fail() << endl;

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