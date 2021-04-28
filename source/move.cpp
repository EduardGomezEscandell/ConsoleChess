#include "move.h"
#include "square.h"
#include "board/board.h"

namespace ConsoleChess {


Move::Move(const int & departure_rank,
           const int & departure_file,
           const int & landing_rank,
           const int & landing_file) :
    departure_rank(departure_rank),
    departure_file(departure_file),
    landing_rank(landing_rank),
    landing_file(landing_file)
{}

std::ostream& operator<<(std::ostream& os, const Move& m)
{
    os << "Move[";
    os << Square::GetName(m.departure_file, m.departure_rank);
    os << "->";
    os << Square::GetName(m.landing_file, m.landing_rank);
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
