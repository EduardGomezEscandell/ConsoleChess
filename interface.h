#ifndef CHESS_INTERFACE_H
#define CHESS_INTERFACE_H

#include <iostream>
#include <vector>

#include "defines.h"
#include "board/board.h"

namespace ConsoleChess {


class Interface
{
public:
    Interface() {}

    static int Intro();

    static void DisplayBoard(const Board & rBoard);

protected:

    static int Question(char const* querry, char const* options);
    static std::string BuildQuestion(char const* querry, char const* options);
    static int ChooseRandomColour();

};

}

#endif // CHESS_INTERFACE_H
