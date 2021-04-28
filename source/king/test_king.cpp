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

    for(const Move & m : moves)
    {   
        Square & s = board.GetSquare(m.landing_rank, m.landing_file);
        bool is_attacked = s.IsAttackedBy(king->GetColour());
        std::stringstream ss;
        ss << "King available square is not attacked (" << s.GetName() << ")" <<std::endl;
        this->AssertTrue(is_attacked, ss.str());
    }

}

CHESS_DEFINE_TEST(Checks)
{
    Board board;
    Piece * king = board.CreatePieceInLocation(PieceSet::KING, 5, 5, Colour::WHITE);
    Piece * rook = board.CreatePieceInLocation(PieceSet::ROOK, 6, 6, Colour::BLACK); // Rook to block

    std::vector<Move> expected_moves = {{5,5,4,4},
                                        {5,5,4,5},
                                        {5,5,5,4},
                                        {5,5,6,6}, // Rook capture
                                       };

    rook->UpdateLegalMoves();
    king->UpdateLegalMoves();
    const auto & moves = king->GetMoves();
    this->AssertEqualContainers(moves, expected_moves, "King movement when checks exist incorrect");

    for(const Move & m : moves)
    {   
        Square & s = board.GetSquare(m.landing_rank, m.landing_file);
        bool is_attacked = s.IsAttackedBy(king->GetColour());
        std::stringstream ss;
        ss << "King available square is not attacked (" << s.GetName() << ")" <<std::endl;
        this->AssertTrue(is_attacked, ss.str());
    }

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

CHESS_DEFINE_TEST(PieceType)
{
    King k = King(1,1,nullptr, Colour::BLACK);
    this->AssertEqual(k.GetPieceType(), PieceSet::KING);
}


}

CHESS_TEST_LIST(KingTestSuite)
{
    CHESS_TEST_LIST_ITEM(KingTests::Movement);
    CHESS_TEST_LIST_ITEM(KingTests::Checks);
    CHESS_TEST_LIST_ITEM(KingTests::Notation);
    CHESS_TEST_LIST_ITEM(KingTests::PieceType);
}


}
