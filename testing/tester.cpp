#include <iostream>
#include "tester.h"
#include "../knight/test_knight.h"

namespace ConsoleChess {

Tester::Tester(const Verbosity & verbosity) :
    mVerbosity(verbosity)
{
    mTestSuites.emplace_back(new KnightTestSuite(mVerbosity));
}

void Tester::Print(const Verbosity & minimum_verbosity, const char * message) const
{
    if(this->mVerbosity < minimum_verbosity) return;

    std::cout << message;
}

void Tester::Run()
{
    this->Print(Verbosity::NONE, "Running tests\n");
    for(auto & suite : mTestSuites)
    {
        suite->Run();
    }
}

}
