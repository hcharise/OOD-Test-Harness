#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <functional>
#include <string>

#include "ResultLog.h"

class Executor {
    public:
        Executor(std::function<bool()>);
        void execute();
        ResultLog packageResults();
        static int numOfTests;
        int testID;
    private:
        std::function<bool()> test;
        bool result;
        std::string errorMessage;
};

#endif 