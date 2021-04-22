#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../piece.h"
#include "../defines.h"
#include <memory>
#include <string>

namespace ConsoleChess {

class Board
{
public:
    Board();

    Board(const Board & rRHS);

    Piece * pGetSquareContent(const int & rank, const int & file);
    const Piece * pGetSquareContent(const int & rank, const int & file) const;

    Piece * CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour);

    Colour GetColourOccupied(const int & rank, const int & file) const;
    bool SquareIsEmpty(const int & rank, const int & file);

    static std::string GetSquareName(unsigned int rank, unsigned int file);

    const static int NumberOfFiles = 8;
    const static int NumberOfRanks = 8;
    const static int NumberOfSquares = NumberOfRanks * NumberOfFiles;

    void SetUpInitialPieces();

    std::string Display() const;


protected:
    std::unique_ptr<Piece> mSquares[NumberOfSquares];
};

std::ostream& operator<<(std::ostream& os, const Board& b);

}

#endif // CHESS_BOARD_H
