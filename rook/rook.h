#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"
#include "../board/board.h"
#include "../defines.h"

namespace ConsoleChess {

class Board;

class Rook : public Piece
{
public:
    Rook(const int & rank, const int & file, const Board * parent_board, const Colour & colour);

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;

protected:
    PieceSet mPieceType = PieceSet::ROOK;
    static constexpr char mNotationCharacter = 'r';

    friend class Board;

    bool mHasMoved = false;

};

}
#endif // ROOK_H
