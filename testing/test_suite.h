#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <vector>
#include <map>
#include <memory>
#include "../defines.h"

enum class Verbosity;

/**
 * Macro to define tests without all the boilerplate
 */
#define CHESS_DEFINE_TEST(name)                     \
class name : public Test                            \
{                                                   \
public:                                             \
    name() : Test() {};                             \
                                                    \
    const char * GetName() const override           \
    {                                               \
        return #name;                               \
    }                                               \
protected:                                          \
    void RunTest() const override;                  \
};                                                  \
                                                    \
void name::RunTest() const                          \




namespace ConsoleChess {


class TestFailure : public std::exception
{
public:
    TestFailure(const char * msg)  : message(msg) {};
    const char * what () const throw ()
    {
        return message;
    }
protected:
    const char * message;
};


struct TestReport
{
    TestReport(const char * test_name) : TestReport(Result::SUCCESS, test_name, nullptr) {};
    TestReport(const Result & result, const char * test_name, const char * msg) :
        mResult(result), mTestName(test_name), mMessage(msg)
    {};

    void AddSuiteName(const char * suite_name)
    {
        mSuiteName = suite_name;
    }

    Result mResult;
    const char * mTestName;
    const char * mSuiteName;
    const char * mMessage;
};


class Test
{
public:
    TestReport Run() const;

    virtual const char * GetName() const = 0;

protected:
    virtual void RunTest() const = 0;
    Test() {}
};


class TestSuite
{
public:
    TestSuite(const Verbosity & verbosity);
    void Run(std::vector<TestReport> & rReportList);

    template<typename TTestType>
    void AddTest()
    {
        mTests.emplace_back(new TTestType());
    }

    virtual const char * GetName() const = 0;

protected:
    void Print(const Verbosity & minimum_verbosity, const char * message) const;

    const Verbosity mVerbosity;
    std::vector<std::unique_ptr<Test>> mTests;
};

}

#endif // TESTSUITE_H
