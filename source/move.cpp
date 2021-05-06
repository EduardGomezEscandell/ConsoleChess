#include "move.h"
#include "square.h"
#include "board/board.h"

namespace ConsoleChess {

Move::Move(DataType data)
{
    mData = data;
}

Move::Move(const int & departure_rank,
           const int & departure_file,
           const int & landing_rank,
           const int & landing_file)
{
    mData = 0;
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
    return Move(ShortCastle_mask);
}


Move Move::LongCastle()
{
    return Move(LongCastle_mask);
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
    return rLHS.mData == rRHS.mData;
}


void Move::SetDepartureRank(unsigned int rank)
{
    mData = mData & ~DepRank_mask;                      // Unsetting rank
    mData = mData | ((ThreeDigit_mask & rank) << 13);   // Setting rank
    mData = mData | KnownDR_mask;                       // Setting DR as known
}

void Move::SetDepartureFile(unsigned int file)
{
    mData = mData & ~DepFile_mask;                      // Unsetting file
    mData = mData | ((ThreeDigit_mask & file) << 10);   // Setting file
    mData = mData | KnownDF_mask;                       // Setting DR as known
}

void Move::SetLandingRank(unsigned int rank)
{
    mData = mData & ~LanRank_mask;                      // Unsetting rank
    mData = mData | ((ThreeDigit_mask & rank) << 7);    // Setting rank
}

void Move::SetLandingFile(unsigned int file)
{
    mData = mData & ~LanFile_mask;                      // Unsetting file
    mData = mData | ((ThreeDigit_mask & file) << 4);    // Setting file
}

void Move::UnsetDepartureRank()
{
    mData = mData & ~KnownDR_mask;
}

void Move::UnsetDepartureFile()
{
    mData = mData & ~KnownDF_mask;
}

void Move::SetShortCastle(bool set)
{
    if(set)
    {
        mData = mData & ShortCastle_mask;
    } 
    else 
    {
        mData = mData & ~ShortCastle_mask;
    }
}

void Move::SetLongCastle(bool set)
{
    if(set)
    {
        mData = mData & LongCastle_mask;
    } 
    else 
    {
        mData = mData & ~LongCastle_mask;
    }
}


int Move::GetDepartureRank() const
{
    return static_cast<int>((DepRank_mask & mData) >> 13);
}


int Move::GetDepartureFile() const
{
    return static_cast<int>((DepFile_mask & mData) >> 10);
}


int Move::GetLandingRank() const
{
    return static_cast<int>((LanRank_mask & mData) >> 7);
}


int Move::GetLandingFile() const
{
    return static_cast<int>((LanFile_mask & mData) >> 4);
}


bool Move::IsDepartureRankKnown() const
{
    return static_cast<bool>(KnownDR_mask & mData);
}


bool Move::IsDepartureFileKnown() const
{
    return static_cast<bool>(KnownDF_mask & mData);
}


bool Move::GetShortCastle() const
{
    return static_cast<bool>(ShortCastle_mask & mData);
}


bool Move::GetLongCastle() const
{
    return static_cast<bool>(LongCastle_mask & mData);
}



}
