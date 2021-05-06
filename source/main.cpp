#include "console_chess.h"
#include <iostream>

int main()
{
    try
    {
        auto game = ConsoleChess::Game();
        game.Run();
    }
    catch(const ConsoleChess::ChessError& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}


