#include <iostream>
#include "Executor.h"
using std::vector;

Executor::Executor(std::function<bool()> test)
    : test(test)
{}

void Executor::execute() {
    try {
        std::cout << "Test: " << test() << std::endl;

    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    // need to save results of testFunction and call assess?
}

ResultLog Executor::packageResults() {
    return ResultLog();
}