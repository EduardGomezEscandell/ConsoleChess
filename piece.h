#ifndef PIECE_H
#define PIECE_H

#include "defines.h"
#include <vector>

namespace ConsoleChess {

class Piece
{
public:
    Piece();
protected:
    std::vector<Move> mLegalMoves;
    int mLocation[2];
};

}

#endif // PIECE_H
