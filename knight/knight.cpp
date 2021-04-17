#include "knight.h"
#include "../board/board.h"

namespace ConsoleChess {


void Knight::UpdateLegalMoves()
{
    mLegalMoves.clear();

    constexpr int valid_moves[8][2] = {{ 2, 1},
                                       { 2,-1},
                                       {-2,-1},
                                       {-2, 1},
                                       { 1, 2},
                                       { 1,-2},
                                       {-1, 2},
                                       {-1,-2}};

    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];

    for(int i=0; i<8; i++)
    {
        int destination_rank = initial_rank + valid_moves[i][0];
        int destination_file = initial_file + valid_moves[i][0];

        if(CheckDestinationSquare(destination_rank, destination_file))
        {
            mLegalMoves.push_back(Move{initial_rank, initial_file, destination_rank, destination_file});
        }

    }

}

}
