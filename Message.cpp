#include "Message.h"
#include <sstream>
#include <iomanip>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

Message::Message(const std::string& src,const std::string& dest,const std::string& type,const std::string& author, const std::string& testID, const std::string& passed, const std::string& errorMessage)
    : source(src), destination(dest), messageType(type), author(author), testID(testID), passed(passed), errorMessage(errorMessage) {
    timeStamp = getCurrentTime();
}

std::string Message::getSource() const { return source; }
std::string Message::getDestination() const { return destination; }
std::string Message::getType() const { return messageType; }
std::string Message::getAuthor() const { return author; }
std::string Message::getTestID() const { return testID; }
std::string Message::getTimeStamp() const { return timeStamp; }
std::string Message::getPassed() const { return passed; }
std::string Message::getErrorMessage() const { return errorMessage; }


std::string Message::getCurrentTime() const {
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &now);
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

// Serialize into JSON
std::string Message::serialize() const {

    json j;
    j["source"] = source;
    j["destination"] = destination;
    j["type"] = messageType;
    j["author"] = author;
    j["testID"] = testID;
    j["timestamp"] = timeStamp;
    j["passed"] = passed;
    j["errorMessage"] = errorMessage;

    return j.dump() + endChar;  // Convert JSON object to string
}

// Deserlize from JSON
Message Message::deserialize(const std::string& data) {

    std::string processedMessage;
    int index = 0;

    while (data[index] != endChar) {
        processedMessage = processedMessage + data[index];
        index++;
    }

    json j = json::parse(processedMessage);
    std::string param1 = j["source"].get<std::string>();
    std::string param2 = j["destination"].get<std::string>();
    std::string param3 = j["type"].get<std::string>();
    std::string param4 = j["author"].get<std::string>();
    std::string param5 = j["testID"].get<std::string>();
    std::string param6 = j["passed"].get<std::string>();
    std::string param7 = j["errorMessage"].get<std::string>();
    
    return Message(param1, param2, param3, param4, param5, param6, param7);
}