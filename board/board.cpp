#include "board.h"
#include "../knight/knight.h"
#include "../king/king.h"
#include "../rook/rook.h"
#include <iostream>
#include <exception>

namespace ConsoleChess {


Board::Board()
{
    for(int i=0; i<NumberOfSquares; i++)
    {
        mSquares[i] = nullptr;
    }
}

Piece::Pointer & Board::pGetSquareContent(const int & rank, const int & file)
{
    return mSquares[rank * NumberOfFiles + file];
}

const Piece::Pointer & Board::pGetSquareContent(const int & rank, const int & file) const
{
    return mSquares[rank * NumberOfFiles + file];
}

bool Board::SquareIsEmpty(const int & rank, const int & file)
{
    return (mSquares[rank * NumberOfFiles + file] == nullptr);
}

Piece::Pointer Board::CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour)
{
    Piece::Pointer & square = pGetSquareContent(rank, file);
    switch (piece_type) {

    case PieceSet::NONE:
        square.reset();
        break;
    case PieceSet::KNIGHT:
        square = std::make_shared<Knight>(rank, file, this, colour);
        break;
    case PieceSet::KING:
        square = std::make_shared<King>(rank, file, this, colour);
        break;
    case PieceSet::ROOK:
        square = std::make_shared<Rook>(rank, file, this, colour);
        break;
    default:
        throw std::invalid_argument("Unknown piece type.");
    }

    return square;
}

Colour Board::GetColourOccupied(const int & rank, const int & file) const
{
    const Piece::Pointer & p_square = pGetSquareContent(rank, file);

    if(p_square == nullptr) return Colour::UNDEFINED;

    return p_square->GetColour();

}

std::string Board::GetSquareName(unsigned int rank, unsigned int file)
{
    std::string s;
    s.push_back('a' + file);
    s.push_back('1' + rank);
    return s;
}

}
