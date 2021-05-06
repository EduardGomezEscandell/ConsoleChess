#include "king.h"

namespace ConsoleChess {


CHESS_DEFINE_PIECE_BOILERPLATE(King, KING, 'k')

void King::UpdateLegalMoves()
{
    mLegalMoves.clear();

    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];


    // Regular moves
    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            if(i == 0 && j==0) continue;

            int destination_rank = initial_rank + i;
            int destination_file = initial_file + j;

            if(CheckDestinationSquare(destination_rank, destination_file))
            {
                Square & target_square = mParentBoard->GetSquare(destination_rank, destination_file);
                
                if(!target_square.IsAttackedBy(OppositeColour(mColour))) // King cannot walk into check
                {
                    mLegalMoves.emplace_back(initial_rank, initial_file, destination_rank, destination_file);
                    target_square.SetAttack(mColour);
                }
            }
        }
    }

    // Castling
    if(HasCastlingRights() == false) return;

    const int backrank = mColour==Colour::WHITE ? 0 : Board::NumberOfRanks-1;
    Colour opposite = OppositeColour(mColour);

    // Kingside castling
    Square * corner = &mParentBoard->GetSquare(backrank, Board::NumberOfRanks-1);
    Piece * piece = corner->pGetContent();
    if(!corner->IsEmpty() && piece->HasCastlingRights())
    {
        if(mParentBoard->GetSquare(backrank, 5).IsAttackedBy(opposite) == false
          && mParentBoard->GetSquare(backrank, 6).IsAttackedBy(opposite) == false
          && mParentBoard->GetSquare(backrank, 5).IsEmpty()
          && mParentBoard->GetSquare(backrank, 6).IsEmpty())
        {
            mLegalMoves.push_back(Move::ShortCastle());
        }
    }

    // Queenside castling
    corner = &mParentBoard->GetSquare(backrank, 0);
    piece = corner->pGetContent();
    if(!corner->IsEmpty() && piece->HasCastlingRights())
    {
        if(mParentBoard->GetSquare(backrank, 2).IsAttackedBy(opposite) == false
          && mParentBoard->GetSquare(backrank, 3).IsAttackedBy(opposite) == false
          && mParentBoard->GetSquare(backrank, 1).IsEmpty()
          && mParentBoard->GetSquare(backrank, 2).IsEmpty()
          && mParentBoard->GetSquare(backrank, 3).IsEmpty())
        {
            mLegalMoves.push_back(Move::LongCastle());
        }
    }
    
}


bool King::IsInCheck() const
{
    return mParentBoard->GetSquare(mLocation[0], mLocation[1]).IsAttackedBy(OppositeColour(mColour));
}


bool King::HasCastlingRights() const
{
    return !mHasMoved;
}


void King::RemoveCastlingRights()
{
    mHasMoved = true;
}


}
