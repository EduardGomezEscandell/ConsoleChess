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
                                                        \
PieceSet Name::GetPieceType() const                     \
{                                                       \
    return PieceSet::NameCapitalized;                   \
}                                                       \




namespace ConsoleChess {

class Board;

class Piece
{
public:
    // Constructors
    Piece(const int & rank, const int & file, Board * parent_board, const Colour & colour);
    
    /**
     * @brief Clone: This method allocates a raw pointer and copies the relevant information top clone the piece.
     * Ownership is granted to the caller, so it's recomended to use this method only to construct smart pointers.
     * @param parent_board: The board that will contain the clone.
     * @return Piece*: The raw pointer containing the clone.
     */
    virtual Piece * Clone(Board * parent_board) const = 0;
    
    // Editors
    virtual void UpdateLegalMoves() = 0;
    void SetLocation(const int & rank, const int & file);
    void ChangeBoard(Board * rNewBoard);
    void SetAliveState(bool alive);

    // Getters
    bool IsAlive() const;
    virtual PieceSet GetPieceType() const = 0;
    virtual char GetPieceCharacter() const = 0;
    std::vector<Move> & GetMoves();
    const std::vector<Move> & GetMoves() const;
    Colour GetColour() const;
    virtual void RemoveCastlingRights();
    
    // Queries
    virtual bool IsInCheck() const;
    bool CanMoveTo(const int rank, const int file) const;
    virtual bool HasCastlingRights() const;

protected:
    bool mIsAlive = true;
    int mLocation[2];
    Board * mParentBoard;
    std::vector<Move> mLegalMoves;
    const Colour mColour = Colour::UNDEFINED;

    friend class Board;

    // Editors
    void StraightLineMoveUpdate(const int delta_r, const int delta_f);
    
    // Queries
    bool CheckDestinationSquare(const int & rank, const int & file) const;
    bool CheckIfCaptures(const int & rank, const int & file) const;
};

}

#endif // CHESS_PIECE_H
