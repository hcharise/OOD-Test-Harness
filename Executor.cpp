#include <iostream>
#include <iomanip>
#include "Executor.h"
using std::vector;

Executor::Executor(std::function<bool()> test)
    : test(test)
{}

void Executor::execute() {

    std::cout << std::boolalpha;

    try {
        result = test();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

ResultLog Executor::packageResults() {
    // Can delete once results log is built out
    std::cout << "Test: " << result << std::endl;
    return ResultLog();
}