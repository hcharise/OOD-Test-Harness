#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "ResultLog.h"
#include <functional>
#include <string>

class Executor {
    public:
        Executor(std::function<bool()>);
        void execute(int testIndex);
        ResultLog packageResults();
        static int numOfTests;
    private:
        std::function<bool()> test;
        int testID;
        bool result;
        std::string errorMessage;
};

#endif 