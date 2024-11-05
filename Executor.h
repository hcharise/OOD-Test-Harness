#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include "ResultLog.h"
#include <functional>
using std::vector;

class Executor {
    public:
        Executor(std::function<bool()>);
        void execute();
        ResultLog packageResults();
    private:
        std::function<bool()> test;
        bool result;
        static int testNum;
};

#endif 