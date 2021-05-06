#include "test_rook.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace RookTests {

CHESS_DEFINE_TEST(Movement)
{
    Board board;
    Piece * rook = board.CreatePieceInLocation(PieceSet::ROOK, 3,3, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::KNIGHT, 3, 6, Colour::WHITE); // Knight to obstruct
    board.CreatePieceInLocation(PieceSet::BISHOP, 5, 3, Colour::BLACK); // Bishop to capture

    std::vector<Move> expected_moves = {{3,3,0,3},
                                        {3,3,1,3},
                                        {3,3,2,3},
                                        {3,3,4,3},
                                        {3,3,5,3},
                                        {3,3,3,0},
                                        {3,3,3,1},
                                        {3,3,3,2},
                                        {3,3,3,4},
                                        {3,3,3,5}
                                       };
    rook->UpdateLegalMoves();
    const auto & moves = rook->GetMoves();
    AssertEqualContainers(moves, expected_moves, "Rook non-castling moves incorrect.");

    for(const Move & m : moves)
    {   
        Square & s = board.GetSquare(m.GetLandingRank(), m.GetLandingFile());
        bool is_attacked = s.IsAttackedBy(rook->GetColour());
        std::stringstream ss;
        ss << "Rook available square is not attacked (" << s.GetName() << ")" <<std::endl;
        AssertTrue(is_attacked, ss.str());
    }
}

CHESS_DEFINE_TEST(Notation)
{
    Rook white_rook = Rook(1,1,nullptr, Colour::WHITE);
    Rook black_rook = Rook(1,1,nullptr, Colour::BLACK);
    char c;

    c = white_rook.GetPieceCharacter();
    AssertEqual(c, 'R', "Incorrect notation for white rook");

    c = black_rook.GetPieceCharacter();
    AssertEqual(c, 'r', "Incorrect notation for black rook");
}



}

CHESS_TEST_LIST(RookTestSuite)
{
    CHESS_TEST_LIST_ITEM(RookTests::Movement);
    CHESS_TEST_LIST_ITEM(RookTests::Notation);
}


}
