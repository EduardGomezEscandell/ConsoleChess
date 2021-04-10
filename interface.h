#ifndef INTERFACE_H
#define INTERFACE_H

#include "defines.h"
#include <iostream>
#include <vector>

namespace ChessConsole {


class Interface
{
public:
    Interface() {}

    static int Intro();

protected:

    static int Question(char const* querry, char const* options);
    static std::string BuildQuestion(char const* querry, char const* options);

};

}

#endif // INTERFACE_H
