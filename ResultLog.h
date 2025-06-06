#ifndef RESULT_LOG_H
#define RESULT_LOG_H

#include <string>
#include <vector>
#include <ctime>  //For Date Time stamp

enum class LogLevel {
	PASS_FAIL, // Only logs pass/fail status
	TEST_SPECIFIC, // Logs specific messages for each test
};

class ResultLog {
public:
	ResultLog(bool passed, const std::string& message, int testID, const std::string& libName);
	bool didPass() const; // Fetch test log data
	std::string getMessage() const;
	std::string getTimestamp() const;
	std::string getLogDetails(LogLevel logLevel, int numOfTests) const; // Method to display results based on log level
private:
	bool passed; // Indicates if the test passed
	std::string message; // Message with specific information or errors
	std::string timestamp; // Timestamp of the test execution
	std::string generateTimestamp() const; // Generate the current timestamp
	std::string libName;
	int testID;
};
#endif
