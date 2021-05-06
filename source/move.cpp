#include "move.h"
#include "square.h"
#include "board/board.h"

namespace ConsoleChess {

Move Move::MoveFromBits(uint16_t data16, uint8_t data8)
{
    Move m;
    m.mData16 = data16;
    m.mData8 = data8;

    return m;
}

Move::Move(const int & departure_rank,
           const int & departure_file,
           const int & landing_rank,
           const int & landing_file)
{
    mData16 = 0;
    if(departure_rank>=0) SetDepartureRank(departure_rank);
    if(departure_file>=0) SetDepartureFile(departure_file);
    if(landing_rank>=0)   SetLandingRank(landing_rank);
    if(landing_file>=0)   SetLandingFile(landing_file);
}

Move::Move(const int & landing_rank,
           const int & landing_file)
{
    if(landing_rank>=0)   SetLandingRank(landing_rank);
    if(landing_file>=0)   SetLandingFile(landing_file);

}

Move::Move()
{
}


Move Move::ShortCastle()
{
    return Move(ShortCastle_mask, 0);
}


Move Move::LongCastle()
{
    return Move(LongCastle_mask, 0);
}


std::ostream& operator<<(std::ostream& os, const Move& m)
{   
    const int departure_rank = m.IsDepartureRankKnown() ? m.GetDepartureRank() : -1;
    const int departure_file = m.IsDepartureFileKnown() ? m.GetDepartureFile() : -1;

    os << "Move[";
    os << Square::GetName(departure_rank, departure_file);
    os << "->";
    os << Square::GetName(m.GetLandingFile(), m.GetLandingRank());
    os << "]";
    return os;
}

bool operator==(const Move & rLHS, const Move & rRHS)
{
    return rLHS.mData16 == rRHS.mData16 && rLHS.mData8 == rRHS.mData8;
}


void Move::SetDepartureRank(unsigned int rank)
{
    mData16 = mData16 & ~DepRank_mask;                      // Unsetting rank
    mData16 = mData16 | ((ThreeDigit_mask & rank) << 13);   // Setting rank
    mData16 = mData16 | KnownDR_mask;                       // Setting DR as known
}

void Move::SetDepartureFile(unsigned int file)
{
    mData16 = mData16 & ~DepFile_mask;                      // Unsetting file
    mData16 = mData16 | ((ThreeDigit_mask & file) << 10);   // Setting file
    mData16 = mData16 | KnownDF_mask;                       // Setting DR as known
}

void Move::SetLandingRank(unsigned int rank)
{
    mData16 = mData16 & ~LanRank_mask;                      // Unsetting rank
    mData16 = mData16 | ((ThreeDigit_mask & rank) << 7);    // Setting rank
}

void Move::SetLandingFile(unsigned int file)
{
    mData16 = mData16 & ~LanFile_mask;                      // Unsetting file
    mData16 = mData16 | ((ThreeDigit_mask & file) << 4);    // Setting file
}

void Move::UnsetDepartureRank()
{
    mData16 = mData16 & ~KnownDR_mask;
}

void Move::UnsetDepartureFile()
{
    mData16 = mData16 & ~KnownDF_mask;
}

void Move::SetShortCastle(bool set)
{
    if(set)
    {
        mData16 = mData16 & ShortCastle_mask;
    } 
    else 
    {
        mData16 = mData16 & ~ShortCastle_mask;
    }
}

void Move::SetLongCastle(bool set)
{
    if(set)
    {
        mData16 = mData16 & LongCastle_mask;
    } 
    else 
    {
        mData16 = mData16 & ~LongCastle_mask;
    }
}

void Move::SetPromotion(PieceSet piece)
{
    uint8_t info = 0;

    switch (piece)
    {
    case PieceSet::QUEEN:   info=0b100; break;
    case PieceSet::ROOK:    info=0b101; break;
    case PieceSet::BISHOP:  info=0b110; break;
    case PieceSet::KNIGHT:  info=0b111; break;    
    default:                info=0b000;
    }

    mData8 = mData8 & ~Promotion_mask;  // Resetting promotion bits
    mData8 = mData8 | info;             // Setting promotion bits
}

int Move::GetDepartureRank() const
{
    return static_cast<int>((DepRank_mask & mData16) >> 13);
}


int Move::GetDepartureFile() const
{
    return static_cast<int>((DepFile_mask & mData16) >> 10);
}


int Move::GetLandingRank() const
{
    return static_cast<int>((LanRank_mask & mData16) >> 7);
}


int Move::GetLandingFile() const
{
    return static_cast<int>((LanFile_mask & mData16) >> 4);
}


bool Move::IsDepartureRankKnown() const
{
    return static_cast<bool>(KnownDR_mask & mData16);
}


bool Move::IsDepartureFileKnown() const
{
    return static_cast<bool>(KnownDF_mask & mData16);
}


bool Move::GetShortCastle() const
{
    return static_cast<bool>(ShortCastle_mask & mData16);
}


bool Move::GetLongCastle() const
{
    return static_cast<bool>(LongCastle_mask & mData16);
}

PieceSet Move::GetPromotion() const
{
    uint8_t info = mData8 & Promotion_mask;

    if(info < 0b100) return PieceSet::NONE;

    switch (info)
    {
    case 0b100: return PieceSet::QUEEN;
    case 0b101: return PieceSet::ROOK;
    case 0b110: return PieceSet::BISHOP;
    case 0b111: return PieceSet::KNIGHT;
    default: CHESS_THROW << "Unreachable code reached";
    }
}


}
