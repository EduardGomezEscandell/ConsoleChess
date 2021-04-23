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

Move Interface::AskMove(const Board & rBoard)
{
       std::cout << "Enter your move: ";
       std::string answer;
       std::cin >> answer;



}

bool IsALetter(const char & c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

#define NEXT_CHARACTER_OR_RETURN_TRUE(it, str)  \
if(it != str.rend()){                           \
  it++;                                         \
} else {                                        \
    return true;                                \
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
bool Interface::ParseMove(PieceSet & piece, PieceSet & promotion, int& departure_rank, int& departure_file, int& landing_rank, int& landing_file, std::string input)
{
    /* Move notation:
     *
     *  [Piece] [departure file][Departure rank] [x] {Landing file}{Landing Rank} [= Promotion]
     * [] is optional
     * {} is compulsory
     * It is simpler to parse from the back towards the front
     */
    std::string::reverse_iterator it = input.rbegin();

    if(*it == '=') // Draw offers are ignored for now
    {
        NEXT_CHARACTER_OR_RETURN_TRUE(it, input);
    }

    if(*it == '+') // Check is ignored
    {
        NEXT_CHARACTER_OR_RETURN_TRUE(it, input);
    }

    if(*it == '#') // Checkmate is ignored
    {
        NEXT_CHARACTER_OR_RETURN_TRUE(it, input);
    }

    const auto penultimate_item = input.end()-1; // Distinguishing between draw offer and promotion marker
    auto tmp = std::find(input.begin(), penultimate_item, '='); // Finding promotion marker

    // Dealing with promotion
    if(tmp != penultimate_item)
    {
        tmp++;
        promotion = GetPieceFromChar(*tmp);
        it+=2;
    } else {
        promotion = PieceSet::NONE;
    }

    try {
        piece = PieceSet::PAWN; // default value
        departure_rank = -1;
        departure_file = -1;
        landing_rank = -1;
        landing_file = -1;

        // Getting Landing rank
        landing_rank = *it - '1';
        it++;

        // Gettings Landing file
        landing_file = *it - 'a';

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
            departure_rank = *it - '0';
            it++;
            departure_file = *it - 'a';
            it++;
            break;
        case 2:
            // [Piece][departure file] OR [Piece][Departure rank]. --- [Departure file][Departure rank] is impossible: two pawns cannot attack the same square from the same file.
            if(*it >= 'a' && *it <= 'z') // It's a file
            {
                departure_file = *it - 'a';
            } else {
                departure_rank = *it - '0';
            }
            it++;
            break;
        case 1:
            // [Piece] OR [departure file] OR [departure rank]
            if(*it >= 'A' && *it <= 'Z') // It's a piece
            {
                break;
            }
            if(*it >= 'a' && *it <= 'z') // It's a file
            {
                departure_file = *it - 'a';
            } else { // It's a rank
                departure_rank = *it - '0';
            }


            
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
        return false;
    }
}



Move Interface::ParseAndValidateMove(const std::string & input)
{


    PieceSet piece, promotion;
    int departure_rank, departure_file , landing_rank, landing_file;

    ParseMove(piece, promotion, departure_rank, departure_file, landing_rank, landing_file, input);
    // TODO: validate move
    
    
    return {-1,-1,-1,-1};
}

}
