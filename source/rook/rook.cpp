#include "rook.h"

namespace ConsoleChess {

CHESS_DEFINE_PIECE_BOILERPLATE(Rook, ROOK, 'r')

void Rook::UpdateLegalMoves()
{
    mLegalMoves.clear();

    StraightLineMoveUpdate( 1, 0);
    StraightLineMoveUpdate(-1, 0);
    StraightLineMoveUpdate( 0, 1);
    StraightLineMoveUpdate( 0,-1);
}


}
