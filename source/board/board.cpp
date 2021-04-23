#include "../defines.h"
#include "board.h"
#include "../knight/knight.h"
#include "../king/king.h"
#include "../rook/rook.h"
#include "../bishop/bishop.h"
#include "../queen/queen.h"
#include "../pawn/pawn.h"
#include <iostream>
#include <exception>
#include <memory>
#include <sstream>

namespace ConsoleChess {


Board::Board()
{
    for(int i=0; i<NumberOfSquares; i++)
    {
        mSquares[i] = nullptr;
    }
}

std::tuple<PieceSet, Colour> Board::GetPieceFromFEN(char c)
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
 * FEN constructor. Initializes the board according to Forsyth–Edwards Notation
 */
Board::Board(const std::string & rFen)
{
    for(int i=0; i<NumberOfSquares; i++)
    {
        mSquares[i] = nullptr;
    }
    
    // Reading position block
    unsigned int file = 0;
    unsigned int rank = 7;
    for(const char& c: rFen)
    {
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
                std::stringstream ss;
                ss << "Unexpected character when reading FEN : " << c << "\n";
                throw std::runtime_error(ss.str());
            }

            this->CreatePieceInLocation(piece_type, rank, file, col);
            file++;
        }
    }

    // TODO: Read the rest of the blocks

}

Board::Board(const Board & rRHS)
{
    for(int i=0; i<NumberOfSquares; i++)
    {
        if(rRHS.mSquares[i])
        {
            mSquares[i] = std::unique_ptr<Piece>(rRHS.mSquares[i]->Clone(this));
        }
        else
        {
            mSquares[i] = nullptr;
        }
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
    case PieceSet::BISHOP:
        square = std::unique_ptr<Piece>(new Bishop(rank, file, this, colour));
        break;
    case PieceSet::QUEEN:
        square = std::unique_ptr<Piece>(new Queen(rank, file, this, colour));
        break;
    case PieceSet::PAWN:
        square = std::unique_ptr<Piece>(new Pawn(rank, file, this, colour));
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

std::string Board::GetSquareName(int rank, int file)
{
    std::string s;
    
    if(rank <0 || rank>=Board::NumberOfRanks)
    {
        s.push_back('?');
    } else {
        s.push_back('a' + file);
    }

    if(file <0 || file>=Board::NumberOfFiles)
    {
        s.push_back('?');
    } else {
        s.push_back('1' + rank);
    }

    return s;
}

void Board::SetUpInitialPieces()
{
    // Rooks
    CreatePieceInLocation(PieceSet::ROOK, 0, 0, Colour::WHITE);
    CreatePieceInLocation(PieceSet::ROOK, 0, 7, Colour::WHITE);
    CreatePieceInLocation(PieceSet::ROOK, 7, 0, Colour::BLACK);
    CreatePieceInLocation(PieceSet::ROOK, 7, 7, Colour::BLACK);

    // Knights
    CreatePieceInLocation(PieceSet::KNIGHT, 0, 1, Colour::WHITE);
    CreatePieceInLocation(PieceSet::KNIGHT, 0, 6, Colour::WHITE);
    CreatePieceInLocation(PieceSet::KNIGHT, 7, 1, Colour::BLACK);
    CreatePieceInLocation(PieceSet::KNIGHT, 7, 6, Colour::BLACK);

    // Bishops
    CreatePieceInLocation(PieceSet::BISHOP, 0, 2, Colour::WHITE);
    CreatePieceInLocation(PieceSet::BISHOP, 0, 5, Colour::WHITE);
    CreatePieceInLocation(PieceSet::BISHOP, 7, 2, Colour::BLACK);
    CreatePieceInLocation(PieceSet::BISHOP, 7, 5, Colour::BLACK);

    // Queens
    CreatePieceInLocation(PieceSet::QUEEN, 0, 3, Colour::WHITE);
    CreatePieceInLocation(PieceSet::QUEEN, 7, 3, Colour::BLACK);

    // Kings
    CreatePieceInLocation(PieceSet::KING, 0, 4, Colour::WHITE);
    CreatePieceInLocation(PieceSet::KING, 7, 4, Colour::BLACK);

    // Pawns
    for(unsigned int i=0; i<Board::NumberOfFiles; i++)
    {
        CreatePieceInLocation(PieceSet::PAWN, 1, i, Colour::WHITE);
        CreatePieceInLocation(PieceSet::PAWN, 6, i, Colour::BLACK);
    }
}

std::string Board::Display() const
{
    std::stringstream ss;
    ss<<"+---+---+---+---+---+---+---+---+\n";
    for(int r=this->NumberOfRanks-1; r>=0; r--)
    {
        ss << "|";
        for(int f=0; f < this->NumberOfFiles; f++)
        {
            const Piece * piece = this->pGetSquareContent(r,f);
            if(piece)
            {
                ss << ' ' << piece->GetPieceCharacter() << ' ';
            } else
            {
                ss <<"   ";
            }

            ss <<"|";
        }
        ss<<"\n+---+---+---+---+---+---+---+---+\n";
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    os << b.Display();
    return os;
}

}
