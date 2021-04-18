#include "move.h"
#include "board/board.h"

namespace ConsoleChess {


Move::Move(const unsigned int & departure_rank,
           const unsigned int & departure_file,
           const unsigned int & landing_rank,
           const unsigned int & landing_file) :
    departure_rank(departure_rank),
    departure_file(departure_file),
    landing_rank(landing_rank),
    landing_file(landing_file)
{}

std::ostream& operator<<(std::ostream& os, const Move& m)
{
    os << "Move[";
    os << Board::GetSquareName(m.departure_file, m.departure_rank);
    os << "->";
    os << Board::GetSquareName(m.landing_file, m.landing_rank);
    os << "]";
    return os;
}

bool operator==(const Move & rLHS, const Move & rRHS)
{
    return rLHS.departure_rank == rRHS.departure_rank
        && rLHS.departure_file == rRHS.departure_file
        && rLHS.landing_rank == rRHS.landing_rank
        && rLHS.landing_file == rRHS.landing_file;
}

}
