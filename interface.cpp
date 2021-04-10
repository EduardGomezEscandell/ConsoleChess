#include "interface.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>

#include <stdlib.h>
#include <time.h>

namespace ConsoleChess{


int Interface::Intro()
{
    std::cout << "Console Chess v0.0." << std::endl;
    int colour =  Question("What colour are you going to play?", "wbr");

    if(colour != Colour::Undefined)
    {
        std::cout << "You selected ";
    }
    else
    {
        colour = ChooseRandomColour();
        std::cout << "Randomly selected ";
    }

    switch (colour) {
    case Colour::Black:
        std::cout << "black." << std::endl;
        break;
    case Colour::White:
        std::cout << "white." << std::endl;
        break;
    default:
        std::cerr <<"Unreachable code reached in " << __FILE__ <<":"<<__LINE__<<std::endl;
        throw;
    }
    return colour;
}


std::string Interface::BuildQuestion(char const* querry, char const* options)
{
    std::stringstream ss;
    ss << querry << " (";

    bool first = true;
    for(const char *opt = options; *opt != '\0'; opt++)
    {
        if(!first)
        {
            ss << "|";
        }
        ss << *opt;
        first = false;
    }
    ss << "): ";
    return ss.str();
}

int Interface::Question(char const* querry, char const* options)
{
    std::string question = BuildQuestion(querry, options);

    bool valid_answer = false;
    while(!valid_answer)
    {
        std::cout << question;

        std::cin.clear();

        char answer = std::cin.get();

        const char * search_result = strchr(options, answer);

        if(search_result)
        {
            return static_cast<int>(search_result - options);
        }
    }

    std::cerr <<"Unreachable code reached in " << __FILE__ <<":"<<__LINE__<<std::endl;
    throw;
}

int Interface::ChooseRandomColour()
{
    srand(time(nullptr));
    return rand() % 2;
}

}
