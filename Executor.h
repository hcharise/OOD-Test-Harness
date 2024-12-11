#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <functional>
#include <string>
#include <codecvt>
#include <locale>

#include "ResultLog.h"

typedef bool (*funcTestDriver)();


class Executor {
    public:
        Executor(const wchar_t* libTag);
        void execute();
        bool runDLL();
        ResultLog packageResults();
        static int numOfTests;
        int testID;
        std::string getStringLibTag();
    private:
        const wchar_t* libTag;
        bool result;
        std::string errorMessage;
};

#endif 