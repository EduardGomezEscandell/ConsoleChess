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

    for(unsigned int i = 0; !game_is_over; i++)
    {
        PlayerTurn(i);
    }
}

/**
 * @brief Game::PlayerTurn
 * @param turn_number: The current turn.
 * @return Whether the game is over
 */
bool Game::PlayerTurn(const unsigned int turn_number)
{
    Interface::DisplayBoard(mBoard);
    
    mBoard.UpdateLegalMoves();
    auto move = Interface::AskMove(mBoard);
    mBoard.DoMove(move);

    return false;
}

}
