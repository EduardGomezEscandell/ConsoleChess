#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"
#include "../board/board.h"
#include "../defines.h"

namespace ConsoleChess {

class Board;

class Queen : public Piece
{
public:
    Queen(const int & rank, const int & file, const Board * parent_board, const Colour & colour);

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    PieceSet mPieceType = PieceSet::QUEEN;
    static constexpr char mNotationCharacter = 'r';

    friend class Board;
};

}
#endif // QUEEN_H
