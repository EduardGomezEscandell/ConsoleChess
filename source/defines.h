#ifndef CHESS_DEFINES_H
#define CHESS_DEFINES_H

#include <ostream>
#include <sstream>

#define CHESS_THROW throw ChessError(__FILE__, __LINE__)

namespace ConsoleChess {

class ChessError : std::exception
{
public:
    ChessError(const char * file, const int line)
    {
        std::stringstream ss;
        ss << "Error at " << file << ":" << line <<"\n  ";
        mMessage = ss.str();
    }

    ChessError(const ChessError & rRHS) = default;

    const char * what () const throw () {return &(mMessage[0]);}

    template<typename T>
    ChessError & operator<<(const T & RHS)
    {
        std::stringstream ss;
        ss << mMessage << RHS;
        mMessage = ss.str();
        return *this;
    }

protected:
    std::string mMessage;
};

enum class Result : int
{
    FAILURE = 2,
    ERROR = 1,
    SUCCESS = 0
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

// Note that white=-black. This is important for quick colour flipping.
enum class Colour : short
{
    WHITE = -1,
    BLACK = 1,
    UNDEFINED = -2,
    BOTH = 2
};

Colour OppositeColour(const Colour c);

std::ostream& operator<<(std::ostream& os, const PieceSet& p);

}

#endif // CHESS_DEFINES_H
