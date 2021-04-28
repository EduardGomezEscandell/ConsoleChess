#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "defines.h"
#include "move.h"
#include <vector>
#include <memory>

#define CHESS_DEFINE_PIECE_BOILERPLATE(Name, NameCapitalized, Symbol)\
                                                        \
Name::Name(const int & rank,                            \
           const int & file,                            \
           Board * parent_board,                        \
           const Colour & colour)                       \
    : Piece(rank, file, parent_board, colour)           \
{                                                       \
        mPieceType = PieceSet::NameCapitalized;         \
}                                                       \
                                                        \
Piece * Name::Clone(Board * parent_board) const   \
{                                                       \
    Piece * ptr = new Name(*this);                      \
    ptr->ChangeBoard(parent_board);                     \
    return ptr;                                         \
}                                                       \
                                                        \
char Name::GetPieceCharacter() const                    \
{                                                       \
    static constexpr char c = Symbol;                   \
    return mColour==Colour::BLACK ? c : (c + 'A'-'a');  \
}                                                       \




namespace ConsoleChess {

class Board;

class Piece
{
public:
    virtual void UpdateLegalMoves() = 0;

    Piece(const int & rank, const int & file, Board * parent_board, const Colour & colour);

    virtual Piece * Clone(Board * parent_board) const = 0;

    PieceSet GetPieceType() const;
    Colour GetColour() const;

    std::vector<Move> & GetMoves();
    const std::vector<Move> & GetMoves() const;
    virtual char GetPieceCharacter() const = 0;
    void ChangeBoard(Board * rNewBoard);
    virtual bool IsInCheck() const;

protected:

    int mLocation[2];
    Board * mParentBoard;
    std::vector<Move> mLegalMoves;
    PieceSet mPieceType;
    const Colour mColour = Colour::UNDEFINED;

    friend class Board;

    bool CheckDestinationSquare(const int & rank, const int & file) const;
    bool CheckIfCaptures(const int & rank, const int & file) const;
    void StraightLineMoveUpdate(const int delta_r, const int delta_f);
};

}

#endif // CHESS_PIECE_H
