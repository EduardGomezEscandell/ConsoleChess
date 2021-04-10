#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

namespace ChessConsole {

#include "defines.h"

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

#endif // PLAYER_H
