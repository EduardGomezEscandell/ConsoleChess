#ifndef KING_H
#define KING_H


#include "../piece.h"

namespace ConsoleChess {

class Board;

class King : public Piece
{
public:
    King(const int & rank, const int & file, const Board * parent_board, const Colour & colour);

    void UpdateLegalMoves() override;

protected:
    PieceSet mPieceType = PieceSet::KNIGHT;

    friend class Board;

    bool mHasCastled = false;

};

}
#endif // KING_H
