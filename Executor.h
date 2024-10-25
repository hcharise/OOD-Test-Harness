#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include "ResultLog.h"

class Executor {
    public:
        Executor();
        Executor(vector< vector< void* > > functionParams, vector< void* > functionExpects);
        void execute();
        void assess();
        ResultLog packageResults();
    private:

};

#endif 