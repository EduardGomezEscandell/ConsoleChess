#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <ostream>

namespace ConsoleChess {


class Move
{
public:
    Move(const int & departure_rank,
         const int & departure_file,
         const int & landing_rank,
         const int & landing_file);

    int departure_rank;
    int departure_file;
    int landing_rank;
    int landing_file;

};

std::ostream& operator<<(std::ostream& os, const Move& m);

bool operator==(const Move &, const Move &);

}

#endif // CHESS_MOVE_H
