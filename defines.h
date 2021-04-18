#ifndef CHESS_DEFINES_H
#define CHESS_DEFINES_H

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
    UNDEFINED
};

enum class File : int
{
    a = 0,
    b = 1,
    c = 2,
    d = 3,
    e = 4,
    f = 5,
    g = 6,
    h = 7,
    undefined = -1
};


}

#endif // CHESS_DEFINES_H
