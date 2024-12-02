#include "ResultLog.h"
#include <sstream>
#include <iomanip>

ResultLog::ResultLog(bool passed, const std::string& message) :
	passed(passed), message(message) {
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
std::string ResultLog::getLogDetails(LogLevel logLevel) const {
	std::ostringstream logStream;
	logStream << "Timestamp: " << getTimestamp() << "\n";
	// Log details based on log level
	switch (logLevel) {
	case LogLevel::PASS_FAIL:
		logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n";
		break;
	case LogLevel::TEST_SPECIFIC:
		logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n" << "Message: " << getMessage() << "\n";
		break;
	case LogLevel::DEBUG:
		logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n"
			<< "Message: " << getMessage() << "\n"
			<< "Debug Info: Detailed debug information.\n";
		break;

	}
	return logStream.str();
}
