#include "defines.h"

namespace ConsoleChess {

Colour OppositeColour(const Colour c)
{
    return static_cast<Colour>(- static_cast<int>(c)); // Exploiting the fact that WHITE == - BLACK
}


std::ostream& operator<<(std::ostream& os, const PieceSet& p)
{
    switch(p)
    {
    case PieceSet::NONE:
        os<< "PieceSet::NONE";
        break;
    case PieceSet::PAWN:
        os<< "PieceSet::PAWN";
        break;
    case PieceSet::KNIGHT:
        os<< "PieceSet::KNIGHT";
        break;
    case PieceSet::BISHOP:
        os<< "PieceSet::BISHOP";
        break;
    case PieceSet::ROOK:
        os<< "PieceSet::ROOK";
        break;
    case PieceSet::QUEEN:
        os<< "PieceSet::QUEEN";
        break;
    case PieceSet::KING:
        os<< "PieceSet::KING";
        break;
    }
    return os;
}



}
