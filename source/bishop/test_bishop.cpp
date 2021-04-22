#include "test_bishop.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace BishopTests {

CHESS_DEFINE_TEST(Movement)
{
    Board board;
    Piece * bishop = board.CreatePieceInLocation(PieceSet::BISHOP, 3,3, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::KNIGHT, 5, 5, Colour::WHITE); // Knight to obstruct
    board.CreatePieceInLocation(PieceSet::KNIGHT, 4, 2, Colour::BLACK); // Knight to capture

    std::vector<Move> expected_moves = {// A1 - H8 diagonal
                                        {3,3,0,0},
                                        {3,3,1,1},
                                        {3,3,2,2},
                                        {3,3,4,4},
                                        // G1 - A7 diagonal
                                        {3,3,0,6},
                                        {3,3,1,5},
                                        {3,3,2,4},
                                        {3,3,4,2},
                                       };
    bishop->UpdateLegalMoves();
    const auto & moves = bishop->GetMoves();
    this->AssertEqualContainers(moves, expected_moves, "Bishop non-castling moves incorrect.");
}

CHESS_DEFINE_TEST(Notation)
{
    Bishop white_bishop = Bishop(1,1,nullptr, Colour::WHITE);
    Bishop black_bishop = Bishop(1,1,nullptr, Colour::BLACK); // dark knight
    char c;

    c = white_bishop.GetPieceCharacter();
    this->AssertEqual(c, 'B', "Incorrect notation for white bishop");

    c = black_bishop.GetPieceCharacter();
    this->AssertEqual(c, 'b', "Incorrect notation for black bishop");
}



}

CHESS_TEST_LIST(BishopTestSuite)
{
    CHESS_TEST_LIST_ITEM(BishopTests::Movement);
    CHESS_TEST_LIST_ITEM(BishopTests::Notation);
}


}
