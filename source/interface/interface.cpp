#include "interface.h"
#include "../algebraic_notation/algebraic_notation.h"

#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstring>

#include <stdlib.h>
#include <time.h>

namespace ConsoleChess{


Colour Interface::Intro()
{
    std::cout << "Console Chess v0.0." << std::endl;
    std::map<std::string, Colour> options = {{"w", Colour::WHITE}, {"b", Colour::BLACK}, {"r",Colour::UNDEFINED}};
    Colour colour = Question("What colour are you going to play?", options);

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
        CHESS_THROW <<"\nUnreachable code reached.";
    }
    return colour;
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

Move Interface::AskMove(const Board & rBoard)
{
    Move move;
    bool is_valid = false;

    while(!is_valid)
    {
        std::cout << "Enter your move: ";
        std::string answer;
        std::cin >> answer;

        std::tie(move, is_valid) = Interface::ParseAndValidateMove(answer, rBoard);

        if(!is_valid) std::cout << "Invalid move.\n";
    }

    return move;
}


std::tuple<Move, bool> Interface::ParseAndValidateMove(const std::string & input, const Board & rBoard)
{


    PieceSet piece, promotion;
    Move candidate_move;

    bool is_valid =  AlgebraicReader::ParseMove(piece, promotion, candidate_move, input);

    if(!is_valid) return std::tie(candidate_move, is_valid);


    is_valid = rBoard.ValidateAndCompleteMove(candidate_move, piece, promotion);

    return std::tie(candidate_move, is_valid);
}

}
