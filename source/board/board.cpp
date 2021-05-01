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

unsigned int Board::CoordsToIndex(const unsigned int rank, const unsigned int file)
{
    CheckBoundsDebug(rank, file);
    return rank * NumberOfFiles + file;
}


Board::Board()
{
    for(unsigned int r=0; r<NumberOfRanks; r++)
    {
        for(unsigned int f=0; f<NumberOfFiles; f++)
        {
            mSquares[CoordsToIndex(r,f)].SetLocation(r, f, this);
        }
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
Board::Board(const std::string & rFen) : Board()
{    
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
        mSquares[i].CloneContent(rRHS.mSquares[i]);
    }
}

Square & Board::GetSquare(const int & rank, const int & file)
{
    return mSquares[CoordsToIndex(rank, file)];
}

const Square & Board::GetSquare(const int & rank, const int & file) const
{
    return mSquares[CoordsToIndex(rank, file)];
}

Piece * Board::pGetSquareContent(const int & rank, const int & file)
{
    return mSquares[CoordsToIndex(rank, file)].pGetContent();
}

Piece * Board::pGetSquareContent(const int & square)
{
    return mSquares[square].pGetContent();
}

const Piece * Board::pGetSquareContent(const int & square) const
{
    return mSquares[square].pGetContent();
}

const Piece * Board::pGetSquareContent(const int & rank, const int & file) const
{
    return mSquares[CoordsToIndex(rank, file)].pGetContent();
}

bool Board::SquareIsEmpty(const int & rank, const int & file)
{
    return mSquares[CoordsToIndex(rank, file)].IsEmpty();
}

Piece * Board::CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour)
{
    Square & square = mSquares[CoordsToIndex(rank, file)];

    square.Reset();

    switch (piece_type) {
    case PieceSet::NONE:
        break;
    case PieceSet::KNIGHT:
        square.NewPiece<Knight>(rank, file, this, colour);
        break;
    case PieceSet::KING:
        square.NewPiece<King>(rank, file, this, colour);
        kings.push_back(square.pGetContent());
        break;
    case PieceSet::ROOK:
        square.NewPiece<Rook>(rank, file, this, colour);
        break;
    case PieceSet::BISHOP:
        square.NewPiece<Bishop>(rank, file, this, colour);
        break;
    case PieceSet::QUEEN:
        square.NewPiece<Queen>(rank, file, this, colour);
        break;
    case PieceSet::PAWN:
        square.NewPiece<Pawn>(rank, file, this, colour);
        break;
    default:
        throw std::invalid_argument("Unknown piece type.");
    }

    return square.pGetContent();
}

Colour Board::GetColourOccupied(const int & rank, const int & file) const
{
    const Square & square = mSquares[CoordsToIndex(rank, file)];
    
    if(square.IsEmpty()) return Colour::UNDEFINED;

    return square.pGetContent()->GetColour();
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

/**
 * @brief Evaulates the board to see if either player is in check
 * @return Colour of the player in check
 */
Colour Board::IsInCheck() const
{
    return Colour::UNDEFINED;
}


std::ostream& operator<<(std::ostream& os, const Board& b)
{
    os << b.Display();
    return os;
}


bool Board::IsAttackedBy(const unsigned int rank, const unsigned int file, const Colour attacker)
{
    mSquares[CoordsToIndex(rank, file)].IsAttackedBy(attacker);
}


void Board::SetAttack(const unsigned int rank, const unsigned int file, const Colour attacker)
{
    mSquares[CoordsToIndex(rank, file)].SetAttack(attacker);
}


void Board::UnSetAttack(const unsigned int rank, const unsigned int file, const Colour attacker)
{
    mSquares[CoordsToIndex(rank, file)].UnsetAttack(attacker);
}


void Board::ResetAttack(const unsigned int rank, const unsigned int file)
{
    mSquares[CoordsToIndex(rank, file)].ResetAttack();
}

bool Board::ValidateAndCompleteMove(Move & rMove, const PieceSet piece_type, const PieceSet promotion) const
{
    if(piece_type != PieceSet::PAWN && promotion != PieceSet::NONE) return false; // Only pawns can promote

    if(piece_type == PieceSet::PAWN && promotion == PieceSet::NONE) return false; // Pawns have to promote to something
    if(promotion == PieceSet::PAWN) return false;                                 // Pawns cannot promote to pawns

    if(rMove.departure_file < 0 || rMove.departure_rank < 0) // Departure quare is not specified
    {
        for(const auto & square : mSquares)
        {
            if(square.ValidateMove(piece_type, rMove.landing_file, rMove.landing_rank))
            {
                rMove.departure_rank = square.GetRank();
                rMove.departure_file = square.GetFile();
                return true;
            }
        }

        return false;
    }
    else // Departure square is specified
    {
        const Square & square = mSquares[CoordsToIndex(rMove.departure_file, rMove.departure_rank)];
        
        return square.ValidateMove(piece_type, rMove.landing_file, rMove.landing_rank);
        
    }
}

/**
 * @brief Checks if the rank and file are valid, but only when debug mode is enabled.
 */
#ifndef NDEBUG
void Board::CheckBoundsDebug(const int rank, const int file)
{
    if(rank >= 8 || rank < 0 || file < 0 || file >= 8)
    {
        throw std::logic_error("Index out of bounds");
    }
}
#else
void Board::CheckBoundsDebug(const int, const int) {}
#endif

}
