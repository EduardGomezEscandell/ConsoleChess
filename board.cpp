#include "board.h"
#include <iostream>

namespace ConsoleChess {


Board::Board()
{
    for(int i=0; i<NumberOfCells; i++)
    {
        squares[i] = nullptr;
    }
}

Piece * Board::GetCellContent(const int & rank, const int & file)
{
    if(rank > NumberOfRanks || file > NumberOfFiles)
    {
        std::cerr << "Attempted to access square outside of the board" << std::endl;
        throw;
    }

    return squares[rank * NumberOfFiles + file];
}

}
