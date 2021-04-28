#include "king.h"

namespace ConsoleChess {


CHESS_DEFINE_PIECE_BOILERPLATE(King, KING, 'k')

void King::UpdateLegalMoves()
{
    mLegalMoves.clear();

    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];

    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            if(i == 0 && j==0) continue;

            int destination_rank = initial_rank + i;
            int destination_file = initial_file + j;

            if(CheckDestinationSquare(destination_rank, destination_file))
            {
                mLegalMoves.emplace_back(initial_rank, initial_file, destination_rank, destination_file);
            }
        }
    }

}

bool King::IsInCheck() const
{
    // const Board& b = *(this->mParentBoard);
    return false;
}


}
