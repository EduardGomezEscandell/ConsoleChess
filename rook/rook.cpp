#include "rook.h"

namespace ConsoleChess {


Rook::Rook(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
    : Piece(rank, file, parent_board, colour)
{

}

void Rook::UpdateLegalMoves()
{
    mLegalMoves.clear();

    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];

    // Moving up
    for(int r=initial_rank+1; r <= 7; r++)
    {
        bool valid = CheckDestinationSquare(r, initial_file);
        if(valid)
        {
            mLegalMoves.emplace_back(initial_rank, initial_file, r, initial_file);
        }
        else
        {
            break;
        }
    }

    // Moving down
    for(int r=initial_rank-1; r >= 0; r--)
    {
        bool valid = CheckDestinationSquare(r, initial_file);
        if(valid)
        {
            mLegalMoves.emplace_back(initial_rank, initial_file, r, initial_file);
        }
        else
        {
            break;
        }
    }

    // Moving right
    for(int f=initial_file+1; f <= 7; f++)
    {
        bool valid = CheckDestinationSquare(initial_rank, f);
        if(valid)
        {
            mLegalMoves.emplace_back(initial_rank, initial_file, initial_rank, f);
        }
        else
        {
            break;
        }
    }

    // Moving left
    for(int f=initial_file-1; f >= 0; f--)
    {
        bool valid = CheckDestinationSquare(initial_rank, f);
        if(valid)
        {
            mLegalMoves.emplace_back(initial_rank, initial_file, initial_rank, f);
        }
        else
        {
            break;
        }
    }

}


}
