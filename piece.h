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
    virtual char GetPieceCharacter() const = 0;

protected:

    int mLocation[2];
    const Board * mParentBoard;
    std::vector<Move> mLegalMoves;
    PieceSet mPieceType = PieceSet::NONE;
    const Colour mColour = Colour::UNDEFINED;


    friend class Board;

    Piece(const int & rank, const int & file, const Board * parent_board, const Colour & colour);
    bool CheckDestinationSquare(const int & rank, const int & file) const;
    bool CheckIfCaptures(const int & rank, const int & file) const;
    void StraightLineMoveUpdate(const int delta_r, const int delta_f);
};

}

#endif // CHESS_PIECE_H
