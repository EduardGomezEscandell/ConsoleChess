#ifndef MOVE_H
#define MOVE_H

#include <ostream>

namespace ConsoleChess {


class Move
{
public:
    Move(const unsigned int & departure_rank,
         const unsigned int & departure_file,
         const unsigned int & landing_rank,
         const unsigned int & landing_file);

    /**
     * @brief Constructor to avoid compiler warnigs about int->uint conversions
     * @param departure_rank
     * @param departure_file
     * @param landing_rank
     * @param landing_file
     */
    Move(const int & departure_rank,
         const int & departure_file,
         const int & landing_rank,
         const int & landing_file) :
        Move(static_cast<unsigned int>(departure_rank),
             static_cast<unsigned int>(departure_file),
             static_cast<unsigned int>(landing_rank),
             static_cast<unsigned int>(landing_file))
    {};

    unsigned int departure_rank;
    unsigned int departure_file;
    unsigned int landing_rank;
    unsigned int landing_file;

};

std::ostream& operator<<(std::ostream& os, const Move& m);

bool operator==(const Move &, const Move &);

}

#endif // MOVE_H
