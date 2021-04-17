#include "test_knight.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace KnightTests {


CHESS_DEFINE_TEST(BlankTest)
{

}

}

CHESS_TEST_LIST(KnightTestSuite)
{
    CHESS_TEST_LIST_ITEM(KnightTests::BlankTest);
}


}
