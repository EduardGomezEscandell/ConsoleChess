#ifndef ROOK_H
#define ROOK_H


#include "../piece.h"

namespace ConsoleChess {

class Board;

class Rook : public Piece
{
public:
    Rook(const int & rank, const int & file, const Board * parent_board, const Colour & colour);

    void UpdateLegalMoves() override;
    void RevokeCastlingRights();

protected:
    PieceSet mPieceType = PieceSet::ROOK;

    friend class Board;

    bool mHasMoved = false;

};

}
#endif // ROOK_H
