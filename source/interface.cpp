#include "interface.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

#include <stdlib.h>
#include <time.h>

namespace ConsoleChess{


int Interface::Intro()
{
    std::cout << "Console Chess v0.0." << std::endl;
    Colour colour = (Colour) Question("What colour are you going to play?", "wbr");

    if(colour != Colour::UNDEFINED)
    {
        std::cout << "You selected ";
    }
    else
    {
        colour = (Colour) ChooseRandomColour();
        std::cout << "Randomly selected ";
    }

    switch (colour) {
    case Colour::BLACK:
        std::cout << "black." << std::endl;
        break;
    case Colour::WHITE:
        std::cout << "white." << std::endl;
        break;
    default:
        std::cerr <<"\nUnreachable code reached in " << __FILE__ <<":"<<__LINE__<<std::endl;
        throw;
    }
    return (int) colour;
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

        std::string answer;
        std::cin >> answer;

        const char * search_result = strchr(options, answer[0]);

        if(search_result)
        {
            return static_cast<int>(search_result - options);
        }

        std::cout << "Unrecognized input.\n";
    }

    std::cerr <<"Unreachable code reached in " << __FILE__ <<":"<<__LINE__<<std::endl;
    throw;
}

int Interface::ChooseRandomColour()
{
    srand(time(nullptr));
    return  (rand() % 2);
}

void Interface::DisplayBoard(const Board & rBoard)
{
    std::cout << rBoard;
}

}
