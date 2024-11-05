#include <vector>
#include <functional>
#include "TestHarness.h"
#include "iTest.h"

using std::vector;

int main() {

    // Vector of lambdas to be passed to TestHarness()
    vector<std::function<bool()>> tests;


    // TESTING FUNCTIONS
    
    // ------ Positive Number ------
    // Should pass
    auto lam_Pos_Num_Pass = [a = 3]() {
        Positive_Number num(a);
        return (num.test());
    };
    tests.push_back(lam_Pos_Num_Pass);
    // Should fail
    auto lam_Pos_Num_Fail = [a = -4]() {
        Positive_Number num(a);
        return (num.test());
    };
    tests.push_back(lam_Pos_Num_Fail);

    // ------ Empty String ------
    // Should pass
    auto lam_Empty_Str_Pass = [s = "happy"]() {
        Empty_String str(s);
        return (str.test());
    };
    tests.push_back(lam_Empty_Str_Pass);
    // Should fail
    auto lam_Empty_Str_Fail = [s = ""]() {
        Empty_String str(s);
        return (str.test());
    };
    tests.push_back(lam_Empty_Str_Fail);

    // ------ Equal Num ------
    // Should pass
    auto lam_Eq_Num_Pass = [x = 5, y = 5]() {
        Equal_Num nums(x, y);
        return (nums.test());
    };
    tests.push_back(lam_Eq_Num_Pass);
    // Should fail
    auto lam_Eq_Num_Fail = [x = 5, y = 8]() {
        Equal_Num nums(x, y);
        return (nums.test());
    };
    tests.push_back(lam_Eq_Num_Fail);


    // Create and run testHarness using tests declared above
    TestHarness testHarness(tests);
    testHarness.runAllTests();
    testHarness.printOutResults();
    
    return 0;
}