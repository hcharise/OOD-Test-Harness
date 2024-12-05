///////////////////////////////////////////////////////////////////////
// Utilities.cpp - small, generally usefule, helper classes          //
// ver 1.2                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

#include <cctype>
#include <iostream>
#include "Utilities.h"

using namespace Utilities;

std::function<void(const std::string&)> Title =
[](auto src) { StringHelper::Title(src, '='); };

std::function<void(const std::string&)> title =
[](auto src) { StringHelper::Title(src, '-'); };

void StringHelper::title(const std::string& src)
{
    std::cout << "\n  " << src;
    std::cout << "\n " << std::string(src.size() + 2, '-');
}

void StringHelper::Title(const std::string& src, char underline)
{
    std::cout << "\n  " << src;
    std::cout << "\n " << std::string(src.size() + 2, underline);
}

std::vector<std::string> StringHelper::split(const std::string& src)
{
    std::vector<std::string> accum;
    std::string temp;
    size_t index = 0;
    do
    {
        while ((isspace(src[index]) || src[index] == ',') && src[index] != '\n')
        {
            ++index;
            if (temp.size() > 0)
            {
                accum.push_back(temp);
                temp.clear();
            }
        }
        if (src[index] != '\0')
            temp += src[index];
    } while (index++ < src.size());
    if (temp.size() > 0)
        accum.push_back(temp);
    return accum;
}

void Utilities::putline()
{
    std::cout << "\n";
}
