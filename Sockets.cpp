/////////////////////////////////////////////////////////////////////////
// Sockets.cpp - C++ wrapper for Win32 socket api                      //
// ver 5.2                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016           //
// CST 4-187, Syracuse University, 315 443-3948, jfawcett@twcny.rr.com //
//---------------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                      //
// All rights granted provided this copyright notice is retained       //
//---------------------------------------------------------------------//
// Application: OOD Project #4                                         //
// Platform:    Visual Studio 2015, Dell XPS 8900, Windows 10 pro      //
/////////////////////////////////////////////////////////////////////////

#include "Sockets.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <memory>
#include <functional>
#include <exception>
#include "Utilities.h"

using namespace Sockets;
using Util = Utilities::StringHelper;
template<typename T>
using Conv = Utilities::Converter<T>;
using Show = StaticLogger<1>;

/////////////////////////////////////////////////////////////////////////////
// SocketSystem class members

//----< constructor starts up sockets by loading winsock lib >---------------

SocketSystem::SocketSystem()
{
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        Show::write("\n  WSAStartup failed with error = " + Conv<int>::toString(iResult));
    }
}
//-----< destructor frees winsock lib >--------------------------------------

SocketSystem::~SocketSystem()
{
    int error = WSACleanup();
    Show::write("\n  -- Socket System cleaning up\n");
}

/////////////////////////////////////////////////////////////////////////////
// Socket class members

//----< constructor sets TCP protocol and Stream mode >----------------------

Socket::Socket(IpVer ipver) : ipver_(ipver)
{
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}
//----< promotes Win32 socket to Socket >------------------------------------
/*
*  You have to set ip version if you want IP6 after promotion, e.g.:
*     s.ipVer() = IP6;
*/
Socket::Socket(::SOCKET sock) : socket_(sock)
{
    ipver_ = IP4;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
}
//----< transfer socket ownership with move constructor >--------------------

Socket::Socket(Socket&& s)
{
    socket_ = s.socket_;
    s.socket_ = INVALID_SOCKET;
    ipver_ = s.ipver_;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = s.hints.ai_family;
    hints.ai_socktype = s.hints.ai_socktype;
    hints.ai_protocol = s.hints.ai_protocol;
}
//----< transfer socket ownership with move assignment >---------------------

Socket& Socket::operator=(Socket&& s)
{
    if (this == &s) return *this;
    socket_ = s.socket_;
    s.socket_ = INVALID_SOCKET;
    ipver_ = s.ipver_;
    hints.ai_family = s.hints.ai_family;
    hints.ai_socktype = s.hints.ai_socktype;
    hints.ai_protocol = s.hints.ai_protocol;
    return *this;
}
//----< get, set IP version >------------------------------------------------
/*
*  Note:
*    Only instances of SocketListener are influenced by ipVer().
*    Clients will use whatever protocol the server supports.
*/
Socket::IpVer& Socket::ipVer()
{
    return ipver_;
}
//----< close connection >---------------------------------------------------

void Socket::close()
{
    if (socket_ != INVALID_SOCKET)
        ::closesocket(socket_);
}
//----< tells receiver there will be no more sends from this socket >--------

bool Socket::shutDownSend()
{
    ::shutdown(socket_, SD_SEND);
    if (socket_ != INVALID_SOCKET)
        return true;
    return false;
}

//----< tells receiver this socket won't call receive anymore >--------------

bool Socket::shutDownRecv()
{
    ::shutdown(socket_, SD_RECEIVE);
    if (socket_ != INVALID_SOCKET)
        return true;
    return false;
}
//----< tells receiver there will be no more sends or recvs >----------------

bool Socket::shutDown()
{
    ::shutdown(socket_, SD_BOTH);
    if (socket_ != INVALID_SOCKET)
        return true;
    return false;

}
//----< destructor closes socket handle >------------------------------------

Socket::~Socket() {
    shutDown();
    close();
}
//----< send buffer >--------------------------------------------------------
/*
*  - bytes must be less than or equal to the size of buffer
*  - doesn't return until requested number of bytes have been sent
*/
bool Socket::send(size_t bytes, byte* buffer)
{
    size_t bytesSent = 0, bytesLeft = bytes;
    byte* pBuf = buffer;
    while (bytesLeft > 0)
    {
        bytesSent = ::send(socket_, pBuf, bytesLeft, 0);
        if (socket_ == INVALID_SOCKET || bytesSent == 0)
            return false;
        bytesLeft -= bytesSent;
        pBuf += bytesSent;
    }
    return true;
}
//----< recv buffer >--------------------------------------------------------
/*
*  - bytes must be less than or equal to the size of buffer
*  - doesn't return until buffer has been filled with requested bytes
*/
bool Socket::recv(size_t bytes, byte* buffer)
{
    size_t bytesRecvd = 0, bytesLeft = bytes;
    byte* pBuf = buffer;
    while (bytesLeft > 0)
    {
        bytesRecvd = ::recv(socket_, pBuf, bytesLeft, 0);
        if (socket_ == INVALID_SOCKET || bytesRecvd == 0)
            return false;
        bytesLeft -= bytesRecvd;
        pBuf += bytesRecvd;
    }
    return true;
}
//----< sends a terminator terminated string >-------------------------------
/*
 *  Doesn't return until entire string has been sent
 *  By default terminator is '\0'
 */
bool Socket::sendString(const std::string& str, byte terminator)
{
    size_t bytesSent, bytesRemaining = str.size();
    const byte* pBuf = &(*str.begin());
    while (bytesRemaining > 0)
    {
        bytesSent = ::send(socket_, pBuf, bytesRemaining, 0);
        if (bytesSent == INVALID_SOCKET || bytesSent == 0)
            return false;
        bytesRemaining -= bytesSent;
        pBuf += bytesSent;
    }
    ::send(socket_, &terminator, 1, 0);
    return true;
}
//----< receives terminator terminated string >------------------------------
/*
 * - Doesn't return until a terminator byte as been received.
 * - result includes terminator
 * ToDo:
 * - needs reads of one byte to be replaced by bulk reads into a
 *   stream buffer to improve efficiency.
 * - That will require building a circular buffer.
 * - performance seems acceptable, so won't do this now
 */
std::string Socket::recvString(byte terminator)
{
    static const int buflen = 1;
    char buffer[1];
    std::string str;
    bool first = true;
    while (true)
    {
        iResult = ::recv(socket_, buffer, buflen, 0);
        if (iResult == 0 || iResult == INVALID_SOCKET)
        {
            //StaticLogger<1>::write("\n  -- invalid socket in Socket::recvString");
            break;
        }
        if (buffer[0] == terminator)
        {
            // added 9/29/2017
            str += terminator;
            break;
        }
        str += buffer[0];
    }
    return str;
}
//----< strips terminator character that recvString includes >---------------

std::string Socket::removeTerminator(const std::string& src)
{
    return src.substr(0, src.size() - 1);
}
//----< attempt to send specified number of bytes, but may not send all >----
/*
 * returns number of bytes actually sent
 */
size_t Socket::sendStream(size_t bytes, byte* pBuf)
{
    return ::send(socket_, pBuf, bytes, 0);
}
//----< attempt to recv specified number of bytes, but may not send all >----
/*
* returns number of bytes actually received
*/
size_t Socket::recvStream(size_t bytes, byte* pBuf)
{
    return ::recv(socket_, pBuf, bytes, 0);
}
//----< returns bytes available in recv buffer >-----------------------------

size_t Socket::bytesWaiting()
{
    unsigned long int ret;
    ::ioctlsocket(socket_, FIONREAD, &ret);
    return (size_t)ret;
}
//----< waits for server data, checking every timeToCheck millisec >---------

bool Socket::waitForData(size_t timeToWait, size_t timeToCheck)
{
    size_t MaxCount = timeToWait / timeToCheck;
    static size_t count = 0;
    while (bytesWaiting() == 0)
    {
        if (++count < MaxCount)
            ::Sleep(timeToCheck);
        else
            return false;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////
// SocketConnector class members

//----< constructor inherits its base Socket's Win32 socket_ member >--------

SocketConnecter::SocketConnecter() : Socket()
{
    hints.ai_family = AF_UNSPEC;
}
//----< move constructor transfers ownership of Win32 socket_ member >-------

SocketConnecter::SocketConnecter(SocketConnecter&& s) : Socket()
{
    socket_ = s.socket_;
    s.socket_ = INVALID_SOCKET;
    ipver_ = s.ipver_;
    hints.ai_family = s.hints.ai_family;
    hints.ai_socktype = s.hints.ai_socktype;
    hints.ai_protocol = s.hints.ai_protocol;
}
//----< move assignment transfers ownership of Win32 socket_ member >--------

SocketConnecter& SocketConnecter::operator=(SocketConnecter&& s)
{
    if (this == &s) return *this;
    socket_ = s.socket_;
    s.socket_ = INVALID_SOCKET;
    ipver_ = s.ipver_;
    hints.ai_family = s.hints.ai_family;
    hints.ai_socktype = s.hints.ai_socktype;
    hints.ai_protocol = s.hints.ai_protocol;
    return *this;
}
//----< destructor announces destruction if Verbose(true) >------------------

SocketConnecter::~SocketConnecter()
{
    Show::write("\n  -- SocketConnecter instance destroyed");
}
//----< request to connect to ip and port >----------------------------------

bool SocketConnecter::connect(const std::string& ip, size_t port)
{
    size_t uport = htons((u_short)port);
    std::string sPort = Conv<size_t>::toString(uport);

    // Resolve the server address and port
    const char* pTemp = ip.c_str();
    iResult = getaddrinfo(pTemp, sPort.c_str(), &hints, &result);  // was DEFAULT_PORT
    if (iResult != 0) {
        Show::write("\n  -- getaddrinfo failed with error: " + Conv<int>::toString(iResult));
        return false;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        char ipstr[INET6_ADDRSTRLEN];
        void* addr;
        char* ipver;

        // get pointer to address - different fields in IPv4 and IPv6:

        if (ptr->ai_family == AF_INET) { // IPv4
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)ptr->ai_addr;
            addr = &(ipv4->sin_addr);
            char astring[] = "IPv4";
            ipver = astring;
        }
        else { // IPv6
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)ptr->ai_addr;
            addr = &(ipv6->sin6_addr);
            char astring[] = "IPv6";
            ipver = astring;
        }

        // convert the IP to a string and print it:
        inet_ntop(ptr->ai_family, addr, ipstr, sizeof ipstr);
        //printf("\n  %s: %s", ipver, ipstr);

        // Create a SOCKET for connecting to server
        socket_ = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_ == INVALID_SOCKET) {
            int error = WSAGetLastError();
            Show::write("\n\n  -- socket failed with error: " + Conv<int>::toString(error));
            return false;
        }

        iResult = ::connect(socket_, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            socket_ = INVALID_SOCKET;
            int error = WSAGetLastError();
            Show::write("\n  -- WSAGetLastError returned " + Conv<int>::toString(error));
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (socket_ == INVALID_SOCKET) {
        int error = WSAGetLastError();
        Show::write("\n  -- unable to connect to server, error = " + Conv<int>::toString(error));
        return false;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////
// SocketListener class members

//----< constructs SocketListener, specifying type of protocol to use >------

SocketListener::SocketListener(size_t port, IpVer ipv) : Socket(ipv), port_(port)
{
    socket_ = INVALID_SOCKET;
    ZeroMemory(&hints, sizeof(hints));
    if (ipv == Socket::IP6)
        hints.ai_family = AF_INET6;       // use this if you want an IP6 address
    else
        hints.ai_family = AF_INET;        // this gives IP4 address
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
}
//----< move constructor transfers ownership of Win32 socket_ member >-------

SocketListener::SocketListener(SocketListener&& s) : Socket()
{
    socket_ = s.socket_;
    s.socket_ = INVALID_SOCKET;
    ipver_ = s.ipver_;
    hints.ai_family = s.hints.ai_family;
    hints.ai_socktype = s.hints.ai_socktype;
    hints.ai_protocol = s.hints.ai_protocol;
    hints.ai_flags = s.hints.ai_flags;
}
//----< move assignment transfers ownership of Win32 socket_ member >--------

SocketListener& SocketListener::operator=(SocketListener&& s)
{
    if (this == &s) return *this;
    socket_ = s.socket_;
    s.socket_ = INVALID_SOCKET;
    ipver_ = s.ipver_;
    hints.ai_family = s.hints.ai_family;
    hints.ai_socktype = s.hints.ai_socktype;
    hints.ai_protocol = s.hints.ai_protocol;
    hints.ai_flags = s.hints.ai_flags;
    return *this;
}
//----< destructor announces destruction if Verbal(true) >-------------------

SocketListener::~SocketListener()
{
    Show::write("\n  -- SocketListener instance destroyed");
}
//----< binds SocketListener to a network adddress on local machine >--------

bool SocketListener::bind()
{
    Show::write("\n  -- staring bind operation");

    // Resolve the server address and port

    size_t uport = ::htons((u_short)port_);
    StaticLogger<1>::write("\n  -- netstat uport = " + Utilities::Converter<size_t>::toString(uport));
    std::string sPort = Conv<size_t>::toString(uport);
    iResult = getaddrinfo(NULL, sPort.c_str(), &hints, &result);
    if (iResult != 0) {
        Show::write("\n  -- getaddrinfo failed with error: " + Conv<int>::toString(iResult));
        return false;
    }

    // Iterate through all results and bind to first available or all, depending on else condition, below

    for (auto pResult = result; pResult != NULL; pResult = pResult->ai_next)
    {
        // Create a SOCKET for connecting to server

        socket_ = socket(pResult->ai_family, pResult->ai_socktype, pResult->ai_protocol);
        if (socket_ == INVALID_SOCKET) {
            int error = WSAGetLastError();
            Show::write("\n  -- socket failed with error: " + Conv<int>::toString(error));
            continue;
        }
        Show::write("\n  -- server created ListenSocket");

        // Setup the TCP listening socket

        iResult = ::bind(socket_, pResult->ai_addr, (int)pResult->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            int error = WSAGetLastError();
            Show::write("\n  -- bind failed with error: " + Conv<int>::toString(error));
            socket_ = INVALID_SOCKET;
            continue;
        }
        else
        {
            //break;  // bind to first available
            continue;   // bind to all
        }
    }
    freeaddrinfo(result);
    Show::write("\n  -- bind operation complete");
    return true;
}
//----< put SocketListener in listen mode, doesn't block >-------------------

bool SocketListener::listen()
{
    Show::write("\n  -- starting TCP listening socket setup");
    iResult = ::listen(socket_, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        int error = WSAGetLastError();
        Show::write("\n  -- listen failed with error: " + Conv<int>::toString(error));
        socket_ = INVALID_SOCKET;
        return false;
    }
    Show::write("\n  -- server TCP listening socket setup complete");
    return true;
}
//----< accepts incoming requrests to connect - blocking call >--------------

Socket SocketListener::accept()
{
    ::SOCKET sock = ::accept(socket_, NULL, NULL);
    Socket clientSocket = sock;    // uses Socket(::SOCKET) promotion ctor
    if (!clientSocket.validState()) {
        acceptFailed_ = true;
        int error = WSAGetLastError();
        Show::write("\n  -- server accept failed with error: " + Conv<int>::toString(error));
        Show::write(
            "\n  -- this occurs when application shuts down while listener thread is blocked on Accept call"
        );
        return clientSocket;
    }
    return clientSocket;
}
//----< request SocketListener to stop accepting connections >---------------

void SocketListener::stop()
{
    stop_.exchange(true);
    sendString("Stop!");
}