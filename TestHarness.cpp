#include "TestHarness.h"
#include "ResultLog.h"
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include "ThreadPool.h"
#include "Sockets.h"

using std::vector;
using std::thread;
using std::cout;
using std::endl;

std::vector<ResultLog> results;

/*
class ClientHandler {
public:
    void operator()(Sockets::Socket clientSocket) {
        std::string msg = clientSocket.recvString();  // Receive message from client
        std::cout << "Server received: " << msg << std::endl;
        clientSocket.sendString("Hello from Server!");  // Send response to client
    }
};
*/


// Constructor - checks that vector is non-empty
TestHarness::TestHarness(vector<std::function<bool()>> tests) {
    if (tests.empty()) throw std::invalid_argument("No tests passed in.");

    for (auto test : tests) {
        Executor executor(test);
        executors.push_back(executor);
    }

    /*
    Sockets::SocketSystem socketSystem;

    // Set up the server
    int port = 8080;
    Sockets::SocketListener listener(port, Sockets::Socket::IP4);
    ClientHandler handler;
    listener.start(handler);  // Start the server listening for connections

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Server is listening on port " << port << "...\n";
    */
    
}

// Creates and runs executor for each lambda in tests vector
void TestHarness::runAllTests() {
    ThreadPool<3> trpl;
    int testNum = 0;

    cout << "-------- Threadpool started.. --------\n";


    for (auto executor : executors) {
        testNum++;

        ThreadPool<3>::CallObj co = [&trpl, executor, testNum]() mutable ->bool {
            std::stringstream msg;
            msg << "Thread " << Utilities::Converter<thread::id>::toString(std::this_thread::get_id()) << " running test " << testNum << "\n";
            std::cout << msg.str();

            executor.execute(testNum);

            return true;
        };
        trpl.workItem(co);
    }

    ThreadPool<3>::CallObj exit = []() ->bool { return false; };
    trpl.workItem(exit);
    trpl.wait();

    cout << "-------- Threadpool complete! --------\n\n";


}

// Prints header/footer and the result log for each test run
void TestHarness::printOutResults(LogLevel logLevel) {

   
    cout << "------------ TEST RESULTS ------------\n" << endl;

    for (auto result : results) {
        cout << result.getLogDetails(LogLevel::TEST_SPECIFIC);
    }

    cout << "----------- End of Results -----------\n" << endl;

}

