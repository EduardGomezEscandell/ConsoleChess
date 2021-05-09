#include "test_board.h"
#include "board.h"
#include <cstdio>

namespace ConsoleChess {

namespace BoardTests {

CHESS_DEFINE_TEST(Constructor)
{
    Board board;

    const int nfiles = board.NumberOfFiles;
    AssertEqual<const int, int>(nfiles, 8);

    const int nranks = board.NumberOfRanks;
    AssertEqual<const int, int>(nranks, 8);

    const int nsquares = board.NumberOfSquares;
    AssertEqual<const int, int>(nsquares, 64);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            bool isempty = board.SquareIsEmpty(i,j);
            char buffer[256];
            sprintf(buffer, "Square %d, %d is not empty at the begining", i, j);
            AssertTrue(isempty, buffer);
        }
    }
}

CHESS_DEFINE_TEST(CreatePiece)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KNIGHT, 0,0, Colour::WHITE);

    Colour c = board.GetColourOccupied(0,0);
    AssertEqual((int) c, (int) Colour::WHITE, "Square colour should have been white but it was not");

    c = board.GetColourOccupied(0,1);
    AssertEqual((int) c, (int) Colour::UNDEFINED, "Square colour should have been undefined but it was not");
}

CHESS_DEFINE_TEST(FullPieceSet)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KING,   0, 4, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::KNIGHT, 0, 6, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::ROOK,   0, 7, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::BISHOP, 0, 3, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::QUEEN,  0, 5, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::PAWN,   1, 0, Colour::WHITE);
}

CHESS_DEFINE_TEST(CopyConstructor)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KING, 5, 5, Colour::BLACK);
    Piece * original = board.pGetSquareContent(5,5);

    Board new_board = board;
    Piece * new_king = new_board.pGetSquareContent(5,5);

    AssertDifferent(new_king, static_cast<Piece *>(nullptr));     // Ensuring there is something
    AssertEqual(new_king->GetPieceType(), PieceSet::KING);        // Ensuring there is a king

    AssertDifferent(original, new_king);                          // Ensuring the new piece is different instance
}

CHESS_DEFINE_TEST(KingInCheck)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KING, 5,5, Colour::BLACK);
    
    // Checking positive test
    board.CreatePieceInLocation(PieceSet::ROOK, 5, 0, Colour::WHITE);
    board.UpdateLegalMoves();

    AssertTrue(board.IsInCheck(Colour::BLACK));
    
    // Checking negative test
    board.GetSquare(5,0).Vacate();
    board.ResetAttacks();
    board.UpdateLegalMoves();

    AssertFalse(board.IsInCheck(Colour::BLACK));
}

CHESS_DEFINE_TEST(TwoPossibleMoves)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::ROOK, 0,5, Colour::WHITE); // Rook on f1
    board.CreatePieceInLocation(PieceSet::ROOK, 7,5, Colour::WHITE); // Rook on f8
    board.UpdateLegalMoves();

    Move move{5, 5}; // Move ?f6
    AssertFalse(board.ValidateAndCompleteMove(move, PieceSet::ROOK), "Failed to notice move Rf6 is ambiguous: both rooks can move to f6");

    move = Move{5,5};
    move.SetDepartureFile(5);
    AssertFalse(board.ValidateAndCompleteMove(move, PieceSet::ROOK), "Failed to notice move Rff6 is ambiguous: both rooks are on the F file");

    move = Move{5,5};
    move.SetDepartureRank(0);
    AssertTrue(board.ValidateAndCompleteMove(move, PieceSet::ROOK), "Failed to validate move R1f6");

    move = Move{0,5,5,5};
    AssertTrue(board.ValidateAndCompleteMove(move, PieceSet::ROOK), "Failed to validate move Rf1f6");
}


}



CHESS_TEST_LIST(BoardTestSuite)
{
    CHESS_TEST_LIST_ITEM(BoardTests::Constructor)
    CHESS_TEST_LIST_ITEM(BoardTests::CreatePiece)
    CHESS_TEST_LIST_ITEM(BoardTests::FullPieceSet)
    CHESS_TEST_LIST_ITEM(BoardTests::CopyConstructor)
    CHESS_TEST_LIST_ITEM(BoardTests::KingInCheck)
    CHESS_TEST_LIST_ITEM(BoardTests::TwoPossibleMoves)
}


}
