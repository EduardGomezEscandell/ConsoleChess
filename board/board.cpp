#include "../defines.h"
#include "board.h"
#include "../knight/knight.h"
#include "../king/king.h"
#include "../rook/rook.h"
#include <iostream>
#include <exception>
#include <memory>

namespace ConsoleChess {


Board::Board()
{
    for(int i=0; i<NumberOfSquares; i++)
    {
        mSquares[i] = nullptr;
    }
}

Piece * Board::pGetSquareContent(const int & rank, const int & file)
{
    return mSquares[rank * NumberOfFiles + file].get();
}

const Piece * Board::pGetSquareContent(const int & rank, const int & file) const
{
    return mSquares[rank * NumberOfFiles + file].get();
}

bool Board::SquareIsEmpty(const int & rank, const int & file)
{
    return (mSquares[rank * NumberOfFiles + file] == nullptr);
}

Piece * Board::CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour)
{
    std::unique_ptr<Piece> & square = mSquares[rank * NumberOfFiles + file];
    square.reset();

    switch (piece_type) {
    case PieceSet::NONE:
        break;
    case PieceSet::KNIGHT:
        square = std::unique_ptr<Piece>(new Knight(rank, file, this, colour));
        break;
    case PieceSet::KING:
        square = std::unique_ptr<Piece>(new King(rank, file, this, colour));
        break;
    case PieceSet::ROOK:
        square = std::unique_ptr<Piece>(new Rook(rank, file, this, colour));
        break;
    default:
        throw std::invalid_argument("Unknown piece type.");
    }

    return square.get();
}

Colour Board::GetColourOccupied(const int & rank, const int & file) const
{
    const Piece * p_square = pGetSquareContent(rank, file);

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
