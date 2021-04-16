#ifndef DEFINES_H
#define DEFINES_H


namespace ConsoleChess {


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

enum class File
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

struct Move
{
    const int initial_rank;
    const int initial_file;
    const int destination_rank;
    const int destination_file;
};



}

#endif // DEFINES_H
