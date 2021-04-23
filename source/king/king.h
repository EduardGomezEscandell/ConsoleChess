#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "../piece.h"
#include "../board/board.h"
#include "../defines.h"

namespace ConsoleChess {

class Board;

class King : public Piece
{
public:
    King(const int & rank, const int & file, const Board * parent_board, const Colour & colour);
    Piece * Clone(const Board * parent_board) const override;

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    friend class Board;

    bool mHasCastled = false;

};

}
#endif // CHESS_KING_H