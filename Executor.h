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
        bool result;
    private:
        std::function<bool()> test;
        std::string errorMessage;
};

#endif 