#include <iostream>
#include "tester.h"

#include "../knight/test_knight.h"
#include "../king/test_king.h"
#include "../rook/test_rook.h"
#include "../bishop/test_bishop.h"
#include "../queen/test_queen.h"
#include "../pawn/test_pawn.h"
#include "../board/test_board.h"
#include "../interface/test_interface.h"
#include "../algebraic_notation/test_algebraic.h"

namespace ConsoleChess {

Tester::Tester(const Verbosity & verbosity) :
    mVerbosity(verbosity)
{
    mTestSuites.emplace_back(new KnightTestSuite(mVerbosity));
    mTestSuites.emplace_back(new KingTestSuite(mVerbosity));
    mTestSuites.emplace_back(new RookTestSuite(mVerbosity));
    mTestSuites.emplace_back(new BishopTestSuite(mVerbosity));
    mTestSuites.emplace_back(new QueenTestSuite(mVerbosity));
    mTestSuites.emplace_back(new PawnTestSuite(mVerbosity));
    mTestSuites.emplace_back(new BoardTestSuite(mVerbosity));
    mTestSuites.emplace_back(new InterfaceTestSuite(mVerbosity));
    mTestSuites.emplace_back(new AlgebraicNotationTestSuite(mVerbosity));
}

void Tester::Print(const Verbosity & minimum_verbosity, const char * message) const
{
    if(this->mVerbosity < minimum_verbosity) return;

    std::cout << message;
}

void Tester::Print(const Verbosity & minimum_verbosity, const std::string & message) const
{
    if(this->mVerbosity < minimum_verbosity) return;

    std::cout << message;
}

void Tester::Run()
{
    mResult = Result::SUCCESS;

    this->Print(Verbosity::NONE, "Running tests\n");

    std::vector<TestReport> test_reports;

    for(auto & suite : mTestSuites)
    {
        suite->Run(test_reports);
    }

    this->Print(Verbosity::NONE, "\nTests completed.\n");

    for(auto & report: test_reports)
    {
        switch(report.mResult)
        {
        case Result::SUCCESS:
            this->Print(Verbosity::FULL, "Test ");
            this->Print(Verbosity::FULL, report.mSuiteName);
            this->Print(Verbosity::FULL, "/");
            this->Print(Verbosity::FULL, report.mTestName);
            this->Print(Verbosity::FULL, " was completed succesfully.\n");
            break;
        case Result::ERROR:
            this->Print(Verbosity::NONE, "\n----------------------------------\n");
            this->Print(Verbosity::NONE, "Test ");
            this->Print(Verbosity::NONE, report.mSuiteName);
            this->Print(Verbosity::NONE, "/");
            this->Print(Verbosity::NONE, report.mTestName);
            this->Print(Verbosity::NONE, " was erroneous. Exception message:\n");
            this->Print(Verbosity::NONE, report.mMessage);
            this->Print(Verbosity::NONE, "\n----------------------------------\n");
            mResult = report.mResult==Result::SUCCESS ? Result::ERROR : mResult;
            break;
        case Result::FAILURE:
            this->Print(Verbosity::NONE, "\n----------------------------------\n");
            this->Print(Verbosity::NONE, "Test ");
            this->Print(Verbosity::NONE, report.mSuiteName);
            this->Print(Verbosity::NONE, "/");
            this->Print(Verbosity::NONE, report.mTestName);
            this->Print(Verbosity::NONE, " failed. Exception message:\n");
            this->Print(Verbosity::NONE, report.mMessage);
            this->Print(Verbosity::NONE, "\n----------------------------------\n");
            mResult = report.mResult;
            break;
        }
    }
}

template<>
int Tester::GetResult<int>()
{
    return static_cast<int>(mResult);
}

template<>
Result Tester::GetResult<Result>()
{
    return mResult;
}

}
