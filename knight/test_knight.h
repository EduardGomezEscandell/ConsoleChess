#ifndef TESTKNIGHT_H
#define TESTKNIGHT_H

#include "../defines.h"
#include "knight.h"
#include "../testing/test_suite.h"
#include <memory>


namespace ConsoleChess {

////////////////// TEST SUITE ///////////////////////////////

class KnightTestSuite : public TestSuite
{
public:
    KnightTestSuite(const Verbosity & verbosity);

    const char * GetName() const override
    {
        return "KnightTestSuite";
    }
};


}

#endif // TESTKNIGHT_H
