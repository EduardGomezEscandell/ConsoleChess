#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <vector>
#include <map>
#include <memory>

#include "test.h"
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

#define CHESS_DEFINE_TEST_SUITE(name)               \
class name : public TestSuite                       \
{                                                   \
public:                                             \
    name(const Verbosity & verbosity);              \
                                                    \
    const char * GetName() const override           \
    {                                               \
        return #name;                               \
    }                                               \
};                                                  \

#define CHESS_TEST_LIST(suite_name)                 \
suite_name::suite_name(const Verbosity & verbosity) \
    : TestSuite(verbosity)

#define CHESS_TEST_LIST_ITEM(test_name)             \
mTests.emplace_back(new test_name());

namespace ConsoleChess {



class TestSuite
{
public:
    TestSuite(const Verbosity & verbosity);
    Result Run(std::vector<TestReport> & rReportList);

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
