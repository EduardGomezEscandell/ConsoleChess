#include "game.h"
#include "interface/interface.h"


namespace ConsoleChess {

Game::Game()
{
    mBoard.SetUpInitialPieces();
}

void Game::Run()
{
    Colour c = Interface::Intro();

    bool game_is_over = false;
    while(!game_is_over)
    {
        game_is_over = PlayerTurn();
    }
}

/**
 * @brief Game::PlayerTurn
 * @return Whether the game is over
 */
bool Game::PlayerTurn()
{
    Interface::DisplayBoard(mBoard);
    
    mBoard.UpdateLegalMoves();
    auto move = Interface::AskMove(mBoard);
    mBoard.DoMove(move);

    return false;
}

}
