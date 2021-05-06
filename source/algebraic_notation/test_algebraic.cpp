#include "test_algebraic.h"
#include "algebraic_notation.h"
#include <string>

namespace ConsoleChess {

namespace AlgebraicTests {

CHESS_DEFINE_TEST(PawnCheck)
{
    PieceSet piece;
    Move move;

    std::string input = "e5+";
    bool valid_move = AlgebraicReader::ParseMove(piece, move, input);
    
    AssertTrue(valid_move, "Failed to recognize the validity of example 1");
    AssertEqual(piece, PieceSet::PAWN, "Failed to read the piece in example 1");
    AssertEqual(move.GetPromotion(), PieceSet::NONE, "Failed to read the promotion in example 1");
    AssertFalse(move.IsDepartureFileKnown(),"Failed to read the departure_file in example 1");
    AssertFalse(move.IsDepartureRankKnown(), "Failed to read the departure_rank in example 1");
    AssertEqual(move.GetLandingRank(), 4, "Failed to read the landing_rank in example 1");
    AssertEqual(move.GetLandingFile(), 4, "Failed to read the landing_file in example 1");
}

CHESS_DEFINE_TEST(RookCapture)
{
    PieceSet piece;
    Move move;

    const std::string input = "Rxc6";
    const bool valid_move = AlgebraicReader::ParseMove(piece, move, input);
    
    AssertTrue(valid_move, "Failed to recognize the validity of example 2");
    AssertEqual(piece, PieceSet::ROOK, "Failed to read the piece in example 2");
    AssertEqual(move.GetPromotion(), PieceSet::NONE, "Failed to read the promotion in example 2");
    AssertFalse(move.IsDepartureFileKnown(), "Failed to read the departure_file in example 2");
    AssertFalse(move.IsDepartureRankKnown(), "Failed to read the departure_rank in example 2");
    AssertEqual(move.GetLandingRank(), 5, "Failed to read the landing_rank in example 2");
    AssertEqual(move.GetLandingFile(), 2, "Failed to read the landing_file in example 2");
}

CHESS_DEFINE_TEST(RookCaptureDraw)
{
    PieceSet piece;
    Move move;

    const std::string input = "Rexc6=";
    const bool valid_move = AlgebraicReader::ParseMove(piece, move, input);
    
    AssertTrue(valid_move, "Failed to recognize the validity of example 3");
    AssertEqual(piece, PieceSet::ROOK, "Failed to read the piece in example 3");
    AssertEqual(move.GetPromotion(), PieceSet::NONE, "Failed to read the promotion in example 3");
    AssertTrue(move.IsDepartureFileKnown(), "Failed to read the departure_file in example 3");
    AssertEqual(move.GetDepartureFile(), 4, "Failed to read the departure_file value in example 3");
    AssertFalse(move.IsDepartureRankKnown(), "Failed to read the departure_rank in example 3");
    AssertEqual(move.GetLandingRank(), 5, "Failed to read the landing_rank in example 3");
    AssertEqual(move.GetLandingFile(), 2, "Failed to read the landing_file in example 3");
}

CHESS_DEFINE_TEST(PawnCapturePromoteMate)
{
    PieceSet piece;
    Move move;

    const std::string input = "gxh8=Q#";
    const bool valid_move = AlgebraicReader::ParseMove(piece, move, input);
    
    AssertTrue(valid_move, "Failed to recognize the validity of example 4");
    AssertEqual(piece, PieceSet::PAWN, "Failed to read the piece in example 4");
    AssertEqual(move.GetPromotion(), PieceSet::QUEEN, "Failed to read the promotion in example 4");
    AssertTrue(move.IsDepartureFileKnown(), "Failed to read the departure_file in example 4");
    AssertEqual(move.GetDepartureFile(), 6, "Failed to read the departure_file value in example 4");
    AssertFalse(move.IsDepartureRankKnown(), "Failed to read the departure_rank in example 4");
    AssertEqual(move.GetLandingRank(), 7, "Failed to read the landing_rank in example 4");
    AssertEqual(move.GetLandingFile(), 7, "Failed to read the landing_file in example 4");
}

CHESS_DEFINE_TEST(Typo)
{
    PieceSet piece;
    Move move;
    const std::string input = "qh8"; // this move is a typo, should be Qh8
    const bool valid_move = AlgebraicReader::ParseMove(piece, move, input);
    
    AssertFalse(valid_move, "Failed to recognize the non-validity of example 5");
}

CHESS_DEFINE_TEST(RookPromotion)
{
    PieceSet piece;
    Move move;
    const std::string input = "Ra5=Q"; // this move is nonsense
    const bool valid_move = AlgebraicReader::ParseMove(piece, move, input);
    
    AssertFalse(valid_move, "Failed to recognize the non-validity of example 6");
}

CHESS_DEFINE_TEST(ShortCastles)
{
    PieceSet piece;
    Move move;
    const std::string input = "O-O";

    auto e = AssertRaises<ChessError>([&]()
    {
        AlgebraicReader::ParseMove(piece, move, input);
    });

    AssertRegex(e.what(), "[^]*Castling is not yet implemented[^]*", "Failed to throw castling not implemented exception");
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
    CHESS_TEST_LIST_ITEM(AlgebraicTests::ShortCastles);
}


}
