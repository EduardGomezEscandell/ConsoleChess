#include "test_rook.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace RookTests {

CHESS_DEFINE_TEST(Movement)
{
    Board board;
    Piece * rook = board.CreatePieceInLocation(PieceSet::ROOK, 3,3, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::KNIGHT, 3, 6, Colour::WHITE); // Knight to obstruct

    std::vector<Move> expected_moves = {{3,3,0,3},
                                        {3,3,1,3},
                                        {3,3,2,3},
                                        {3,3,4,3},
                                        {3,3,5,3},
                                        {3,3,6,3},
                                        {3,3,7,3},
                                        {3,3,3,0},
                                        {3,3,3,1},
                                        {3,3,3,2},
                                        {3,3,3,4},
                                        {3,3,3,5}
                                       };
    rook->UpdateLegalMoves();
    const auto & moves = rook->GetMoves();
    this->AssertEqualContainers(moves, expected_moves, "Rook non-castling moves incorrect.");
}

CHESS_DEFINE_TEST(Notation)
{
    Rook white_rook = Rook(1,1,nullptr, Colour::WHITE);
    Rook black_rook = Rook(1,1,nullptr, Colour::BLACK); // dark knight
    char c;

    c = white_rook.GetPieceCharacter();
    this->AssertEqual(c, 'R', "Incorrect notation for white knight");

    c = black_rook.GetPieceCharacter();
    this->AssertEqual(c, 'r', "Incorrect notation for black knight");
}



}

CHESS_TEST_LIST(RookTestSuite)
{
    CHESS_TEST_LIST_ITEM(RookTests::Movement);
    CHESS_TEST_LIST_ITEM(RookTests::Notation);
}


}
