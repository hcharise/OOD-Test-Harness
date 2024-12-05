///////////////////////////////////////////////////////////////////////
// ThreadPool.cpp - Enqueue work items to run on one of a collection //
//                  of threads, created at startup.                  //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016         //
///////////////////////////////////////////////////////////////////////


#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include "ThreadPool.h"

//----< test stub >--------------------------------------------------

#ifndef TEST_THREADPOOL
#define TEST_THREADPOOL

#include <iostream>
using namespace std::chrono_literals;
using namespace Utilities;
using Utils = StringHelper;

#endif