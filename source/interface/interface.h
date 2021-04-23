#ifndef CHESS_INTERFACE_H
#define CHESS_INTERFACE_H

#include <iostream>
#include <vector>
#include <tuple>

#include "../defines.h"
#include "../board/board.h"

namespace ConsoleChess {

class Interface
{
public:
    Interface() {}

    static int Intro();

    static void DisplayBoard(const Board & rBoard);
    static Move AskMove(const Board & rBoard);

    static bool ParseMove(PieceSet & piece, PieceSet & promotion, int& departure_rank, int& departure_file, int& landing_rank, int& landing_file, std::string input);
    static Move ParseAndValidateMove(const std::string & input);
protected:

    static int Question(char const* querry, char const* options);
    static std::string BuildQuestion(char const* querry, char const* options);
    static int ChooseRandomColour();

    static PieceSet GetPieceFromChar(const char c);


};

}

#endif // CHESS_INTERFACE_H
