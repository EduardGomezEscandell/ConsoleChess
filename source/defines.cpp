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

std::ostream& operator<<(std::ostream& os, const Colour& c)
{
    switch (c)
    {
    case Colour::WHITE:     os << "WHITE";      break;
    case Colour::BLACK:     os << "BLACK";      break;
    case Colour::BOTH:      os << "BOTH";       break;
    case Colour::UNDEFINED: os << "UNDEFINED";  break;
    
    default: CHESS_THROW << "Unreachable code reached";
    }

    return os;
}


}
