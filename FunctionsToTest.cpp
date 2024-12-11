#include <vector>
#include <functional>
#include "TestHarness.h"
#include "ResultLog.h"
#include "iTest.h"

using std::vector;
using std::string;

int main() {
 
	vector<const wchar_t*> libraries;

	libraries.push_back(L"DLL1");
    libraries.push_back(L"DLL2");
    libraries.push_back(L"DLL3");
    libraries.push_back(L"DLL4");

    // Create and run testHarness using tests declared above
    TestHarness testHarness(libraries);
    testHarness.runAllTests();
    testHarness.printOutResults(LogLevel::TEST_SPECIFIC);
    
    return 0;
}