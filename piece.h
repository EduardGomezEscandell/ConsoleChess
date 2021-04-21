#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "defines.h"
#include "move.h"
#include <vector>
#include <memory>

namespace ConsoleChess {

class Board;

class Piece
{
public:
    virtual void UpdateLegalMoves() = 0;

    PieceSet GetPieceType() const;
    Colour GetColour() const;

    std::vector<Move> & GetMoves();
    const std::vector<Move> & GetMoves() const;

protected:

    int mLocation[2];
    const Board * mParentBoard;
    int mPinDirection;

    PieceSet mPieceType = PieceSet::NONE;
    const Colour mColour = Colour::UNDEFINED;

    std::vector<Move> mLegalMoves;

    friend class Board;

    Piece(const int & rank, const int & file, const Board * parent_board, const Colour & colour);
    bool CheckDestinationSquare(const int & rank, const int & file) const;
};

}

#endif // CHESS_PIECE_H
