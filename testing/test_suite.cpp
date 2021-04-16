#include "test_suite.h"
#include <iostream>

namespace ConsoleChess {


Test::Result Test::Run() const
{
    {
        try
        {
            RunTest();
        }
        catch(TestFailure)
        {
            return Result::FAILURE;
        }
        catch(...)
        {
            return Result::ERROR;
        }
    };

    return Result::SUCCESS;
}


TestSuite::TestSuite(const Verbosity & verbosity)
    :   mVerbosity(verbosity)
{
}

void TestSuite::Run() const
{
    char buffer[512];
    sprintf(buffer, "Running %s: ", this->GetName());
    this->Print(Verbosity::FULL, buffer);

    for(auto & test: mTests)
    {
        Test::Result r = test->Run();

        switch (r)
        {
        case Test::Result::SUCCESS:
            this->Print(Verbosity::PROGRESS, ".");
            break;

        case Test::Result::FAILURE:
            this->Print(Verbosity::PROGRESS, "x");
            break;

        case Test::Result::ERROR:
            this->Print(Verbosity::PROGRESS, "e");
            break;
        }
    }

    this->Print(Verbosity::FULL, "\n");
}

void TestSuite::Print(const Verbosity & minimum_verbosity, const char * message) const
{
    if(this->mVerbosity < minimum_verbosity) return;

    std::cout << message;
}



}
