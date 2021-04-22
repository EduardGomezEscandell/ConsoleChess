#include "game.h"
#include "interface.h"


namespace ConsoleChess {

Game::Game()
{
    mBoard.SetUpInitialPieces();
}

void Game::Run()
{
    Interface::Intro();
    Interface::DisplayBoard(mBoard);
}

}
