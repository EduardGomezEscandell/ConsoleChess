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
    Knight(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
        : Piece(rank, file, parent_board, colour){};

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    PieceSet mPieceType = PieceSet::KNIGHT;
    friend class Board;



};

}

#endif // CHESS_KNIGHT_H
