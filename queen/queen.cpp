#include "queen.h"

namespace ConsoleChess {


Queen::Queen(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
    : Piece(rank, file, parent_board, colour)
{

}

char Queen::GetPieceCharacter() const
{
    static constexpr char c = 'q';
    return mColour==Colour::BLACK ? c : (c + 'A'-'a'); // Capitalizing white pieces
}

void Queen::UpdateLegalMoves()
{
    mLegalMoves.clear();

    // Ranks and files
    StraightLineMoveUpdate( 1, 0);
    StraightLineMoveUpdate(-1, 0);
    StraightLineMoveUpdate( 0, 1);
    StraightLineMoveUpdate( 0,-1);

    // Diagonals
    StraightLineMoveUpdate( 1, 1);
    StraightLineMoveUpdate(-1, 1);
    StraightLineMoveUpdate( 1,-1);
    StraightLineMoveUpdate(-1,-1);
}


}
