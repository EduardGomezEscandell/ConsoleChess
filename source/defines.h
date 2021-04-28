#ifndef CHESS_DEFINES_H
#define CHESS_DEFINES_H

#include <ostream>

namespace ConsoleChess {

enum class Result
{
    FAILURE, ERROR, SUCCESS
};

enum class PieceSet
{
    NONE,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class Verbosity
{
    NONE = 0,
    PROGRESS = 1,
    FULL = 2
};


enum class Colour
{
    WHITE,
    BLACK,
    UNDEFINED,
    BOTH
};


std::ostream& operator<<(std::ostream& os, const PieceSet& p);

}

#endif // CHESS_DEFINES_H
