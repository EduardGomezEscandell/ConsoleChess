#include "game.h"
#include "fen/FEN.h"
#include "interface/interface.h"


namespace ConsoleChess {

Game::Game()
{
}

void Game::Run()
{
    Interface::Intro();

    const int option = Interface::StartMenu();

    switch (option)
    {
    case 1:
        mpBoard = std::make_unique<Board>();
        mpBoard->SetUpInitialPieces();
        break;
    case 2:
        mpBoard = std::make_unique<Board>(Interface::ReadFEN());
        break;
    default:
        break;
    }

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
#ifndef NDEBGUG
    if(!mpBoard) CHESS_THROW << "Tried to make a player turn with no board";
#endif

    Interface::DisplayBoard(*mpBoard);
    
    mpBoard->UpdateLegalMoves();
    auto move = Interface::AskMove(*mpBoard);
    mpBoard->DoMove(move);

    return false;
}

}
