#ifndef TEST_H
#define TEST_H

#include<iostream>
#include <cstring>
#include <exception>
#include <sstream>
#include <algorithm>
#include "../defines.h"

namespace ConsoleChess {

class TestFailure : public std::exception
{
public:
    TestFailure(const char * msg){
        mMessage = std::string(msg);
    };

    TestFailure(const std::string & msg)  : mMessage(msg) {};

    const char * what () const throw ()
    {
        return mMessage.c_str();
    }

protected:
    std::string mMessage;
};


struct TestReport
{
    TestReport(const char * test_name) : TestReport(Result::SUCCESS, test_name, "") {};

    TestReport(const Result & result, const char * test_name, const char * msg) :
        mResult(result), mTestName(test_name), mMessage(msg)
    {};

    TestReport(const Result & result, const char * test_name, const std::string & msg) :
        mResult(result), mTestName(test_name), mMessage(msg)
    {};

    void AddSuiteName(const char * suite_name)
    {
        mSuiteName = suite_name;
    }

    Result mResult;
    const char * mTestName;
    const char * mSuiteName;
    const std::string mMessage;
};


class Test
{
public:
    TestReport Run() const;
    virtual const char * GetName() const = 0;

protected:
    virtual void RunTest() const = 0;
    Test() {}

    template<typename T, typename U>
    void AssertEqual(const T & t, const U & u, const char * msg = "") const
    {
        if(t == u) return;

        std::stringstream ss;
        ss << "Comparisson error: " << t << " is not equal to " << u;
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

    template<typename T>
    void AssertTrue(const T & t, const char * msg = "") const
    {
        if(t) return;

        std::stringstream ss;
        ss << "Truth error: " << t << " is not true";
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

    template<typename T1, typename T2>
    void AssertEqualContainers(const T1 & c1, const T2 & c2, const char * msg = "") const
    {
        if(c1.size() != c2.size())
        {
            std::stringstream ss;
            ss << "Containers have different size: " << c1.size() << " versus " << c2.size() <<".";
            if(msg[0] != '\0')
            {
                ss << "\n" << msg;
            }
            throw TestFailure(ss.str());
        }

        for(const auto & e : c1)
        {
            auto r = std::find(c2.begin(), c2.end(), e);

            if(r == c2.end())
            {
                std::stringstream ss;
//                ss << "Object" << e << "in container 1 not present in container 2.";
                if(msg[0] != '\0')
                {
                    ss << "\n" << msg;
                }
                throw TestFailure(ss.str());
            }
        }

        for(const auto & e : c2)
        {
            auto r = std::find(c1.begin(), c1.end(), e);

            if(r == c1.end())
            {
                std::stringstream ss;
//                ss << "Object" << e << "in container 2 not present in container 1.";
                if(msg[0] != '\0')
                {
                    ss << "\n" << msg;
                }
                throw TestFailure(ss.str());
            }
        }

    }

};

}

#endif // TEST_H