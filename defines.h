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


}

#endif // CHESS_DEFINES_H
