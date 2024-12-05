#include "ResultLog.h"
//#include <sstream>
//#include <iomanip>
#include <ctime>
#include <stdexcept> //Provides standard exceptions like logic_error and runtime_error

using std::setw;

ResultLog::ResultLog(bool passed, const std::string & message, int testID):
	passed(passed), message(message), testID(testID) {
	timestamp = generateTimestamp();
}

std::string ResultLog::generateTimestamp() const {
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &now);  // Use localtime_r on non-Windows systems***
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
	switch(logLevel) {
		case LogLevel::PASS_FAIL:
			logStream << setw(width) << "  Result: " << (didPass() ? "PASS" : "FAIL") << "\n";
			break;

		case LogLevel::TEST_SPECIFIC:
			logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n" << "Message: " << getMessage() << "\n";
			break;

	return logStream.str();
}

// Serialize the log to a JSON string
std::string ResultLog::serialize() const {
    Json::Value root;
    root["passed"] = passed;
    root["message"] = message;
    root["timestamp"] = timestamp;

    Json::StreamWriterBuilder writer; // Used to configure and create JSON string writers
    return Json::writeString(writer, root); // Converts the JSON root object to a formatted string using the writer
}

// Deserialize a JSON string into a ResultLog object
ResultLog ResultLog::deserialize(const std::string& data) {
    Json::CharReaderBuilder reader; // Configures the JSON string reader
/* std::unique_ptr<Json::CharReader> reader_ptr(reader.newCharReader());
if (!reader_ptr->parse(json_str.c_str(), json_str.c_str() + json_str.length(), &root, &errs)) {
    // Handle parsing error
} */	
    Json::Value root; // Represents the root of a JSON structure, used to store parsed or generated JSON data
    std::istringstream iss(data);
    std::string errors;

    if (!Json::parseFromStream(reader, iss, &root, &errors)) {
        throw std::invalid_argument("Failed to deserialize ResultLog: " + errors);
    }

    ResultLog log;
    log.passed = root["passed"].asBool();
    log.message = root["message"].asString();
    log.timestamp = root["timestamp"].asString();
    return log;
}
