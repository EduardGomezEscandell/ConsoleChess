#ifndef BOARD_H
#define BOARD_H

#include "../piece.h"

namespace ConsoleChess {

class Board
{
public:
    Board();

    Piece::Pointer & pGetSquareContent(const int & rank, const int & file);
    const Piece::Pointer & pGetSquareContent(const int & rank, const int & file) const;
    std::shared_ptr<Piece> operator()(const int & rank, const int & file) {return pGetSquareContent(rank, file);};

    Piece::Pointer CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour);

    Colour GetColourOccupied(const int & rank, const int & file) const;
    bool SquareIsEmpty(const int & rank, const int & file);

    static std::string GetSquareName(unsigned int rank, unsigned int file);

    const static int NumberOfFiles = 8;
    const static int NumberOfRanks = 8;
    const static int NumberOfSquares = NumberOfRanks * NumberOfFiles;


protected:
    std::shared_ptr<Piece> mSquares[NumberOfSquares];
    std::vector<std::shared_ptr<Piece>> mPieces;
};

}
#endif // BOARD_H
