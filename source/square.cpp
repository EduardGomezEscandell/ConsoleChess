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

unsigned int Square::GetRank() const
{
    return mRank;
}

unsigned int Square::GetFile() const
{
    return mFile;
}



void Square::SetLocation(const unsigned int Rank, const unsigned int File, Board * pOwner)
{
    mRank = Rank;
    mFile = File;
    mpOwner = pOwner;
}

void Square::Vacate()
{
    if(mContent) mContent->SetAliveState(false);
    mContent = nullptr;
}

void Square::SwapContent(Square & rOther)
{
    Piece * tmp = rOther.mContent;
    rOther.mContent = this->mContent;
    this->mContent = tmp;
}

void Square::OverwriteContent(Piece * rPiece)
{
    this->Vacate();
    this->mContent = rPiece;
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
    Vacate();
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

std::string Square::GetName() const
{
    return Square::GetName(mRank, mFile);
}


Piece * Square::pGetContent()
{
    return mContent;
}


const Piece * Square::pGetContent() const
{
    return mContent;
}


bool Square::ValidateMove(PieceSet piece_type, const int rank, const int file, Colour colour) const
{
    if(IsEmpty()) return false;                             // The square is empty

    const Piece * piece = this->pGetContent();  

    if(piece->GetColour() != colour) return false;          // It's an enemy piece
    if(piece->GetPieceType() != piece_type) return false;   // It's the wrong piece

    if(piece->CanMoveTo(rank, file))
    {
        return true;
    }
    else
    {
        return false;
    }
}

} // namespace ConsoleChess