#include "piece.h"
#include "board/board.h"

namespace ConsoleChess {


Piece::Piece(const int & rank, const int & file, const Board * parent_board, const Colour & colour) :
     mParentBoard(parent_board),
     mColour(colour)
{
    mLocation[0] = rank;
    mLocation[1] = file;
    mPieceType = PieceSet::NONE;
}

void Piece::ChangeBoard(const Board * rNewBoard)
{
    this->mParentBoard = rNewBoard;
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

bool Piece::CheckIfCaptures(const int & rank, const int & file) const
{
    const Colour opposite_colour = this->mColour==Colour::WHITE ? Colour::BLACK : Colour::WHITE;

    if(mParentBoard->GetColourOccupied(rank, file) == opposite_colour) return true;

    return false;
}

const std::vector<Move> & Piece::GetMoves() const
{
    return mLegalMoves;
}

std::vector<Move> & Piece::GetMoves()
{
    return mLegalMoves;
}

PieceSet Piece::GetPieceType() const
{
    return mPieceType;
}

Colour Piece::GetColour() const
{
    return mColour;
}

/**
 * @brief Piece::StraightLineMoveUpdate adds moves that are in the same line (same rank, file or diagonal in one of the two directions).
 * Stops at the end of the board, at same-colour piece and at oposite piece.
 * @param delta_r
 * @param delta_f
 */
void Piece::StraightLineMoveUpdate(const int delta_r, const int delta_f)
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
            break; // Cannot move to square occupied by same-colour piece or beyond board's edge
        }
    }
}

/**
 * @brief Defalt value for IsInCheck method. Only the king should override
 * 
 * @return true: It's a king and it's in check
 * @return false: Either it's not a king or it's a king and not in check
 */
bool Piece::IsInCheck() const
{
    return false;
}


}
