#include "bishop.h"

namespace ConsoleChess {

CHESS_DEFINE_PIECE_BOILERPLATE(Bishop, BISHOP, 'b');

void Bishop::UpdateLegalMoves()
{
    mLegalMoves.clear();

    this->StraightLineMoveUpdate( 1, 1);
    this->StraightLineMoveUpdate( 1,-1);
    this->StraightLineMoveUpdate(-1, 1);
    this->StraightLineMoveUpdate(-1,-1);
}


}
