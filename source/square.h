#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "defines.h"
#include "memory"
#include "piece.h"

namespace ConsoleChess
{

class Square
{
public:
    void Vacate();
    void SwapContent(Square & rOther);
    void OverwriteContent(Piece * rpPiece);

    unsigned int GetRank() const;
    unsigned int GetFile() const;

    Piece * pGetContent();
    const Piece * pGetContent() const;

    bool IsAttackedBy(Colour attacker);
    void SetAttack(Colour attacker);
    void UnsetAttack(Colour attacker);
    void ResetAttack();

    bool IsEmpty() const;

    static std::string GetName(int rank, int file);
    std::string GetName() const;

    bool ValidateMove(PieceSet piece_type, const int rank, const int file, Colour colour) const;

protected:
    Piece * mContent = nullptr;
    bool mWhiteAttacks;
    bool mBlackAttacks;

    unsigned int mRank;
    unsigned int mFile;

    friend class Board;
    Board * mpOwner;

    Square();
    void SetLocation(const unsigned int Rank, const unsigned int File, Board * pOwner);
    void Reset();
};

} // namespace ConsoleChess


#endif