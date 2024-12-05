///////////////////////////////////////////////////////////////
// Cpp11-BlockingQueue.cpp - Thread-safe Blocking Queue      //
// ver 1.3                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2013 //
///////////////////////////////////////////////////////////////

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include "Cpp11-BlockingQueue.h"

#ifndef TEST_BLOCKINGQUEUE
#define TEST_BLOCKINGQUEUE

std::mutex ioLock;

void test(BlockingQueue<std::string>* pQ)
{
    std::string msg;
    do
    {
        msg = pQ->deQ();
        {
            std::lock_guard<std::mutex> l(ioLock);
            std::cout << "\n  thread deQed " << msg.c_str();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while (msg != "quit");
}

#endif