#include "test_suite.h"
#include <iostream>

namespace ConsoleChess {


TestSuite::TestSuite(const Verbosity & verbosity)
    :   mVerbosity(verbosity)
{
}

void TestSuite::Run(std::vector<TestReport> & rReportList)
{
    char buffer[512];
    sprintf(buffer, "Running %s: ", this->GetName());
    this->Print(Verbosity::FULL, buffer);

    for(auto & test: mTests)
    {
        TestReport r = test->Run();
        r.AddSuiteName(this->GetName());

        switch (r.mResult)
        {
        case Result::SUCCESS:
            this->Print(Verbosity::PROGRESS, ".");
            rReportList.push_back(r);
            break;

        case Result::FAILURE:
            this->Print(Verbosity::PROGRESS, "x");
            rReportList.push_back(r);
            break;

        case Result::ERROR:
            this->Print(Verbosity::PROGRESS, "e");
            rReportList.push_back(r);
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
