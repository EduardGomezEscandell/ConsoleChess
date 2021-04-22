#include "test_suite.h"
#include <iostream>

namespace ConsoleChess {


TestSuite::TestSuite(const Verbosity & verbosity)
    :   mVerbosity(verbosity)
{
}

Result TestSuite::Run(std::vector<TestReport> & rReportList)
{
    char buffer[512];
    sprintf(buffer, "Running %s: ", this->GetName());
    this->Print(Verbosity::PROGRESS, buffer);
    Result suite_result = Result::SUCCESS;

    for(auto & test: mTests)
    {
        TestReport r = test->Run();
        r.AddSuiteName(this->GetName());

        switch (r.mResult)
        {
        case Result::SUCCESS:
            this->Print(Verbosity::NONE, ".");
            rReportList.push_back(r);
            break;

        case Result::FAILURE:
            this->Print(Verbosity::NONE, "x");
            rReportList.push_back(r);
            if(suite_result == Result::SUCCESS) suite_result = Result::FAILURE;
            break;

        case Result::ERROR:
            this->Print(Verbosity::NONE, "e");
            rReportList.push_back(r);
            suite_result = Result::ERROR;
            break;
        }
    }
    this->Print(Verbosity::PROGRESS, "\n");
    return suite_result;
}

void TestSuite::Print(const Verbosity & minimum_verbosity, const char * message) const
{
    if(this->mVerbosity < minimum_verbosity) return;

    std::cout << message;
}



}
