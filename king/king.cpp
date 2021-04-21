#include "king.h"

namespace ConsoleChess {


King::King(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
    : Piece(rank, file, parent_board, colour)
{

}

char King::GetPieceCharacter() const
{
    static constexpr char c = 'k';
    return mColour==Colour::BLACK ? c : (c + 'A'-'a'); // Capitalizing white pieces
}

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


}
