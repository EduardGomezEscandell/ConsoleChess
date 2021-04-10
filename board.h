#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

namespace ConsoleChess {

class Board
{
public:
    Board();

    Piece * GetCellContent(const int & rank, const int & file);

    Piece * operator()(const int & rank, const int & file) {return GetCellContent(rank, file);};

    const static int NumberOfFiles = 8;
    const static int NumberOfRanks = 8;
    const static int NumberOfCells = NumberOfRanks * NumberOfFiles;

protected:
    Piece * squares[NumberOfCells];
};

}
#endif // BOARD_H
