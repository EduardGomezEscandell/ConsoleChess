#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <memory>
#include "defines.h"

namespace ConsoleChess {


class Player
{
public:
    Player(int colour)
        : mColour(colour)
    {
    }

    const int& GetColour()
    {
        return mColour;
    }

protected:
    const int mColour;

};

}

#endif // CHESS_PLAYER_H
