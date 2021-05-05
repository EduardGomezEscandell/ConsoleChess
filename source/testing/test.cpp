#include "test.h"

namespace ConsoleChess {


TestReport Test::Run() const
{
    {
        try
        {
            RunTest();
        }
        catch(const TestFailure & e)
        {
            return TestReport(Result::FAILURE, this->GetName(), e.what());
        }
        catch(const std::logic_error & e)
        {
            return TestReport(Result::ERROR, this->GetName(), e.what());
        }
        catch(const std::runtime_error & e)
        {
            return TestReport(Result::ERROR, this->GetName(), e.what());
        }
        catch(const ChessError & e)
        {
            return TestReport(Result::ERROR, this->GetName(), e.what());
        }
        catch(const std::exception & e)
        {
            return TestReport(Result::ERROR, this->GetName(), "No message");
        }
    };

    return TestReport(this->GetName());
}

}
