#ifndef INTERFACE_H
#define INTERFACE_H

#include "defines.h"
#include <iostream>
#include <vector>

namespace ConsoleChess {


class Interface
{
public:
    Interface() {}

    static int Intro();

    void AskMove();

protected:

    static int Question(char const* querry, char const* options);
    static std::string BuildQuestion(char const* querry, char const* options);
    static int ChooseRandomColour();


};

}

#endif // INTERFACE_H
