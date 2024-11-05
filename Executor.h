#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "ResultLog.h"
#include <functional>

class Executor {
    public:
        Executor(std::function<bool()>);
        void execute();
        ResultLog packageResults();
    private:
        std::function<bool()> test;
        bool result;
        static int testNum; // do this next!
};

#endif 