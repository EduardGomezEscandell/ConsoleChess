#include "square.h"
#include "board/board.h"

namespace ConsoleChess
{

Square::Square() :
      mWhiteAttacks(false),
      mBlackAttacks(false),
      mRank(0),
      mFile(0)
{}

void Square::SetLocation(const unsigned int Rank, const unsigned int File, Board * pOwner)
{
    mFile = File;
    mRank = Rank;
    mpOwner = pOwner;
}

void Square::SwapContent(Square & rOther)
{
    this->mContent.swap(rOther.mContent);
}

void Square::SwapContent(std::unique_ptr<Piece> & rpPiece)
{
    this->mContent.swap(rpPiece);
}

Piece * Square::CloneContent(const Square & rRHS)
{
    if(rRHS.IsEmpty())
    {
        mContent.reset();
    }
    else
    {
        auto p_copy = std::unique_ptr<Piece>(rRHS.mContent->Clone(mpOwner));
        SwapContent(p_copy);
    }

    return mContent.get();
}


bool Square::IsAttackedBy(Colour attacker)
{
    switch(attacker)
    {
        case Colour::WHITE: return mWhiteAttacks;
        case Colour::BLACK: return mBlackAttacks;
        default: return false;
    }
}

void Square::SetAttack(Colour attacker)
{
    switch(attacker)
    {
        case Colour::WHITE: mWhiteAttacks = true;  break;
        case Colour::BLACK: mBlackAttacks = true;  break;
        default: break;
    }
}


void Square::UnsetAttack(Colour attacker)
{
    switch(attacker)
    {
        case Colour::WHITE: mWhiteAttacks = false;  break;
        case Colour::BLACK: mBlackAttacks = false;  break;
        default: break;
    }
}


void Square::ResetAttack()
{
    mWhiteAttacks = false;
    mBlackAttacks = false;
}


void Square::Reset()
{
    mContent.reset();
    ResetAttack();
}

bool Square::IsEmpty() const
{
    return !static_cast<bool>(mContent);
}

std::string Square::GetName(int rank, int file)
{
    std::string s;
    
    if(rank <0 || rank>=Board::NumberOfRanks)
    {
        s.push_back('?');
    } else {
        s.push_back('a' + file);
    }

    if(file <0 || file>=Board::NumberOfFiles)
    {
        s.push_back('?');
    } else {
        s.push_back('1' + rank);
    }

    return s;
}


Piece * Square::pGetContent()
{
    return mContent.get();
}


const Piece * Square::pGetContent() const
{
    return mContent.get();
}

} // namespace ConsoleChess