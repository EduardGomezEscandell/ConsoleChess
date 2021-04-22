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


void Bishop::UpdateLegalMoves()
{
    mLegalMoves.clear();

    this->StraightLineMoveUpdate( 1, 1);
    this->StraightLineMoveUpdate( 1,-1);
    this->StraightLineMoveUpdate(-1, 1);
    this->StraightLineMoveUpdate(-1,-1);
}


}
