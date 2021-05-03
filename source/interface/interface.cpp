#include "interface.h"
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
        std::cerr <<"\nUnreachable code reached in " << __FILE__ <<":"<<__LINE__<<std::endl;
        throw;
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

bool IsALetter(const char & c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

#define NEXT_CHARACTER_OR_RETURN_TRUE(it, str)  \
it++;                                           \
if(it == str.rend()){                           \
    return true;                                \
}                                               \

#define NEXT_CHARACTER_OR_THROW(it, str)        \
it++;                                           \
if(it == str.rend()){                           \
    throw std::runtime_error("Wrong input");    \
}                                               \


PieceSet Interface::GetPieceFromChar(const char c)
{
    switch (c) {
        case 'R':   return PieceSet::ROOK;
        case 'B':   return PieceSet::BISHOP;
        case 'Q':   return PieceSet::QUEEN;
        case 'K':   return PieceSet::KING;
        case 'N':   return PieceSet::KNIGHT;
        default:    return PieceSet::NONE;
    }
}


/**
 * Parses the move specified as a string and returns the gathered info. Unknown values are set as -1
 */
bool Interface::ParseMove(PieceSet & piece, PieceSet & promotion, Move& rMove, std::string input)
{
    /* Move notation:
     *
     * [Piece] [departure file][Departure rank] [x] {Landing file}{Landing Rank} [= Promotion][+|=|#]
     * [] is optional
     * {} is compulsory
     * It is simpler to parse from the back towards the front
     */
    std::string::reverse_iterator it = input.rbegin();

    try 
    {
        if(*it == '=') // Draw offers are ignored for now
        {
            NEXT_CHARACTER_OR_THROW(it, input);
        }

        if(*it == '+') // Check is ignored
        {
            NEXT_CHARACTER_OR_THROW(it, input);
        }

        if(*it == '#') // Checkmate is ignored
        {
            NEXT_CHARACTER_OR_THROW(it, input);
        }

        const auto last_item = input.end()-1; // Distinguishing between draw offer and promotion marker
        auto tmp = std::find(input.begin(), last_item, '='); // Finding promotion marker

        // Dealing with promotion
        if(tmp != last_item)
        {
            tmp++;
            promotion = GetPieceFromChar(*tmp);
            
            // Advancing past = sign
            NEXT_CHARACTER_OR_THROW(it, input);
            NEXT_CHARACTER_OR_THROW(it, input);

        } else {
            promotion = PieceSet::NONE;
        }

        piece = PieceSet::PAWN; // default value
        rMove = {-1,-1,-1,-1};

        // Getting Landing rank
        rMove.landing_rank = *it - '1';
        
        NEXT_CHARACTER_OR_THROW(it, input);

        // Gettings Landing file
        rMove.landing_file = *it - 'a';

        NEXT_CHARACTER_OR_RETURN_TRUE(it, input);

        // Ignoring capture
        if(*it == 'x')
        {
            NEXT_CHARACTER_OR_RETURN_TRUE(it, input);
        }

        // Getting [departure file][Departure rank]

        switch(std::distance(it, input.rend())) {
        case 3:
            // [Piece][departure file][Departure rank]
            rMove.departure_rank = *it - '0';
            it++;
            rMove.departure_file = *it - 'a';
            it++;
            break;
        case 2:
            // [Piece][departure file] OR [Piece][Departure rank]. --- [Departure file][Departure rank] is impossible: two pawns cannot attack the same square from the same file.
            if(*it >= 'a' && *it <= 'h') // It's a file
            {
                rMove.departure_file = *it - 'a';
            } else if(*it >= '0' && *it <= '9') { // It's a rank
                rMove.departure_rank = *it - '0';
            } else {
                throw std::runtime_error("Wrong input");
            }
            it++;
            break;
        case 1:
            // [Piece] OR [departure file] OR [departure rank]
            if(*it >= 'A' && *it <= 'Z') // It's potentially a piece
            {
                break;
            }
            if(*it >= 'a' && *it <= 'h') // It's a file
            {
                rMove.departure_file = *it - 'a';
            } else if(*it >= '0' && *it <= '9') { // It's a rank
                rMove.departure_rank = *it - '0';
            } else {
                throw std::runtime_error("Wrong input");
            }
            return true;
        default:
            throw std::runtime_error("Wrong input");
        }

        // Getting [Piece]
        piece = GetPieceFromChar(*it);
        
        if(piece == PieceSet::NONE)
        {
            throw std::runtime_error("Unrecognized piece type");
        }
        
        return true;
    }
    catch (...)
    {
        // Cleaning up
        piece     = PieceSet::NONE;
        promotion = PieceSet::NONE;
        rMove = {-1,-1,-1,-1};
        return false;
    }
}



std::tuple<Move, bool> Interface::ParseAndValidateMove(const std::string & input, const Board & rBoard)
{


    PieceSet piece, promotion;
    Move candidate_move;

    bool is_valid =  ParseMove(piece, promotion, candidate_move, input);

    if(!is_valid) return std::tie(candidate_move, is_valid);


    is_valid = rBoard.ValidateAndCompleteMove(candidate_move, piece, promotion);

    return std::tie(candidate_move, is_valid);
}

}
