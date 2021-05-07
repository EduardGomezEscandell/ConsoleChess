#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"
#include "../board/board.h"
#include "../defines.h"

namespace ConsoleChess {

class Board;

class Pawn : public Piece
{
public:
    Pawn(const int & rank, const int & file, Board * parent_board, const Colour & colour);
    Piece * Clone(Board * parent_board) const override;

    void UpdateLegalMoves() override;
    char GetPieceCharacter() const override;
    PieceSet GetPieceType() const override;

protected:
    friend class Board;

    void EmplaceMoveMaybePromote(const int DepartureRank,
                                 const int DepartureFile,
                                 const int LandingRank,
                                 const int LandingFile);
};

}
#endif // PAWN_H
