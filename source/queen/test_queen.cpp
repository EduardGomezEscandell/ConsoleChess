#include "test_queen.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace QueenTests {

CHESS_DEFINE_TEST(Movement)
{
    Board board;
    Piece * Queen = board.CreatePieceInLocation(PieceSet::QUEEN, 3,3, Colour::WHITE); // Queen at D4
    board.CreatePieceInLocation(PieceSet::KNIGHT, 3, 6, Colour::WHITE); // Knight to obstruct at D7
    board.CreatePieceInLocation(PieceSet::BISHOP, 5, 3, Colour::BLACK); // Bishop to capture  at F4
    board.CreatePieceInLocation(PieceSet::KNIGHT, 5, 5, Colour::WHITE); // Knight to obstruct at F6
    board.CreatePieceInLocation(PieceSet::KNIGHT, 4, 2, Colour::BLACK); // Knight to capture  at E3

    std::vector<Move> expected_moves = {// 4th rank
                                        {3,3,0,3},
                                        {3,3,1,3},
                                        {3,3,2,3},
                                        {3,3,4,3},
                                        {3,3,5,3},
                                        // D file
                                        {3,3,3,0},
                                        {3,3,3,1},
                                        {3,3,3,2},
                                        {3,3,3,4},
                                        {3,3,3,5},
                                        // A1 - H8 diagonal
                                        {3,3,0,0},
                                        {3,3,1,1},
                                        {3,3,2,2},
                                        {3,3,4,4},
                                        // G1 - A7 diagonal
                                        {3,3,0,6},
                                        {3,3,1,5},
                                        {3,3,2,4},
                                        {3,3,4,2}};
    Queen->UpdateLegalMoves();
    const auto & moves = Queen->GetMoves();

    AssertEqualContainers(moves, expected_moves, "Queen moves incorrect.");

    for(const Move & m : moves)
    {   
        Square & s = board.GetSquare(m.GetLandingRank(), m.GetLandingFile());
        bool is_attacked = s.IsAttackedBy(Queen->GetColour());
        std::stringstream ss;
        ss << "Queen available square is not attacked (" << s.GetName() << ")" <<std::endl;
        AssertTrue(is_attacked, ss.str());
    }
}

CHESS_DEFINE_TEST(Notation)
{
    Queen white_queen = Queen(1,1,nullptr, Colour::WHITE);
    Queen black_queen = Queen(1,1,nullptr, Colour::BLACK);
    char c;

    c = white_queen.GetPieceCharacter();
    AssertEqual(c, 'Q', "Incorrect notation for white queen");

    c = black_queen.GetPieceCharacter();
    AssertEqual(c, 'q', "Incorrect notation for black queen");
}



}

CHESS_TEST_LIST(QueenTestSuite)
{
    CHESS_TEST_LIST_ITEM(QueenTests::Movement);
    CHESS_TEST_LIST_ITEM(QueenTests::Notation);
}


}
