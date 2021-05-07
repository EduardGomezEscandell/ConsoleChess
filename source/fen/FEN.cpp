#include "FEN.h"

namespace ConsoleChess
{
namespace FEN
{

std::tuple<PieceSet, Colour> GetPieceFromFEN(char c)
{
    Colour col = Colour::UNDEFINED;
    if(c >= 'a' && c <= 'z')
    {
        col = Colour::BLACK;
        c += 'A' - 'a'; // Capitalizing
    } 
    else if(c >= 'A' && c <= 'Z')
    {
        col = Colour::WHITE;
    }

    PieceSet piece;
    switch (c)
    {
        case 'P':   piece = PieceSet::PAWN;     break;
        case 'R':   piece = PieceSet::ROOK;     break;
        case 'B':   piece = PieceSet::BISHOP;   break;
        case 'Q':   piece = PieceSet::QUEEN;    break;
        case 'K':   piece = PieceSet::KING;     break;
        case 'N':   piece = PieceSet::KNIGHT;   break;
        default:    piece = PieceSet::NONE;
    }

    return std::tie(piece, col);
}

/**
 * @brief Returns a board from a string containing Forsyth–Edwards Notation (FEN)
 * 
 * @param str: The FEN string
 * @returns The board generated
 */
Board Reader(const char * str)
{
    Board board;

    // Reading position block
    unsigned int file = 0;
    unsigned int rank = 7;
    for(const char * ptr = str; *ptr != '\0'; ptr++)
    {
        const char c = *ptr;
        if(c==' ') break; // End of block

        if(c=='/') // End of rank
        {
            file = 0;
            rank--;
        }
        else if(c >= '0' && c <= '9') // Empty squares
        {
            file += (c - '0');
        }
        else
        {
            Colour col;
            PieceSet piece_type;
            std::tie(piece_type, col) = GetPieceFromFEN(c);

            if(piece_type == PieceSet::NONE)
            {
                CHESS_THROW << "Unexpected character when reading FEN : " << c;
            }

            board.CreatePieceInLocation(piece_type, rank, file, col);
            file++;
        }
    }

    return board;
}

std::string Writer(const Board & rBoard)
{
    return "";
}

}
}