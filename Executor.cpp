#include <iostream>
#include <iomanip>
#include "Executor.h"

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
    // Need to modify to pass result to resultLog once built out
    std::cout << "Test: " << result << std::endl;
    return ResultLog();
}