#include "queen.h"

namespace ConsoleChess {


CHESS_DEFINE_PIECE_BOILERPLATE(Queen, QUEEN, 'q');

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
