#include <string>
#include <iostream>
#include <thread>
#include <algorithm>

#include "ThreadPool.h"
#include "TestHarness.h"
#include "ResultLog.h"
#include "reciver.h"
#include "Message.h"

using std::vector;
using std::thread;
using std::cout;
using std::endl;

std::vector<ResultLog> results; // Shared vector that holds results from executors

// Constructor - checks that vector is non-empty, creates executor object for each test
TestHarness::TestHarness(vector<const wchar_t*> libraries) {
    if (libraries.empty()) throw std::invalid_argument("No libraries passed in.");

    // CHANGE THIS to iterate through libraries and update executor() construction with params
    for (const wchar_t* library : libraries) {
        Executor executor(library);
        executors.push_back(executor);
    }
}

// Creates threadpool and passes in all tests to be run
void TestHarness::runAllTests() {

    // Create threadpool
    ThreadPool<4> trpl;

    cout << "-------- Threadpool started.. --------\n";

    // Declare a callable object for each executor
    for (auto executor : executors) {
        ThreadPool<4>::CallObj co = [&trpl, executor]() mutable ->bool {

            // Threadsafe printout indicating which test is being run by which thread
            std::stringstream msg;
            msg << "Thread " << Utilities::Converter<thread::id>::toString(std::this_thread::get_id()) << " running test " << executor.testID << "\n";
            std::cout << msg.str();

            std::string message;
            getMessage(message);
            // std::cout << message << std::endl;
            try {
                Message msg = Message::deserialize(message);
                std::cout << "Received Message:\n"
                    << "Source: " << msg.getSource() << "\n"
                    << "Destination: " << msg.getDestination() << "\n"
                    << "Type: " << msg.getType() << "\n"
                    << "Author: " << msg.getAuthor() << "\n"
                    << "Timestamp: " << msg.getTimeStamp() << "\n"
                    << "Body: " << msg.getBody() << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error deserializing message: " << e.what() << "\n";
            }

            // Run the test
            executor.execute();

            return true; // True tells the thread to continue taking tasks
        };

        // Add new callable object to blocking queue that threads pull tasks from
        trpl.workItem(co);
    }

    // Send "exit" task and wait for all tasks in threadpool to complete
    ThreadPool<4>::CallObj exit = []() ->bool { return false; };
    trpl.workItem(exit);
    trpl.wait();

    cout << "-------- Threadpool complete! --------\n\n";

}

// Prints header/footer and the result log for each test run
void TestHarness::printOutResults(LogLevel logLevel) {

    cout << "------------ TEST RESULTS ------------\n" << endl;

    for (auto result : results) {
        cout << result.getLogDetails(logLevel, Executor::numOfTests);
    }

    cout << "----------- End of Results -----------" << endl;
}