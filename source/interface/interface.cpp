#include "interface.h"
#include "../algebraic_notation/algebraic_notation.h"
#include "../fen/FEN.h"

#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <regex>

#include <stdlib.h>
#include <time.h>

namespace ConsoleChess{


void Interface::Intro()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "     Console Chess v0.0\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
    // COMMENTED UNTIL COLOUR IS USED:
    
    // std::map<std::string, Colour> options = {{"w", Colour::WHITE}, {"b", Colour::BLACK}, {"r",Colour::UNDEFINED}};
    // Colour colour = Question("What colour are you going to play?", options);

    // if(colour != Colour::UNDEFINED)
    // {
    //     std::cout << "You selected ";
    // }
    // else
    // {
    //     colour = (Colour) ChooseRandomColour();
    //     std::cout << "Randomly selected ";
    // }

    // switch (colour) {
    // case Colour::BLACK:
    //     std::cout << "black." << std::endl;
    //     break;
    // case Colour::WHITE:
    //     std::cout << "white." << std::endl;
    //     break;
    // default:
    //     CHESS_THROW <<"\nUnreachable code reached.";
    // }
    // return colour;
}

int Interface::StartMenu()
{
    std::stringstream query;
    query << "Chose an option:\n"
          << " [1] Start game\n"
          << " [2] Import game in FEN format\n"
          << "Chose an option";

    std::map<std::string, int> options = {{"1", 1}, {"", 1}, {"2", 2}};
    return Interface::Question(query.str(), options);
}

Board Interface::ReadFEN()
{
    std::cout << "Write the game in Forsyth–Edwards Notation (FEN): ";
    bool valid_fen = false;
    
    std::string fen;
    while(!valid_fen)
    {
        std::cin >> fen;
        valid_fen = FEN::Validator(fen.c_str());

        if(!valid_fen)
        {
            std::cout << "Invalid FEN. Please check for any typos and try again: ";
        }
    }

    return FEN::Reader(fen.c_str());
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
        switch (rBoard.WhoMoves())
        {
            case Colour::WHITE: std::cout << "White to move. ";     break;
            case Colour::BLACK: std::cout << "Black to move. ";     break;
            default:    CHESS_THROW << "Unreachable code reached";
        }

        std::cout << "Enter a move or a /command: ";
        std::string answer;
        std::cin >> answer;

        if(answer[0] == '/')
        {
            Interface::RunCommand(answer, rBoard);
        }
        else
        {
            std::tie(move, is_valid) = Interface::ParseAndValidateMove(answer, rBoard);
            if(!is_valid) std::cout << "Invalid move.\n";
        }
    }

    return move;
}


std::tuple<Move, bool> Interface::ParseAndValidateMove(const std::string & input, const Board & rBoard)
{
    PieceSet piece;
    Move candidate_move;

    bool is_valid =  AlgebraicReader::ParseMove(piece, candidate_move, input);

    if(!is_valid) return std::tie(candidate_move, is_valid);
    
    is_valid = rBoard.ValidateAndCompleteMove(candidate_move, piece);

    return std::tie(candidate_move, is_valid);
}

void Interface::RunCommand(const std::string & command, const Board & rBoard)
{
    if(std::regex_match(command, std::regex(R"(\/help)")))
    {
        std::cout << "~~~~~ CONSOLECHESS HELP ~~~~~\n";
        std::cout << "  Enter a move in algebraic notation or a command preceded by a forward slash. Examples:\n";
        std::cout <<"     /help    will print this message\n";
        std::cout <<"     /fen     will print the current state of the board in FEN. " << std::endl;
        std::cout <<"     /board   will print the board again. " << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
    else if(std::regex_match(command, std::regex(R"(\/fen)")))
    {
        std::cout << "\n    " << FEN::Writer(rBoard) << "\n" << std::endl;
    }
    else if(std::regex_match(command, std::regex(R"(\/board)")))
    {
        std::cout << "\n" << rBoard.Display() << "\n";
    }
}

}
