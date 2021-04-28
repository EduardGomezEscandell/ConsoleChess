#include "test_pawn.h"
#include "../board/board.h"

namespace ConsoleChess {

namespace PawnTests {

CHESS_DEFINE_TEST(Movement)
{
    Board board;
    Piece * white_pawn = board.CreatePieceInLocation(PieceSet::PAWN, 3,3, Colour::WHITE); // Pawn in D4
    Piece * black_pawn = board.CreatePieceInLocation(PieceSet::PAWN, 5,4, Colour::BLACK); // Pawn in E6

    board.CreatePieceInLocation(PieceSet::KNIGHT, 4,2, Colour::BLACK); // Knight to be captured by D4
    board.CreatePieceInLocation(PieceSet::BISHOP, 4,4, Colour::WHITE); // Bishop to blockade E6


    // Testing white
    std::vector<Move> expected_moves = {{3,3,4,3}, // advance
                                        {3,3,4,2}, // capture knight
                                       };
    white_pawn->UpdateLegalMoves();
    const auto & white_moves = white_pawn->GetMoves();
    this->AssertEqualContainers(white_moves, expected_moves, "White pawn moves are incorrect.");


    // Testing black
    expected_moves = {}; // Pawn is blockaded: no moves

    black_pawn->UpdateLegalMoves();
    const auto & black_moves = black_pawn->GetMoves();
    this->AssertEqualContainers(black_moves, expected_moves, "Black pawn moves are incorrect.");

    for(const Move & m : white_pawn->GetMoves())
    {   
        Square & s = board.GetSquare(m.landing_rank, m.landing_file);
        bool is_attacked = s.IsAttackedBy(white_pawn->GetColour());
        
        if(m.departure_file == m.landing_file) // Pawns cannot attack forwards
        {
            std::stringstream ss;
            ss << "Pawn available forward square is attacked (" << s.GetName() << ")" <<std::endl;
            this->AssertFalse(is_attacked, ss.str());
        }
        else // Pawns can attack diagonaly
        {
            std::stringstream ss;
            ss << "Pawn available diagonal square is not attacked (" << s.GetName() << ")" <<std::endl;
            this->AssertTrue(is_attacked, ss.str());
        }
    }
}

CHESS_DEFINE_TEST(Notation)
{
    Pawn white_pawn = Pawn(1,1,nullptr, Colour::WHITE);
    Pawn black_pawn = Pawn(1,1,nullptr, Colour::BLACK);
    char c;

    c = white_pawn.GetPieceCharacter();
    this->AssertEqual(c, 'O', "Incorrect notation for white pawn");

    c = black_pawn.GetPieceCharacter();
    this->AssertEqual(c, 'o', "Incorrect notation for black pawn");
}



}

CHESS_TEST_LIST(PawnTestSuite)
{
    CHESS_TEST_LIST_ITEM(PawnTests::Movement);
    CHESS_TEST_LIST_ITEM(PawnTests::Notation);
}


}
