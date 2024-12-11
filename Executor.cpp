#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <mutex>

#include "Executor.h"
#include "sender.h"

extern std::vector<ResultLog> results; // Shared vector that holds results from executors
std::mutex results_mutex; // Mutually exclusive access to results vector

int Executor::numOfTests = 0; // Overall count of tests

// Initializes executor test with test number
Executor::Executor(const wchar_t* libTag)
    : libTag(libTag) {
    numOfTests++;
    testID = numOfTests;
}

// Attempts to run given test, stores result on results vector
void Executor::execute() {

    try {
        result = runDLL();
        errorMessage = "No errors.";
    } catch(const std::exception& e) {
        errorMessage = e.what();
        result = 0;
    }
    
    std::lock_guard<std::mutex> lock(results_mutex);

    results.push_back(packageResults());
    // THIS NEEDS the message data from results to be serialized and sent
    const char* message = "The executor sent this!";
    sendMessage(message);
}

bool Executor::runDLL() {
	HINSTANCE hDLL;
	funcTestDriver testDriver;

	hDLL = LoadLibraryEx(libTag, NULL, NULL); // Handle to DLL

	std::cout << "----- " << libTag << " -----" << std::endl;

	if (hDLL != NULL) {
		testDriver = (funcTestDriver)GetProcAddress(hDLL, "testDriver");

		if (testDriver != NULL) {
			return testDriver();
		}
		else
			std::cout << "Did not load Test Driver correctly." << std::endl;

		FreeLibrary(hDLL);
	}
	else {
		std::cout << "Library load failed!" << std::endl;
        return false;
	}
}

// Passes results and exceptions to Result Log
ResultLog Executor::packageResults() {
    return ResultLog(result, errorMessage, testID);
}