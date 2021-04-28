#include "game.h"
#include "interface/interface.h"


namespace ConsoleChess {

Game::Game()
{
    mBoard.SetUpInitialPieces();
}

void Game::Run()
{
    Interface::Intro();
}

/**
 * @brief Game::PlayerTurn
 * @param turn_number: The current turn.
 * @return Whether the game is over
 */
bool Game::PlayerTurn(const unsigned int turn_number)
{
    Interface::DisplayBoard(mBoard);
    //Player * player = mPlayers[turn_number % 2].get();

    //auto move = Interface::AskMove(mBoard);

    return false;

}

}
