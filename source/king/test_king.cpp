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
    AssertEqualContainers(moves, expected_moves, "King movement incorrect");

    for(const Move & m : moves)
    {   
        Square & s = board.GetSquare(m.GetLandingRank(), m.GetLandingFile());
        bool is_attacked = s.IsAttackedBy(king->GetColour());
        std::stringstream ss;
        ss << "King available square is not attacked (" << s.GetName() << ")" <<std::endl;
        AssertTrue(is_attacked, ss.str());
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
    AssertEqualContainers(moves, expected_moves, "King movement when checks exist incorrect");

    for(const Move & m : moves)
    {   
        Square & s = board.GetSquare(m.GetLandingRank(), m.GetLandingFile());
        bool is_attacked = s.IsAttackedBy(king->GetColour());
        std::stringstream ss;
        ss << "King available square is not attacked (" << s.GetName() << ")" <<std::endl;
        AssertTrue(is_attacked, ss.str());
    }

}

CHESS_DEFINE_TEST(Notation)
{
    King white_king = King(1,1,nullptr, Colour::WHITE);
    King black_king = King(1,1,nullptr, Colour::BLACK); // dark knight
    char c;

    c = white_king.GetPieceCharacter();
    AssertEqual(c, 'K', "Incorrect notation for white knight");

    c = black_king.GetPieceCharacter();
    AssertEqual(c, 'k', "Incorrect notation for black knight");
}

CHESS_DEFINE_TEST(PieceType)
{
    King k = King(1,1,nullptr, Colour::BLACK);
    AssertEqual(k.GetPieceType(), PieceSet::KING);
}

CHESS_DEFINE_TEST(KingInCheck)
{
    Board board;
    Piece * king = board.CreatePieceInLocation(PieceSet::KING, 5,5, Colour::WHITE);
    
    // Checking positive test
    board.CreatePieceInLocation(PieceSet::ROOK, 5, 0, Colour::BLACK);
    board.UpdateLegalMoves();

    AssertTrue(king->IsInCheck());
    
    // Checking negative test
    board.GetSquare(5,0).Vacate();
    board.ResetAttacks();
    board.UpdateLegalMoves();

    AssertFalse(king->IsInCheck());
}

CHESS_DEFINE_TEST(ShortCastle)
{
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R"); // Initial configuration without kingside bishop & rook
    board.UpdateLegalMoves();
    
    Piece * king = board.pGetSquareContent(0, 4);

    std::vector<Move> expected_moves = {{0,4,0,5},
                                         Move::ShortCastle()
    };

    AssertEqualContainers(king->GetMoves(), expected_moves);
}

CHESS_DEFINE_TEST(LongCastle)
{
    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3KBNR"); // Initial configuration without kingside bishop & rook
    board.UpdateLegalMoves();
    
    Piece * king = board.pGetSquareContent(0, 4);

    std::vector<Move> expected_moves = {{0,4,0,3},
                                         Move::LongCastle()
    };

    AssertEqualContainers(king->GetMoves(), expected_moves);
}

CHESS_DEFINE_TEST(CastleObstructedByAttack)
{
    Board board("rnbqkbnr/ppp1pppp/8/8/8/8/PPP1PPPP/R3KBNR"); // Initial configuration without kingside bishop & rook
    board.UpdateLegalMoves();
    
    Piece * king = board.pGetSquareContent(0, 4);
    std::vector<Move> expected_moves = {};


    AssertEqualContainers(king->GetMoves(), expected_moves);
}




}

CHESS_TEST_LIST(KingTestSuite)
{
    CHESS_TEST_LIST_ITEM(KingTests::Movement);
    CHESS_TEST_LIST_ITEM(KingTests::Checks);
    CHESS_TEST_LIST_ITEM(KingTests::Notation);
    CHESS_TEST_LIST_ITEM(KingTests::PieceType);
    CHESS_TEST_LIST_ITEM(KingTests::KingInCheck);
    CHESS_TEST_LIST_ITEM(KingTests::ShortCastle);
    CHESS_TEST_LIST_ITEM(KingTests::LongCastle);
    CHESS_TEST_LIST_ITEM(KingTests::CastleObstructedByAttack);
}


}
