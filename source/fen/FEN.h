#ifndef CHESS_FEN
#define CHESS_FEN

#include "../board/board.h"

namespace ConsoleChess
{
namespace FEN
{
    Board Reader(const char * fen);
    std::string Writer(const Board & board);
}
}


#endif