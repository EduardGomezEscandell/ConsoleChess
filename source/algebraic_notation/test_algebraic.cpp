#include "test_algebraic.h"
#include "algebraic_notation.h"
#include <string>

namespace ConsoleChess {

namespace AlgebraicTests {

CHESS_DEFINE_TEST(PawnCheck)
{
    PieceSet piece, promotion;
    Move move;

    std::string input = "e5+";
    bool valid_move = AlgebraicReader::ParseMove(piece, promotion, move, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 1");
    this->AssertEqual(piece, PieceSet::PAWN, "Failed to read the piece in example 1");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to read the promotion in example 1");
    this->AssertEqual(move.departure_file, -1, "Failed to read the departure_file in example 1");
    this->AssertEqual(move.departure_rank, -1, "Failed to read the departure_rank in example 1");
    this->AssertEqual(move.landing_rank, 4, "Failed to read the landing_rank in example 1");
    this->AssertEqual(move.landing_file, 4, "Failed to read the landing_file in example 1");
}

CHESS_DEFINE_TEST(RookCapture)
{
    PieceSet piece, promotion;
    Move move;

    const std::string input = "Rxc6";
    const bool valid_move = AlgebraicReader::ParseMove(piece, promotion, move, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 2");
    this->AssertEqual(piece, PieceSet::ROOK, "Failed to read the piece in example 2");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to read the promotion in example 2");
    this->AssertEqual(move.departure_file, -1, "Failed to read the departure_file in example 2");
    this->AssertEqual(move.departure_rank, -1, "Failed to read the departure_rank in example 2");
    this->AssertEqual(move.landing_rank, 5, "Failed to read the landing_rank in example 2");
    this->AssertEqual(move.landing_file, 2, "Failed to read the landing_file in example 2");
}

CHESS_DEFINE_TEST(RookCaptureDraw)
{
    PieceSet piece, promotion;
    Move move;

    const std::string input = "Rexc6=";
    const bool valid_move = AlgebraicReader::ParseMove(piece, promotion, move, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 3");
    this->AssertEqual(piece, PieceSet::ROOK, "Failed to read the piece in example 3");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to read the promotion in example 3");
    this->AssertEqual(move.departure_file, 4, "Failed to read the departure_file in example 3");
    this->AssertEqual(move.departure_rank, -1, "Failed to read the departure_rank in example 3");
    this->AssertEqual(move.landing_rank, 5, "Failed to read the landing_rank in example 3");
    this->AssertEqual(move.landing_file, 2, "Failed to read the landing_file in example 3");
}

CHESS_DEFINE_TEST(PawnCapturePromoteMate)
{
    PieceSet piece, promotion;
    Move move;

    const std::string input = "gxh8=Q#";
    const bool valid_move = AlgebraicReader::ParseMove(piece, promotion, move, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 4");
    this->AssertEqual(piece, PieceSet::PAWN, "Failed to read the piece in example 4");
    this->AssertEqual(promotion, PieceSet::QUEEN, "Failed to read the promotion in example 4");
    this->AssertEqual(move.departure_file, 6, "Failed to read the departure_file in example 4");
    this->AssertEqual(move.departure_rank, -1, "Failed to read the departure_rank in example 4");
    this->AssertEqual(move.landing_rank, 7, "Failed to read the landing_rank in example 4");
    this->AssertEqual(move.landing_file, 7, "Failed to read the landing_file in example 4");
}

CHESS_DEFINE_TEST(Typo)
{
    PieceSet piece, promotion;
    Move move;
    const std::string input = "qh8"; // this move is a typo, should be Qh8
    const bool valid_move = AlgebraicReader::ParseMove(piece, promotion, move, input);
    
    this->AssertEqual(valid_move, false, "Failed to recognize the non-validity of example 5");
    this->AssertEqual(piece, PieceSet::NONE, "Failed to read the piece in example 5");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to clean up the promotion in example 5");
    this->AssertEqual(move.departure_file, -1, "Failed to clean up the departure_file in example 5");
    this->AssertEqual(move.departure_rank, -1, "Failed to clean up the departure_rank in example 5");
    this->AssertEqual(move.landing_rank, -1, "Failed to clean up the landing_rank in example 5");
    this->AssertEqual(move.landing_file, -1, "Failed to clean up the landing_file in example 5");
}

CHESS_DEFINE_TEST(RookPromotion)
{
    PieceSet piece, promotion;
    Move move;
    const std::string input = "O-O"; // this move is a typo, should be Qh8
    const bool valid_move = AlgebraicReader::ParseMove(piece, promotion, move, input);
    
    this->AssertEqual(valid_move, false, "Failed to recognize the non-validity of example 6");
    this->AssertEqual(piece, PieceSet::NONE, "Failed to read the piece in example 6");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to clean up the promotion in example 6");
    this->AssertEqual(move.departure_file, -1, "Failed to clean up the departure_file in example 6");
    this->AssertEqual(move.departure_rank, -1, "Failed to clean up the departure_rank in example 6");
    this->AssertEqual(move.landing_rank, -1, "Failed to clean up the landing_rank in example 6");
    this->AssertEqual(move.landing_file, -1, "Failed to clean up the landing_file in example 6");
}


}


CHESS_TEST_LIST(AlgebraicNotationTestSuite)
{
    CHESS_TEST_LIST_ITEM(AlgebraicTests::PawnCheck);
    CHESS_TEST_LIST_ITEM(AlgebraicTests::RookCapture);
    CHESS_TEST_LIST_ITEM(AlgebraicTests::RookCaptureDraw);
    CHESS_TEST_LIST_ITEM(AlgebraicTests::PawnCapturePromoteMate);
    CHESS_TEST_LIST_ITEM(AlgebraicTests::RookPromotion);
    CHESS_TEST_LIST_ITEM(AlgebraicTests::Typo);
}


}
