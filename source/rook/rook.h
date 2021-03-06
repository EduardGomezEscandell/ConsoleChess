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
    Rook(const int & rank, const int & file, Board * parent_board, const Colour & colour);
    Piece * Clone(Board * parent_board) const override;

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;
    PieceSet GetPieceType() const override;

    bool HasCastlingRights() const override;
    void RemoveCastlingRights() override;

protected:
    friend class Board;

    bool mHasMoved = false;

};

}
#endif // ROOK_H
