#include "pawn.h"

namespace ConsoleChess {

CHESS_DEFINE_PIECE_BOILERPLATE(Pawn, PAWN, 'o');

void Pawn::UpdateLegalMoves()
{
    mLegalMoves.clear();

    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];

    const int target_rank = initial_rank + (mColour == Colour::WHITE ? 1 : -1);

    if(target_rank > 7 || target_rank < 0)  return; // This should be impossible: pawns cannot exist in the oponent's backrank

    // Captures to the left
    if(initial_file > 0 && CheckIfCaptures(target_rank, initial_file-1))
    {
        mLegalMoves.emplace_back(initial_rank, initial_file, target_rank, initial_file-1);
    }

    // Captures to the right
    if(initial_file < 7 && CheckIfCaptures(target_rank, initial_file+1))
    {
        mLegalMoves.emplace_back(initial_rank, initial_file, target_rank, initial_file+1);
    }

    // Advances
    if(this->mParentBoard->pGetSquareContent(target_rank, initial_file) == nullptr)
    {
        mLegalMoves.emplace_back(initial_rank, initial_file, target_rank, initial_file);
    }

}


}
