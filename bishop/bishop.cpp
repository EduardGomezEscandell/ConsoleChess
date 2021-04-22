#include "bishop.h"

namespace ConsoleChess {


Bishop::Bishop(const int & rank, const int & file, const Board * parent_board, const Colour & colour)
    : Piece(rank, file, parent_board, colour)
{

}

char Bishop::GetPieceCharacter() const
{
    static constexpr char c = 'b';
    return mColour==Colour::BLACK ? c : (c + 'A'-'a'); // Capitalizing white pieces
}

void Bishop::UpdateMovesInDirection(const int delta_r, const int delta_f)
{
    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];

    int r = initial_rank;
    int f = initial_file;

    for(int k=0; k < Board::NumberOfSquares; k++)
    {
        r += delta_r;
        f += delta_f;


        if(CheckDestinationSquare(r, f))
        {
            mLegalMoves.emplace_back(initial_rank, initial_file, r, f);

            if(CheckIfCaptures(r,f))
            {
                break; // Cannot move beyond capture
            }

        } else
        {
            break; // Cannot move same-team own piece
        }
    }
}


void Bishop::UpdateLegalMoves()
{
    mLegalMoves.clear();

    UpdateMovesInDirection( 1, 1);
    UpdateMovesInDirection( 1,-1);
    UpdateMovesInDirection(-1, 1);
    UpdateMovesInDirection(-1,-1);
}


}
