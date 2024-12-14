#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>
#include "json.h"

class Message {
public:
    Message(const std::string& src,const std::string& dest,const std::string& type,const std::string& author, const std::string& testID, const std::string& passed, const std::string& erroMessage);

    std::string getSource() const;
    std::string getDestination() const;
    std::string getType() const;
    std::string getAuthor() const;
    std::string getTestID() const;
    std::string getTimeStamp() const;
    std::string getPassed() const;
    std::string getErrorMessage() const;

    // Puts it to String format
    std::string serialize() const;

    // Puts it to message object
    static Message deserialize(const std::string& data);

private:
    std::string source;
    std::string destination;
    std::string messageType;
    std::string author;
    std::string testID;
    std::string timeStamp;
    std::string passed;
    std::string errorMessage;
    std::string getCurrentTime() const;
    const static char endChar = '*'; // indicates the end of the message
};

#endif
