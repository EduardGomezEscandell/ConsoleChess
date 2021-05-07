#include "pawn.h"

namespace ConsoleChess {

CHESS_DEFINE_PIECE_BOILERPLATE(Pawn, PAWN, 'o')

void Pawn::EmplaceMoveMaybePromote(const int DepartureRank,
                                   const int DepartureFile,
                                   const int LandingRank,
                                   const int LandingFile)
{
    if((LandingRank == 7 && mColour==Colour::WHITE)
        || (LandingRank == 0 && mColour==Colour::BLACK))
    {
        mLegalMoves.emplace_back(DepartureRank, DepartureFile, LandingRank, LandingFile, PieceSet::QUEEN);
        mLegalMoves.emplace_back(DepartureRank, DepartureFile, LandingRank, LandingFile, PieceSet::ROOK);
        mLegalMoves.emplace_back(DepartureRank, DepartureFile, LandingRank, LandingFile, PieceSet::BISHOP);
        mLegalMoves.emplace_back(DepartureRank, DepartureFile, LandingRank, LandingFile, PieceSet::KNIGHT);
    }
    else
    {
        mLegalMoves.emplace_back(DepartureRank, DepartureFile, LandingRank, LandingFile);
    }
}


void Pawn::UpdateLegalMoves()
{
    mLegalMoves.clear();

    const int initial_rank = mLocation[0];
    const int initial_file = mLocation[1];


    // Double-square move
    if(mColour==Colour::WHITE && initial_rank == 1 && CheckDestinationSquare(initial_rank+2, initial_file))
    {
        mLegalMoves.emplace_back(initial_rank, initial_file, initial_rank+2, initial_file);
    }
    if(mColour==Colour::BLACK && initial_rank == 6 && CheckDestinationSquare(initial_rank-2, initial_file))
    {
        mLegalMoves.emplace_back(initial_rank, initial_file, initial_rank-2, initial_file);
    }

    // Single-square moves
    const int target_rank = initial_rank + (mColour == Colour::WHITE ? 1 : -1);

    // Captures to the left
    if(initial_file > 0 && CheckIfCaptures(target_rank, initial_file-1))
    {
        EmplaceMoveMaybePromote(initial_rank, initial_file, target_rank, initial_file-1);
        mParentBoard->SetAttack(target_rank, initial_file-1, mColour);
    }

    // Captures to the right
    if(initial_file < 7 && CheckIfCaptures(target_rank, initial_file+1))
    {
        EmplaceMoveMaybePromote(initial_rank, initial_file, target_rank, initial_file+1);
        mParentBoard->SetAttack(target_rank, initial_file+1, mColour);
    }

    // Advances
    if(this->mParentBoard->pGetSquareContent(target_rank, initial_file) == nullptr)
    {
        EmplaceMoveMaybePromote(initial_rank, initial_file, target_rank, initial_file);
    }

}


}
