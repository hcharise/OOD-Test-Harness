#include "ResultLog.h"

// Constructor
ResultLog::ResultLog() : passed(false), message(""), timestamp(generateTimestamp()) {}

ResultLog::ResultLog(bool passed, const std::string& message)
    : passed(passed), message(message), timestamp(generateTimestamp()) {}

bool ResultLog::didPass() const {
    return passed;
}

std::string ResultLog::getMessage() const {
    return message;
}

std::string ResultLog::getTimestamp() const {
    return timestamp;
}

// Generate a timestamp in the format "YYYY-MM-DD HH:MM:SS"
std::string ResultLog::generateTimestamp() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now); // Use localtime_r for non-Windows systems
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string ResultLog::getLogDetails(LogLevel logLevel) const {
    std::ostringstream logStream;
    logStream << "Timestamp: " << getTimestamp() << "\n"
              << "Source: " << source << "\n"
              << "Destination: " << destination << "\n";

    switch (logLevel) {
        case LogLevel::PASS_FAIL:
            logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n";
            break;
        case LogLevel::TEST_SPECIFIC:
            logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n"
                      << "Message: " << getMessage() << "\n";
            break;
        case LogLevel::DEBUG:
            logStream << "Test Result: " << (didPass() ? "PASS" : "FAIL") << "\n"
                      << "Message: " << getMessage() << "\n"
                      << "Debug Info: Detailed debug information.\n";
            break;
    }
    return logStream.str();
}
//Serialize JSON String
std::string ResultLog::serialize() const {
    Json::Value root;
    root["passed"] = passed;
    root["message"] = message;
    root["timestamp"] = timestamp;
    root["source"] = source;
    root["destination"] = destination;

    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, root);
}
//Deserialize
ResultLog ResultLog::deserialize(const std::string& jsonStr) {
    Json::Value root;
    Json::CharReaderBuilder reader;
    std::istringstream iss(jsonStr);
    std::string errors;

    if (!Json::parseFromStream(reader, iss, &root, &errors)) {
        throw std::invalid_argument("Failed to deserialize ResultLog: " + errors);
    }

    ResultLog log;
    log.passed = root["passed"].asBool();
    log.message = root["message"].asString();
    log.timestamp = root["timestamp"].asString();
    log.source = root["source"].asString();
    log.destination = root["destination"].asString();

    return log;
}

void ResultLog::setSource(const std::string& source) {
    this->source = source;
}

void ResultLog::setDestination(const std::string& destination) {
    this->destination = destination;
}

std::string ResultLog::getSource() const {
    return source;
}

std::string ResultLog::getDestination() const {
    return destination;
}
