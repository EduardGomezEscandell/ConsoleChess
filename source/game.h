#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include "player.h"
#include "board/board.h"

namespace ConsoleChess   {

class Game
{
public:
    Game();

    void Run();

protected:
    std::unique_ptr<Player> mPlayers[2];
    Board mBoard;

    bool PlayerTurn();
};

}

#endif // CHESS_GAME_H

