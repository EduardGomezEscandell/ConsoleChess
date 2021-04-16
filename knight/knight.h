#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

namespace ConsoleChess {

class Board;

class Knight : public Piece
{
public:
    Knight(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
        : Piece(rank, file, parent_board, colour){};

    void UpdateLegalMoves() override;

protected:
    PieceSet mPieceType = PieceSet::KNIGHT;

    friend class Board;



};

}

#endif // KNIGHT_H
