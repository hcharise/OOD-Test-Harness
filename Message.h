#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>
#include <json.hpp>

class Message {
public:
    Message(std::string& src, std::string& dest, std::string& type, std::string& author, std::string& body);

    std::string getSource() const;
    std::string getDestination() const;
    std::string getType() const;
    std::string getAuthor() const;
    std::string getTimeStamp() const;
    std::string getBody() const;

    // Puts it to String format
    std::string serialize() const;

    // Puts it to message object
    static Message deserialize(const std::string& data);

private:
    std::string source;
    std::string destination;
    std::string messageType;
    std::string author;
    std::string timeStamp;
    std::string body;
    std::string getCurrentTime() const;
};

#endif
