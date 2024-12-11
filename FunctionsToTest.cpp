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

void runDLL(const wchar_t* libTag, std::string libName);

int main()
{
	runDLL(L"DLL1", "DLL1");
	runDLL(L"DLL2", "DLL2");
	runDLL(L"DLL3", "DLL3");
	runDLL(L"DLL4", "DLL4");
	
	return 0;
}

void runDLL(const wchar_t* libTag, std::string libName) {
	HINSTANCE hDLL;
	funcTestDriver testDriver;

	hDLL = LoadLibraryEx(libTag, NULL, NULL); // Handle to DLL

	std::cout << "----- " << libName << " -----" << std::endl;

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
	return;
}