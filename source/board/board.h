#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../piece.h"
#include "../defines.h"
#include "../square.h"
#include <memory>
#include <string>

namespace ConsoleChess {

class Board
{
public:
    Board();
    Board(const std::string & rFen);
    Board(const Board & rRHS);

    Piece * pGetSquareContent(const int & square);
    const Piece * pGetSquareContent(const int & square) const;
    Piece * pGetSquareContent(const int & rank, const int & file);
    const Piece * pGetSquareContent(const int & rank, const int & file) const;

    Piece * CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour);

    Colour GetColourOccupied(const int & rank, const int & file) const;
    bool SquareIsEmpty(const int & rank, const int & file);

    void SetUpInitialPieces();

    std::string Display() const;
    Colour IsInCheck() const;


    static void CheckBoundsDebug(const int rank, const int file);

    static constexpr int NumberOfFiles = 8;
    static constexpr int NumberOfRanks = 8;
    static constexpr int NumberOfSquares = NumberOfRanks * NumberOfFiles;

protected:
    Square mSquares[NumberOfSquares];
    static std::tuple<PieceSet, Colour> GetPieceFromFEN(char c);

    static unsigned int CoordsToIndex(const unsigned int rank, const unsigned int file);
};

std::ostream& operator<<(std::ostream& os, const Board& b);

}

#endif // CHESS_BOARD_H
