#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <mutex>

#include "Executor.h"
#include "sender.h"
#include "Message.h"

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

    std::string msgSrc = "Executor";
    std::string msgDest = "TestHarness";
    std::string msgType = "TestResult";
    std::string msgAuthor = getStringLibTag();
    std::string msgTestID = std::to_string(testID);
    std::string msgPassed = std::to_string(static_cast<int>(result));
    std::string msgError = errorMessage;

    Message msg(msgSrc, msgDest, msgType, msgAuthor, msgTestID, msgPassed, msgError);

    std::string srlmsg = msg.serialize();

    sendMessage(srlmsg.c_str());
}

bool Executor::runDLL() {
	HINSTANCE hDLL;
	funcTestDriver testDriver;

	hDLL = LoadLibraryEx(libTag, NULL, NULL); // Handle to DLL

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

std::string Executor::getStringLibTag() {
    // Convert const wchar_t* to std::string (UTF-8 encoding)
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(libTag);
}