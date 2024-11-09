#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "ResultLog.h"
#include <functional>
#include <string>

class Executor {
    public:
        Executor(std::function<bool()>);
        void execute();
        ResultLog packageResults();
    private:
        std::function<bool()> test;
        bool result;
        std::string errorMessage;
        const int testNum;
        static int totalNumTests;
};

#endif 