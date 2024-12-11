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

	const wchar_t* libName = L"DLL1";
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

	libName = L"DLL2";
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