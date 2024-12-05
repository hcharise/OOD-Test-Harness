#include "Message.h"
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Message::Message(std::string& src, std::string& dest, std::string& type, std::string& author, std::string& body)
    : source(src), destination(dest), messageType(type), author(author), body(body) {
    timeStamp = getCurrentTime();
}

std::string Message::getSource() const { return source; }
std::string Message::getDestination() const { return destination; }
std::string Message::getType() const { return messageType; }
std::string Message::getAuthor() const { return author; }
std::string Message::getTimeStamp() const { return timeStamp; }
std::string Message::getBody() const { return body; }

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
    j["timestamp"] = timeStamp;
    j["body"] = body;
    return j.dump();  // Convert JSON object to string
}

// Deserlize from JSON
Message Message::deserialize(const std::string& data) {
    json j = json::parse(data);
    return Message(
        j["source"].get<std::string>(),
        j["destination"].get<std::string>(),
        j["type"].get<std::string>(),
        j["author"].get<std::string>(),
        j["body"].get<std::string>()
    );
}