#include "rook.h"

namespace ConsoleChess {


Rook::Rook(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
    : Piece(rank, file, parent_board, colour)
{

}

char Rook::GetPieceCharacter() const
{
    static constexpr char c = 'r';
    return mColour==Colour::BLACK ? c : (c + 'A'-'a'); // Capitalizing white pieces
}

void Rook::UpdateLegalMoves()
{
    mLegalMoves.clear();

    StraightLineMoveUpdate( 1, 0);
    StraightLineMoveUpdate(-1, 0);
    StraightLineMoveUpdate( 0, 1);
    StraightLineMoveUpdate( 0,-1);
}


}
