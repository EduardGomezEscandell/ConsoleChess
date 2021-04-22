#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"
#include "../board/board.h"
#include "../defines.h"

namespace ConsoleChess {

class Board;

class Bishop : public Piece
{
public:
    Bishop(const int & rank, const int & file, const Board * parent_board, const Colour & colour);

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    PieceSet mPieceType = PieceSet::BISHOP;
    static constexpr char mNotationCharacter = 'r';

    friend class Board;

    void UpdateMovesInDirection(const int delta_r, const int delta_f);
};

}
#endif // Bishop_H
