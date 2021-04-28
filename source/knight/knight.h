#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "../piece.h"
#include "../board/board.h"
#include "../defines.h"

namespace ConsoleChess {

class Board;

class Knight : public Piece
{
public:
    Knight(const int & rank, const int & file, Board * parent_board, const Colour & colour);

    Piece * Clone(Board * parent_board) const override;

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    friend class Board;

};

}

#endif // CHESS_KNIGHT_H
