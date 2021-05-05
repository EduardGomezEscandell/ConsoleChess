#ifndef CHESS_INTERFACE_H
#define CHESS_INTERFACE_H

#include <iostream>
#include <tuple>
#include <map>
#include <sstream>
#include <string>

#include "../defines.h"
#include "../board/board.h"

namespace ConsoleChess {

class Interface
{
public:
    Interface() {}

    static Colour Intro();

    static void DisplayBoard(const Board & rBoard);
    static Move AskMove(const Board & rBoard);

    static std::tuple<Move, bool> ParseAndValidateMove(const std::string & input, const Board & rBoard);
protected:

    static int ChooseRandomColour();
    static PieceSet GetPieceFromChar(const char c);

    /**
     * @brief Template to ask a question with a limited set of answers. This method creates the question to be printed to screen.
     * @param querry:  The question
     * @param options:  A std::map with the valid answers as a keys
     * @return std::string 
     */
    template<typename T>
    static std::string BuildQuestion(const std::string & querry, const std::map<std::string, T> & options)
    {
        std::stringstream ss;
        ss << querry << " (";

        bool first = true;
        for(const auto & key_value_pair : options)
        {
            if(!first)
            {
                ss << "|";
            }
            ss << key_value_pair.first;
            first = false;
        }
        ss << "): ";
        return ss.str();
    }
    
    /**
     * @brief Template to ask a question with a limited set of answers. This method prints the question and parses the answer.
     * 
     * @tparam T: The type of returned value.
     * @param querry:  The question
     * @param options:  A std::map with the valid answers as a keys and the return values as values
     * @return T: The returned value
     */
    template<typename T>
    static T Question(const std::string & querry, const std::map<std::string, T> & options)
    {
        std::string question = BuildQuestion<T>(querry, options);

        bool valid_answer = false;
        while(!valid_answer)
        {
            std::cout << question;

            std::string answer;
            std::cin >> answer;

            const auto result = options.find(answer);

            if(result != options.end())
            {
                return result->second;
            }
            else
            {
                std::cout << "Unrecognized input.\n";
            }
        }

        CHESS_THROW << "Unreachable code reached.";
    }

};

}

#endif // CHESS_INTERFACE_H
