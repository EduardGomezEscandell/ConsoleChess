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
    AssertEqualContainers(white_moves, expected_moves, "White pawn moves are incorrect.");


    // Testing black
    expected_moves = {}; // Pawn is blockaded: no moves

    black_pawn->UpdateLegalMoves();
    const auto & black_moves = black_pawn->GetMoves();
    AssertEqualContainers(black_moves, expected_moves, "Black pawn moves are incorrect.");

    for(const Move & m : white_pawn->GetMoves())
    {   
        Square & s = board.GetSquare(m.GetLandingRank(), m.GetLandingFile());
        bool is_attacked = s.IsAttackedBy(white_pawn->GetColour());
        
        if(m.GetDepartureFile() == m.GetLandingFile()) // Pawns cannot attack forwards
        {
            std::stringstream ss;
            ss << "Pawn available forward square is attacked (" << s.GetName() << ")" <<std::endl;
            AssertFalse(is_attacked, ss.str());
        }
        else // Pawns can attack diagonaly
        {
            std::stringstream ss;
            ss << "Pawn available diagonal square is not attacked (" << s.GetName() << ")" <<std::endl;
            AssertTrue(is_attacked, ss.str());
        }
    }
}

CHESS_DEFINE_TEST(Notation)
{
    Pawn white_pawn = Pawn(1,1,nullptr, Colour::WHITE);
    Pawn black_pawn = Pawn(1,1,nullptr, Colour::BLACK);
    char c;

    c = white_pawn.GetPieceCharacter();
    AssertEqual(c, 'O', "Incorrect notation for white pawn");

    c = black_pawn.GetPieceCharacter();
    AssertEqual(c, 'o', "Incorrect notation for black pawn");
}

CHESS_DEFINE_TEST(Promotion)
{
    Board board("8/P7/8/8/8/8/p7/8");
    Piece * wpawn = board.pGetSquareContent(6, 0); // white pawn about to promote
    Piece * bpawn = board.pGetSquareContent(1, 0); // black pawn

    board.UpdateLegalMoves();

    // White pawn check
    std::vector<Move> expected_moves = {{6,0,7,0, PieceSet::QUEEN},
                                        {6,0,7,0, PieceSet::ROOK},
                                        {6,0,7,0, PieceSet::BISHOP},
                                        {6,0,7,0, PieceSet::KNIGHT}
    };
    AssertEqualContainers(wpawn->GetMoves(), expected_moves, "White pawn promotion not properly calculated");

    // Black pawn test
    expected_moves.clear();
    expected_moves = {{1,0,0,0, PieceSet::QUEEN},
                      {1,0,0,0, PieceSet::ROOK},
                      {1,0,0,0, PieceSet::BISHOP},
                      {1,0,0,0, PieceSet::KNIGHT}
    };
    AssertEqualContainers(bpawn->GetMoves(), expected_moves, "Black pawn promotion not properly calculated");
}

CHESS_DEFINE_TEST(DoubleAdvance)
{
    Board board("8/p7/8/8/8/8/P7/8");

    Piece * wpawn = board.pGetSquareContent(1, 0); // white pawn
    Piece * bpawn = board.pGetSquareContent(6, 0); // black pawn

    board.UpdateLegalMoves();

    // White pawn check
    std::vector<Move> expected_moves = {{1,0,2,0},
                                        {1,0,3,0}
    };
    AssertEqualContainers(wpawn->GetMoves(), expected_moves, "White pawn double advance not properly implemented");

    // Black pawn test
    expected_moves.clear();
    expected_moves = {{6,0,5,0},
                      {6,0,4,0}
    };
    AssertEqualContainers(bpawn->GetMoves(), expected_moves, "Black pawn double advance not properly implemented");
}


}

CHESS_TEST_LIST(PawnTestSuite)
{
    CHESS_TEST_LIST_ITEM(PawnTests::Movement);
    CHESS_TEST_LIST_ITEM(PawnTests::Notation);
    CHESS_TEST_LIST_ITEM(PawnTests::Promotion);
    CHESS_TEST_LIST_ITEM(PawnTests::DoubleAdvance);
}


}
