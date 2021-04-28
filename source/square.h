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
    void SwapContent(Square & rOther);
    void SwapContent(std::unique_ptr<Piece> & rpPiece);

    Piece * pGetContent();
    const Piece * pGetContent() const;
    Piece * CloneContent(const Square & rRHS);

    bool IsAttackedBy(Colour attacker);
    void SetAttack(Colour attacker);
    void UnsetAttack(Colour attacker);
    void ResetAttack();

    bool IsEmpty() const;

    static std::string GetName(int rank, int file);

    template<typename TPieceType, typename ... Types>
    Piece * NewPiece(Types ... args)
    {
        mContent.reset();
        mContent = std::make_unique<TPieceType>(args...);
        return mContent.get();
    }

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