#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include "ResultLog.h"
using std::vector;

class Executor {
    public:
        Executor(void* testFunction, vector<void *> functionParams, void *functionAssert);
        void execute();
        void assess();
        ResultLog packageResults();
    private:

};

#endif 