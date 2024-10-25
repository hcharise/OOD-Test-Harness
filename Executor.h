#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include "ResultLog.h"

class Executor {
    public:
        Executor(vector<void *> functionParams, void *functionAssert);
        void execute();
        void assess();
        ResultLog packageResults();
    private:

};

#endif 