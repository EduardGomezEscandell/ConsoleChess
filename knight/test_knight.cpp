#include "test_knight.h"
#include "../board.h"

namespace ConsoleChess {


namespace KnightTests {


CHESS_DEFINE_TEST(BlankTest)
{

}

}

KnightTestSuite::KnightTestSuite(const Verbosity & verbosity) : TestSuite(verbosity)
{
    mTests.emplace_back(new KnightTests::BlankTest());
}


}
