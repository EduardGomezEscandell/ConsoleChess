#include "test.h"

namespace ConsoleChess {


TestReport Test::Run() const
{
    {
        try
        {
            RunTest();
        }
        catch(const TestFailure e)
        {
            return TestReport(Result::FAILURE, this->GetName(), e.what());
        }
        catch(const std::exception e)
        {
            return TestReport(Result::ERROR, this->GetName(), e.what());
        }
    };

    return TestReport(this->GetName());
}

}
