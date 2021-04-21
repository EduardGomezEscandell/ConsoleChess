#include "test_knight.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace KnightTests {


CHESS_DEFINE_TEST(Constructor)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KNIGHT, 0, 0, Colour::BLACK);
}

CHESS_DEFINE_TEST(Movement)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KNIGHT, 0, 0, Colour::BLACK);
    Piece * piece = board.pGetSquareContent(0,0);


    std::vector<Move> expected_moves = {{0,0,2,1},
                                        {0,0,1,2}
                                       };

    // Making sure it does not move outside the board
    piece->UpdateLegalMoves();
    this->AssertEqualContainers(piece->GetMoves(), expected_moves, "Unconstrained movement incorrect");

    expected_moves.clear();
    expected_moves.emplace_back(0,0,2,1);

    board.CreatePieceInLocation(PieceSet::KNIGHT, 1,2, Colour::BLACK);
    // Making sure it does not land in an occupied square
    piece->UpdateLegalMoves();
    this->AssertEqualContainers(piece->GetMoves(), expected_moves, "Movement constrained by occupied squares incorrect");


}

}

CHESS_TEST_LIST(KnightTestSuite)
{
    CHESS_TEST_LIST_ITEM(KnightTests::Constructor);
    CHESS_TEST_LIST_ITEM(KnightTests::Movement);
}


}
