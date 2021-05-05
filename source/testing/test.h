#ifndef TEST_H
#define TEST_H

#include<iostream>
#include <cstring>
#include <exception>
#include <sstream>
#include <algorithm>
#include <regex>

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

    template<typename T, typename Tstring=const char *>
    static void AssertTrue(const T& t, const Tstring& msg = "")
    {
        if(t) return;

        std::stringstream ss;
        ss << "AssertTrue error: " << t << " does not evaluate to true";
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

    template<typename T, typename U, typename Tstring=const char *>
    static void AssertEqual(const T & t, const U & u, const Tstring& msg = "")
    {
        if(t == u) return;

        std::stringstream ss;
        ss << "AssertEqual error: " << t << " is not equal to " << u;
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

    template<typename T, typename U, typename Tstring=const char *>
    static void AssertDifferent(const T & t, const U & u, const Tstring& msg = "")
    {
        if(!(t == u)) return;

        std::stringstream ss;
        ss << "AssertDifferent error: " << t << " is equal to " << u;
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

    template<typename T, typename Tstring=const char *>
    static void AssertFalse(const T & t, const Tstring& msg = "")
    {
        if(!t) return;

        std::stringstream ss;
        ss << "AssertFalse error: " << t << " is not false";
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

    template<typename T1, typename T2, typename Tstring=const char *>
    static void AssertEqualContainers(const T1 & c1, const T2 & c2, const Tstring& msg = "")
    {
        if(c1.size() != c2.size())
        {
            std::stringstream ss;
            ss << "AssertEqualContainers error: Containers have different size: " << c1.size() << " versus " << c2.size() <<".";
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
                ss << "AssertEqualContainers error: Object " << e << " in container 1 not present in container 2.";
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
                ss << "AssertEqualContainers error: Object " << e << " in container 2 not present in container 1.";
                if(msg[0] != '\0')
                {
                    ss << "\n" << msg;
                }
                throw TestFailure(ss.str());
            }
        }

    }

    template<typename TExceptionType, typename TLambdaType, typename Tstring=const char *>
    const static TExceptionType AssertRaises(TLambdaType && f, Tstring msg = "")
    {
        try
        {
            f();

            std::stringstream ss;
            ss << "AssertRaises error: Expected exception was not thrown.";
            if(msg[0] != '\0')
            {
                ss << "\n" << msg;
            }
            throw TestFailure(ss.str());
        }
        catch(const TExceptionType & e)
        {
            return e;
        }
    }

    template<typename Tstring=const char *>
    static void AssertRegex(const std::string & str, const std::string & regex_str, const Tstring& msg = "")
    {
        std::unique_ptr<std::regex> regex;
        try
        {
            regex = std::make_unique<std::regex>(regex_str);
        }
        catch(const std::runtime_error & e)
        {
            CHESS_THROW << "Runtime error while parsing regex {" << regex_str << "}:\n    " << e.what();
        }
        
        if(std::regex_match(str, *regex)) return;

        std::stringstream ss;
        ss << "AssertRegex error: {" << str << "} does not match { " << regex_str << " }";
        if(msg[0] != '\0')
        {
            ss << "\n" << msg;
        }

        throw TestFailure(ss.str());
    }

};

}

#endif // TEST_H
