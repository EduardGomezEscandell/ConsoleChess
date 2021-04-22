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
    Piece * Clone(const Board * parent_board) const override;

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    friend class Board;
};

}
#endif // Bishop_H
