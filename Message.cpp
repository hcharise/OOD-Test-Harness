#include "Message.h"
#include <sstream>
#include <iomanip>

Message::Message(std::string src, std::string dest, std::string type, std::string author, std::string body)
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

// Need to add serialization + deserialization
