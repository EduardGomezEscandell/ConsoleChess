#include "test_king.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace KingTests {


CHESS_DEFINE_TEST(Movement)
{
    Board board;
    Piece * king = board.CreatePieceInLocation(PieceSet::KING, 5, 5, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::KNIGHT, 6, 6, Colour::WHITE); // Knight to obstruct

    std::vector<Move> expected_moves = {{5,5,4,4},
                                        {5,5,4,5},
                                        {5,5,4,6},
                                        {5,5,5,4},
                                        {5,5,5,6},
                                        {5,5,6,4},
                                        {5,5,6,5},
                                       };
    king->UpdateLegalMoves();
    const auto & moves = king->GetMoves();
    this->AssertEqualContainers(moves, expected_moves, "King movement incorrect");

}

CHESS_DEFINE_TEST(Notation)
{
    King white_king = King(1,1,nullptr, Colour::WHITE);
    King black_king = King(1,1,nullptr, Colour::BLACK); // dark knight
    char c;

    c = white_king.GetPieceCharacter();
    this->AssertEqual(c, 'K', "Incorrect notation for white knight");

    c = black_king.GetPieceCharacter();
    this->AssertEqual(c, 'k', "Incorrect notation for black knight");
}


}

CHESS_TEST_LIST(KingTestSuite)
{
    CHESS_TEST_LIST_ITEM(KingTests::Movement);
    CHESS_TEST_LIST_ITEM(KingTests::Notation);
}


}
