#ifndef PIECE_H
#define PIECE_H

#include "defines.h"
#include <vector>
#include <memory>

namespace ConsoleChess {

class Board;

class Piece
{
public:
    typedef std::shared_ptr<Piece> Pointer;
    typedef std::shared_ptr<const Piece> ConstPointer;

    virtual void UpdateLegalMoves() = 0;

    PieceSet WhatIsIt() {return mPieceType;}
    Colour GetColour() {return mColour;}

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

#endif // PIECE_H
