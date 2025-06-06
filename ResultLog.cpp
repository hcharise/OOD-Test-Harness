#include "ResultLog.h"

#include <sstream>
#include <iomanip>

using std::setw;

ResultLog::ResultLog(bool passed, const std::string& message, int testID, const std::string& libName) :
	passed(passed), message(message), testID(testID), libName(libName) {
	timestamp = generateTimestamp();
}

std::string ResultLog::generateTimestamp() const {
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &now);
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}
//Test -Pass or Fail
bool ResultLog::didPass() const {
	return passed;
}
//Specific execution message
std::string ResultLog::getMessage() const {
	return message;
}

//Timestamp
std::string ResultLog::getTimestamp() const {
	return timestamp;
}
//Log details based on Log levels
std::string ResultLog::getLogDetails(LogLevel logLevel, int numOfTests) const {

	std::ostringstream logStream;
	logStream << std::left;
	const int width = 13; // Width for printing results


	logStream << "Test " << testID << " of " << numOfTests << "\n";

	// Log details based on log level
	switch (logLevel) {
	case LogLevel::PASS_FAIL:
		logStream << setw(width) << "  Library: " << libName << "\n";
		logStream << setw(width) << "  Result: " << (didPass() ? "PASS" : "FAIL") << "\n";
		break;

	case LogLevel::TEST_SPECIFIC:
		logStream << setw(width) << "  Library: " << libName << "\n";
		logStream << setw(width) << "  Result: " << (didPass() ? "PASS" : "FAIL") << "\n";
		logStream << setw(width) << "  Message: " << getMessage() << "\n";
		break;
	}
	logStream << setw(width) << "  Timestamp: " << getTimestamp() << "\n\n";

	return logStream.str();
}
