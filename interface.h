#ifndef CHESS_INTERFACE_H
#define CHESS_INTERFACE_H

#include <iostream>
#include <vector>

#include "defines.h"
#include "board/board.h"

namespace ConsoleChess {


class Interface
{
public:
    Interface() {}

    static int Intro();

    void AskMove();
//    void DisplayBoard(const Board & rBoard) const;

protected:

    static int Question(char const* querry, char const* options);
    static std::string BuildQuestion(char const* querry, char const* options);
    static int ChooseRandomColour();



//    template<typename TPiecePointerType>
//    static char PrintPiece(const TPiecePointerType pPiece)
//    {
//        char c = ' ';
//        switch(pPiece->GetPieceType())
//        {
//        case PieceSet::KING:    c = 'K';    break;
//        case PieceSet::KNIGHT:  c = 'N';    break;
//        case PieceSet::ROOK:    c = 'R';    break;
//        case PieceSet::PAWN:    c = 'O';    break;
//        case PieceSet::QUEEN:   c = 'Q';    break;
//        case PieceSet::BISHOP:  c = 'B';    break;
//        default:                c = '?';
//        }

//        if(pPiece->GetColour() == Colour::BLACK) // Making lowercase
//        {
//            c -= ('A' - 'a');
//        }

//        return c;
//    }


};

}

#endif // CHESS_INTERFACE_H
