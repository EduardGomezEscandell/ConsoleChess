#include "test_board.h"
#include "board.h"
#include <cstdio>

namespace ConsoleChess {

namespace BoardTests {

CHESS_DEFINE_TEST(Constructor)
{
    Board board;

    const int nfiles = board.NumberOfFiles;
    this->AssertEqual<const int, int>(nfiles, 8);

    const int nranks = board.NumberOfRanks;
    this->AssertEqual<const int, int>(nranks, 8);

    const int nsquares = board.NumberOfSquares;
    this->AssertEqual<const int, int>(nsquares, 64);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            bool isempty = board.SquareIsEmpty(i,j);
            char buffer[256];
            sprintf(buffer, "Square %d, %d is not empty at the begining", i, j);
            this->AssertTrue(isempty, buffer);
        }
    }
}

CHESS_DEFINE_TEST(CreatePiece)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KNIGHT, 0,0, Colour::WHITE);

    Colour c = board.GetColourOccupied(0,0);
    this->AssertEqual((int) c, (int) Colour::WHITE, "Square colour should have been white but it was not");

    c = board.GetColourOccupied(0,1);
    this->AssertEqual((int) c, (int) Colour::UNDEFINED, "Square colour should have been undefined but it was not");
}

CHESS_DEFINE_TEST(FullPieceSet)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KING,   0, 4, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::KNIGHT, 0, 6, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::ROOK,   0, 7, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::BISHOP, 0, 3, Colour::WHITE);
    board.CreatePieceInLocation(PieceSet::QUEEN,  0, 5, Colour::WHITE);
}

CHESS_DEFINE_TEST(CopyConstructor)
{
    Board board;
    board.CreatePieceInLocation(PieceSet::KING, 5, 5, Colour::BLACK);
    Piece * original = board.pGetSquareContent(5,5);

    Board new_board = board;
    Piece * new_king = new_board.pGetSquareContent(5,5);

    this->AssertDifferent(new_king, static_cast<Piece *>(nullptr));     // Ensuring there is something
    this->AssertEqual(new_king->GetPieceType(), PieceSet::KING);        // Ensuring there is a king

    this->AssertDifferent(original, new_king);                          // Ensuring the new piece is different instance
}


}



CHESS_TEST_LIST(BoardTestSuite)
{
    CHESS_TEST_LIST_ITEM(BoardTests::Constructor)
    CHESS_TEST_LIST_ITEM(BoardTests::CreatePiece)
    CHESS_TEST_LIST_ITEM(BoardTests::FullPieceSet)
    CHESS_TEST_LIST_ITEM(BoardTests::CopyConstructor)
}


}
