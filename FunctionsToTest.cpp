//#include <vector>
//#include <functional>
//#include "TestHarness.h"
//#include "ResultLog.h"
//#include "iTest.h"
//
//using std::vector;
////
////int main() {
////
////    // Vector of lambdas to be passed to TestHarness()
////    vector<std::function<bool()>> tests;
////
////
////    // TESTING FUNCTIONS
////
////    for (int i = 0; i < 3; i++) {
////
////        // ------ Positive Number ------
////        // Should pass
////        auto lam_Pos_Num_Pass = [a = 3]() {
////            Pos_Num num(a);
////            return (num.test());
////        };
////        tests.push_back(lam_Pos_Num_Pass);
////        // Should fail
////        auto lam_Pos_Num_Fail = [a = -4]() {
////            Pos_Num num(a);
////            return (num.test());
////        };
////        tests.push_back(lam_Pos_Num_Fail);
////
////        // ------ Empty String ------
////        // Should pass
////        auto lam_Empty_Str_Pass = [s = "happy"]() {
////            Empty_Str str(s);
////            return (str.test());
////        };
////        tests.push_back(lam_Empty_Str_Pass);
////
////        // Should fail
////        auto lam_Empty_Str_Fail = [s = ""]() {
////            Empty_Str str(s);
////            return (str.test());
////        };
////        tests.push_back(lam_Empty_Str_Fail);
////
////        // ------ Equal Num ------
////        // Should pass
////        auto lam_Eq_Num_Pass = [x = 5, y = 5]() {
////            Equal_Num nums(x, y);
////            return (nums.test());
////        };
////        tests.push_back(lam_Eq_Num_Pass);
////        // Should fail
////        auto lam_Eq_Num_Fail = [x = 5, y = 8]() {
////            Equal_Num nums(x, y);
////            return (nums.test());
////        };
////        tests.push_back(lam_Eq_Num_Fail);
////
////        // Should error - divide by 0!
////        auto lam_E_Divide_Ten = [a = 0]() {
////            E_Divide_Ten num(a);
////            return (num.test());
////        };
////        tests.push_back(lam_E_Divide_Ten);
////    }
////
////    // Create and run testHarness using tests declared above
////    TestHarness testHarness(tests);
////    testHarness.runAllTests();
////    testHarness.printOutResults(LogLevel::TEST_SPECIFIC);
////    
////    return 0;
////}


// MathTest.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
#include <iostream>
#include <windows.h>
typedef bool (*funcTestDriver)();

int main()
{
	HINSTANCE hDLL;
	funcTestDriver testDriver;

	const wchar_t* libName = L"DLL2";
	hDLL = LoadLibraryEx(libName, NULL, NULL); // Handle to DLL

	if (hDLL != NULL) {

		testDriver = (funcTestDriver)GetProcAddress(hDLL, "testDriver");

		if (testDriver != NULL) {
			std::cout << "Test Driver = " << testDriver() << std::endl;
		}
		else
			std::cout << "Did not load Test Driver correctly." << std::endl;

		FreeLibrary(hDLL);
	}
	else {
		std::cout << "Library load failed!" << std::endl;
	}
	return 0;
}