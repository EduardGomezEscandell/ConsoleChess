#ifndef TESTER_H
#define TESTER_H

#include "test_suite.h"
#include <vector>

namespace ConsoleChess {

class Tester
{
public:
    Tester(const Verbosity & verbosity);
    Tester(const Tester &) = delete;

    void Run();

protected:
    std::vector<std::unique_ptr<TestSuite>> mTestSuites;
    const Verbosity mVerbosity;


    void Print(const Verbosity & minimum_verbosity, const char * message) const;
    void Print(const Verbosity & minimum_verbosity, const std::string & message) const;
};

}

#endif // TESTER_H
