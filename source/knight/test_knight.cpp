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
    Piece * knight = board.CreatePieceInLocation(PieceSet::KNIGHT, 0, 0, Colour::BLACK);


    std::vector<Move> expected_moves = {{0,0,2,1},
                                        {0,0,1,2}
                                       };

    // Making sure it does not move outside the board
    knight->UpdateLegalMoves();
    this->AssertEqualContainers(knight->GetMoves(), expected_moves, "Unconstrained movement incorrect");

    expected_moves.clear();
    expected_moves.emplace_back(0,0,2,1);

    board.CreatePieceInLocation(PieceSet::KNIGHT, 1,2, Colour::BLACK);
    // Making sure it does not land in an occupied square
    knight->UpdateLegalMoves();
    this->AssertEqualContainers(knight->GetMoves(), expected_moves, "Movement constrained by occupied squares incorrect");

    for(const Move & m : knight->GetMoves())
    {   
        Square & s = board.GetSquare(m.landing_rank, m.landing_file);
        bool is_attacked = s.IsAttackedBy(knight->GetColour());
        std::stringstream ss;
        ss << "Knight available square is not attacked (" << s.GetName() << ")" <<std::endl;
        this->AssertTrue(is_attacked, ss.str());
    }
}

CHESS_DEFINE_TEST(Notation)
{
    Knight white_knight = Knight(1,1,nullptr, Colour::WHITE);
    Knight batman = Knight(1,1,nullptr, Colour::BLACK); // dark knight
    char c;

    c = white_knight.GetPieceCharacter();
    this->AssertEqual(c, 'N', "Incorrect notation for white knight");

    c = batman.GetPieceCharacter();
    this->AssertEqual(c, 'n', "Incorrect notation for black knight");
}

}
CHESS_TEST_LIST(KnightTestSuite)
{
    CHESS_TEST_LIST_ITEM(KnightTests::Constructor);
    CHESS_TEST_LIST_ITEM(KnightTests::Movement);
    CHESS_TEST_LIST_ITEM(KnightTests::Notation);
}


}
