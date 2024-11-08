#include "ResultLog.h"
#include <sstream>
#include <iomanip>

ResultLog::ResultLog(bool passed,
                     const std::string& message,
                     const std::vector<std::string>& inputs,
                     const std::string& expectedOutput,
                     const std::string& actualOutput,
                     LogLevel logLevel)
    : passed(passed), message(message), inputs(inputs), expectedOutput(expectedOutput), actualOutput(actualOutput), logLevel(logLevel){
    timestamp = generateTimestamp()

}
std::string ResultLog::generateTimestamp() const {
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
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
//Input Params -return
std::vector<std::string> ResultLog::getInputs() const {
    return inputs;
}
//Expected output - return
std::string ResultLog::getExpectedOutput() const {
    return expectedOutput;
}
//Actual OUTPUT *****

std::string ResultLog::getActualOutput() const {
    return actualOutput;
}

//Timestamp
std::string ResultLog::getTimestamp() const {
    return timestamp;
}

//Log details based on Log levels
std::string ResultLog::getLogDetails() const {
    std::ostringstream logStream;
    
    logStream << "Timestamp: " << getTimestamp() << "\n";
    
    // Log details based on log level
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
                      << "Inputs: ";
            
            for (const auto& input : getInputs()) {
                logStream << input << " ";
            }
            
            logStream << "\nExpected Output: " << getExpectedOutput()
                      << "\nActual Output: " << getActualOutput() << "\n";
            break;
    }
    
    return logStream.str();
}
