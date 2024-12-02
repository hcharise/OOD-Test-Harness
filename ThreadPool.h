#pragma once
/////////////////////////////////////////////////////////////////////
// ThreadPool.h - Enqueue work items to run on one of a collection //
//                of threads, created at startup.                  //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016       //
/////////////////////////////////////////////////////////////////////
/*
* Threadpool is a template class, parameterized on the number of
* threads to start.  Each instance with the same parameter value
* shares a mutex used to synchronize access to data shared between
* threads.
*
* Each thread deQs workItems from a blocking queue of callable objects,
* executes the callable object, and goes back to the queue for another.
* The workItems must take no arguments and return a bool.  The value
* of the bool should always be true unless the user wants to shut down
* the threadpool.  If a job needs input parameters, they are simply
* included in the callable object's capture list (lambda) or as member
* data (functor).
*
* The thread pool can be shut down by enqueuing a work item that returns
* false.  Each thread executes the work item and if false encqueus the
* same workItem and then exits.  This means that each thread will terminate.
*/
/*
 * ToDo:
 * - Provide a longRunningOperation option that starts another thread
 *   and terminates when long running operation completes.
 */
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include "Cpp11-BlockingQueue.h"
#include "Logger.h"
#include "Sockets.h"
#include "Utilities.h"


template <size_t numThreads>
class ThreadPool
{
public:
    using CallObj = std::function<bool()>;

    ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void workItem(CallObj& co);
    void wait();
    std::mutex& mutex();
    ~ThreadPool();
private:
    BlockingQueue<CallObj> Q_;
    std::vector<std::thread> threads_;
    std::mutex mtx_;    // lock shared by all threads in pool
    std::function<void()> threadProc_;
};

template<size_t numThreads>
std::mutex& ThreadPool<numThreads>::mutex() { return mtx_; }

//----< define threadProc and start threads >------------------------

template <size_t numThreads>
ThreadPool<numThreads>::ThreadPool()
{
    threadProc_ = [this]()  // all threads use this to acquire their callable objects.
        {
            while (true)
            {
                CallObj co = Q_.deQ();
                if (!co())
                {
                    Q_.enQ(co);
                    break;
                }
            }
            /*std::stringstream msg;
            msg << "\tthread " << Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id()) << " terminating\n";
            std::cout << msg.str()*/;

        };
    for (size_t i = 0; i < numThreads; ++i)
    {
        std::thread t(threadProc_);

        ///
      
        ///
        size_t port = 8080;

        Sockets::SocketSystem ss;  // Initialize socket system

        // Set up the client to connect to the server
        Sockets::SocketConnecter client;
        int loop = 1;
        while (!client.connect("localhost", port) && loop < 1)
        {
            std::cerr << "Thread " + Utilities::Converter<std::thread::id>::toString(t.get_id()) << " client waiting to connect\n";
            loop++;
        }
        if (client.connect("localhost", port)) {
            std::string msg = "Hello from Client!";
            client.sendString(msg);  // Send message to the server
            std::string response = client.recvString();  // Receive the server's response
            std::cout << "Client received: " << response << std::endl;
        }
        else {
            std::cerr << "Thread " + Utilities::Converter<std::thread::id>::toString(t.get_id()) << " failed to connect to the server!" << std::endl;
        }

        // Give the server time to process before the main thread finishes
        std::this_thread::sleep_for(std::chrono::seconds(1));

        ///

        /*std::stringstream msg;
        msg << "\tstarting threadpool thread " + Utilities::Converter<std::thread::id>::toString(t.get_id()) << "\n";
        std::cout << msg.str();*/

        threads_.push_back(std::move(t));
    }
}

template <size_t numThreads>
void ThreadPool<numThreads>::workItem(CallObj& co)
{
    Q_.enQ(co);
   /* std::stringstream msg;
    msg << "\tthreadpool queue size = " << Utilities::Converter<size_t>::toString(Q_.size()) << "\n";
    std::cout << msg.str();*/
}

template <size_t numThreads>
void ThreadPool<numThreads>::wait()
{
    /*std::stringstream msg;
    msg << "\tentering wait with queue size = " << Utilities::Converter<size_t>::toString(Q_.size()) << "\n";
    std::cout << msg.str();*/

    for (auto& thrd : threads_)
        thrd.join();
    Q_.clear();
    /* msg << "\tleaving wait with queue size = " << Utilities::Converter<size_t>::toString(Q_.size()) << "\n";
    std::cout << msg.str();*/

}

template<size_t numThreads>
ThreadPool<numThreads>::~ThreadPool()
{
    for (auto& thrd : threads_)
    {
        if (thrd.joinable())
            thrd.join();
    }
}


/*

#ifndef COMM_CHANNEL_H
#define COMM_CHANNEL_H

#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class CommChannel {
public:
    CommChannel(int port);
    ~CommChannel();

    void startServer();
    void sendMessage(const std::string& message);
    std::string receiveMessage();

private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
    std::condition_variable condition;

    void handleClient();
};

#endif

//commchannel.cpp
#include "CommChannel.h"
#include <iostream>

CommChannel::CommChannel(int port)
    : acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      socket(io_context) {}

CommChannel::~CommChannel() {
    io_context.stop();
}

void CommChannel::startServer() {
    std::thread([this]() { io_context.run(); }).detach();
    acceptor.async_accept(socket, [this](boost::system::error_code ec) {
        if (!ec) {
            handleClient();
        }
    });
}

void CommChannel::sendMessage(const std::string& message) {
    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}

std::string CommChannel::receiveMessage() {
    std::unique_lock<std::mutex> lock(queueMutex);
    condition.wait(lock, [this]() { return !messageQueue.empty(); });

    std::string message = messageQueue.front();
    messageQueue.pop();
    return message;
}

void CommChannel::handleClient() {
    std::array<char, 1024> buffer;
    boost::system::error_code ec;

    while (true) {
        size_t length = socket.read_some(boost::asio::buffer(buffer), ec);
        if (ec) break;

        std::string message(buffer.data(), length);
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.push(message);
        }
        condition.notify_one();
    }
}


*/