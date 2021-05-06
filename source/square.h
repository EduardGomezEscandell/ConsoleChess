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
    void ResetContent();
    void SwapContent(Square & rOther);
    void SwapContent(std::unique_ptr<Piece> & rpPiece);

    unsigned int GetRank() const;
    unsigned int GetFile() const;

    Piece * pGetContent();
    const Piece * pGetContent() const;
    Piece * CloneContent(const Square & rRHS);

    bool IsAttackedBy(Colour attacker);
    void SetAttack(Colour attacker);
    void UnsetAttack(Colour attacker);
    void ResetAttack();

    bool IsEmpty() const;

    static std::string GetName(int rank, int file);
    std::string GetName() const;

    template<typename TPieceType, typename ... Types>
    Piece * NewPiece(Types ... args)
    {
        mContent.reset();
        mContent = std::make_unique<TPieceType>(args...);
        return mContent.get();
    }

    bool ValidateMove(PieceSet piece_type, const int rank, const int file, Colour colour) const;

protected:
    std::unique_ptr<Piece> mContent;
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