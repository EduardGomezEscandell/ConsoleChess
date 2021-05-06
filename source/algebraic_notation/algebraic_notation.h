#ifndef CHESS_ALGEBRAIC_READER
#define CHESS_ALGEBRAIC_READER

#include "../defines.h"
#include "../move.h"
#include <string_view>

namespace ConsoleChess
{

class AlgebraicReader
{
public:
    static bool ParseMove(PieceSet & rPiece, Move& rMove, std::string rInput);

protected:

    static void ProcessTrailingCharacters(std::string & rInput);
    static void ProcessPawnPromotion(Move & rMove, std::string & rInput);
    static void ReadDestination(Move & rMove, std::string & rInput);
    static void ReadLeadingCharacters(Move & rMove, const std::string & rInput);

    static PieceSet CharToPiece(const char c);
};

} // namespace ConsoleChess

#endif