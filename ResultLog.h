#pragma once
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <json/json.h>

class ResultLog {
public:
    enum class LogLevel { PASS_FAIL, TEST_SPECIFIC, DEBUG };

    ResultLog();
    ResultLog(bool passed, const std::string& message);

    bool didPass() const;
    std::string getMessage() const;
    std::string getTimestamp() const;

    std::string getLogDetails(LogLevel logLevel) const;
    std::string serialize() const;
    static ResultLog deserialize(const std::string& jsonStr);

    // Additional functionality for communication requirements
    void setSource(const std::string& source);
    void setDestination(const std::string& destination);
    std::string getSource() const;
    std::string getDestination() const;

private:
    bool passed;
    std::string message;
    std::string timestamp;
    std::string source;      // New for message-passing
    std::string destination; // New for message-passing

    std::string generateTimestamp() const;
};
