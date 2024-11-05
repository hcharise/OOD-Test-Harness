#include <iostream>
#include <iomanip>
#include "Executor.h"

int Executor::totalNumTests = 1;

Executor::Executor(std::function<bool()> test)
    : test(test), testNum(totalNumTests) {
    totalNumTests++;
}

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
    std::cout << "Test #" << testNum << ": " << result << std::endl;
    return ResultLog();
}