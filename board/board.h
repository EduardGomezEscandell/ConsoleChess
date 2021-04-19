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

    std::shared_ptr<Piece> & pGetSquareContent(const int & rank, const int & file);
    const std::shared_ptr<Piece> & pGetSquareContent(const int & rank, const int & file) const;
    std::shared_ptr<Piece> operator()(const int & rank, const int & file) {return pGetSquareContent(rank, file);};

    std::shared_ptr<Piece> CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour);

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

#endif // CHESS_BOARD_H
