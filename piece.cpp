#include "piece.h"
#include "board/board.h"

namespace ConsoleChess {


Piece::Piece(const int & rank, const int & file, const Board * parent_board, const Colour & colour) :
     mParentBoard(parent_board),
     mColour(colour)
{
    mLocation[0] = rank;
    mLocation[1] = file;
}

/**
 * @brief Checks whether the destination square is valid. Does not check if departure is valid (i.e. pins).
 * @param rank
 * @param file
 * @return true when the destination square is valid to land on.
 */
bool Piece::CheckDestinationSquare(const int & rank, const int & file) const
{
    if(rank >= 8 || rank < 0 || file < 0 || file >= 8) return false; // Checking if the destination is within the board

    if(mParentBoard->GetColourOccupied(rank, file) == this->mColour) return false; // Checking if the destination is occupied

    return true;
}

const std::vector<Move> & Piece::GetMoves() const
{
    return mLegalMoves;
}

std::vector<Move> & Piece::GetMoves()
{
    return mLegalMoves;
}

}
