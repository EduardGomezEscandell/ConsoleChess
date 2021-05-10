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

/**
 * @brief Board copy constructor. Square and pieces are copied as well.
 * @param rRHS: The board to copy
 */
Board::Board(const Board & rRHS)
{
    for(unsigned int i=0; i<Board::NumberOfSquares; i++)
    {
        mSquares[i] = rRHS.mSquares[i];
        mSquares[i].mContent = nullptr; // Cannot use Square::Vacate since that changes the state of the piece
        mSquares[i].mpOwner = this;
    }

    for(const auto & piece : rRHS.mPieces)
    {
        mPieces.emplace_back(piece->Clone(this));
        const unsigned int mRank = piece->mLocation[0];
        const unsigned int mFile = piece->mLocation[1];
        GetSquare(mRank, mFile).OverwriteContent(mPieces.back().get());
    }


    mMoveCount = rRHS.mMoveCount;
    
    if(rRHS.mEnPassantSquare)
    {
        mEnPassantSquare = &GetSquare(rRHS.mEnPassantSquare->GetRank(), rRHS.mEnPassantSquare->GetFile());
    }
    
    if(rRHS.mWhiteKing)
    {
        mWhiteKing = pGetSquareContent(rRHS.mWhiteKing->mLocation[0], rRHS.mWhiteKing->mLocation[1]);
    }
    if(rRHS.mBlackKing)
    {
        mBlackKing = pGetSquareContent(rRHS.mBlackKing->mLocation[0], rRHS.mBlackKing->mLocation[1]);
    }
    
    mColourToMove = rRHS.mColourToMove;
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
        return nullptr;
    case PieceSet::KNIGHT:
        mPieces.emplace_back(std::make_unique<Knight>(rank, file, this, colour));
        break;
    case PieceSet::ROOK:
        mPieces.emplace_back(std::make_unique<Rook>(rank, file, this, colour));
        break;
    case PieceSet::BISHOP:
        mPieces.emplace_back(std::make_unique<Bishop>(rank, file, this, colour));
        break;
    case PieceSet::QUEEN:
        mPieces.emplace_back(std::make_unique<Queen>(rank, file, this, colour));
        break;
    case PieceSet::PAWN:
        mPieces.emplace_back(std::make_unique<Pawn>(rank, file, this, colour));
        break;
    case PieceSet::KING:
        mPieces.emplace_back(std::make_unique<King>(rank, file, this, colour));
        
        if(colour==Colour::WHITE)
        {
            if(mWhiteKing) CHESS_THROW << "Attempted to put two white kings on the board";
            mWhiteKing = mPieces.back().get();
        } 
        else if(colour==Colour::BLACK)
        {
            if(mBlackKing) CHESS_THROW << "Attempted to put two black kings on the board";
            mBlackKing = mPieces.back().get();
        }
        break;
    default:
        CHESS_THROW << "Unknown piece type";
    }

    square.OverwriteContent(mPieces.back().get());

    return square.pGetContent();
}

Piece * Board::GetKing(Colour colour)
{
    Piece * king;
    switch(colour)
    {
        case Colour::WHITE:     king = mWhiteKing;  break;
        case Colour::BLACK:     king = mBlackKing;  break;
        default: CHESS_THROW << "Attempted to fetch undetermined-coloured king";
    }

    return king;
}

const Piece * Board::GetKing(Colour colour) const
{
    Piece * king;
    switch(colour)
    {
        case Colour::WHITE:     king = mWhiteKing;  break;
        case Colour::BLACK:     king = mBlackKing;  break;
        default: CHESS_THROW << "Attempted to fetch undetermined-coloured king";
    }

    return king;
}


unsigned int Board::GetMoveCount() const
{
    return mMoveCount;
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
bool Board::IsInCheck(Colour colour) const
{
    for(const Square & square : mSquares)
    {
        if(square.IsEmpty())         continue;
        
        const Piece * p = square.pGetContent();
        
        if(p->GetColour() != colour) continue;
        if(p->IsInCheck())           return true;
    }

    return false;
}


std::ostream& operator<<(std::ostream& os, const Board& b)
{
    os << b.Display();
    return os;
}


bool Board::IsAttackedBy(const unsigned int rank, const unsigned int file, const Colour attacker)
{
    return mSquares[CoordsToIndex(rank, file)].IsAttackedBy(attacker);
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

void Board::UpdateLegalMoves()
{
    for(auto it = mPieces.begin(); it != mPieces.end(); it++)
    {
        Piece * piece = it->get();

        if(piece->IsAlive())
        {
            piece->UpdateLegalMoves();
        }
        else // Removing piece
        {
            auto tmp = it;
            it--;
            mPieces.erase(tmp);
        }
    }

    // Updating kings
    if(mBlackKing) mBlackKing->UpdateLegalMoves();
    if(mWhiteKing) mWhiteKing->UpdateLegalMoves();
}

void Board::ResetAttacks()
{
    for(auto & square : mSquares)
    {
        square.ResetAttack();
    }
}

bool Board::ValidateAndCompleteMove(Move & rMove, const PieceSet piece_type) const
{
    const bool departure_rank_known = rMove.IsDepartureRankKnown();
    const bool departure_file_known = rMove.IsDepartureFileKnown();
    const unsigned int departure_rank = rMove.GetDepartureRank();
    const unsigned int departure_file = rMove.GetDepartureFile();

    if(rMove.GetShortCastle() || rMove.GetLongCastle())
    {
        const Piece * king = GetKing(mColourToMove);
        
        if(!king) return false;
        
        for(auto & king_move : king->GetMoves())
        {
            if(king_move == rMove) return true;
        }
        return false;
    }


    if(departure_rank_known && departure_file_known) // Departure square is specified
    {
        const Square & square = mSquares[CoordsToIndex(departure_rank, departure_file)];
        return square.ValidateMove(piece_type, rMove.GetLandingRank(), rMove.GetLandingFile(), mColourToMove);
    }
    else // Departure square is not fully specified
    {
        unsigned int valid_move_count = 0;

        for(const auto & square : mSquares)
        {
            if(departure_rank_known && departure_rank != square.GetRank()) continue;
            if(departure_file_known && departure_file != square.GetFile()) continue;

            if(square.ValidateMove(piece_type, rMove.GetLandingRank(), rMove.GetLandingFile(), mColourToMove))
            {
                rMove.SetDepartureRank(square.GetRank());
                rMove.SetDepartureFile(square.GetFile());

                if(square.pGetContent()->GetPieceType() == PieceSet::PAWN)
                {
                    if(abs(square.GetRank() - rMove.GetLandingRank()) == 2)
                    {
                        rMove.SetEnPassant();
                    }
                }
                valid_move_count++;
            }
        }

        return valid_move_count==1; // If >1, then the move is underdefined (for example two rooks may be able move to the same square)
    }
}

/**
 * @brief DoMove performs the move indicated in Move.
 * This move will not be validated, so run it through ValidateAndCompleteMove before attempting to perform it, else the behaviour is undefined.
 * En passant square is updated. Colour to move is updated. Move count is increassed.
 * @param Move: The move to perform
 */
void Board::DoMove(const Move & rMove)
{
    if(rMove.GetShortCastle()==true)
    {
        const unsigned int backrank = mColourToMove == Colour::WHITE ? 0 : 7;

        // Moving king
        Square * departure = &mSquares[CoordsToIndex(backrank,4)];
        Square * landing = &mSquares[CoordsToIndex(backrank,6)];
        MovePiece(*departure, *landing);

        // Moving rook
        departure = &mSquares[CoordsToIndex(backrank,7)];
        landing = &mSquares[CoordsToIndex(backrank,5)];
        MovePiece(*departure, *landing);

    }
    else if(rMove.GetLongCastle()==true)
    {
        const unsigned int backrank = mColourToMove == Colour::WHITE ? 0 : 7;

        // Moving king
        Square * departure = &mSquares[CoordsToIndex(backrank,4)];
        Square * landing = &mSquares[CoordsToIndex(backrank,2)];
        MovePiece(*departure, *landing);

        // Moving rook
        departure = &mSquares[CoordsToIndex(backrank,0)];
        landing = &mSquares[CoordsToIndex(backrank,3)];
        MovePiece(*departure, *landing);
    }
    else if(rMove.GetPromotion() != PieceSet::NONE)
    {
        // Promoting pawn
        Square & departure = mSquares[CoordsToIndex(rMove.GetDepartureRank(), rMove.GetDepartureFile())];
        departure.Vacate();

        Piece * newpiece = CreatePieceInLocation(rMove.GetPromotion(), rMove.GetLandingRank(), rMove.GetLandingFile(), mColourToMove);
        newpiece->RemoveCastlingRights();        
    }
    else
    {
        // Moving piece
        Square & departure = mSquares[CoordsToIndex(rMove.GetDepartureRank(), rMove.GetDepartureFile())];
        Square & landing = mSquares[CoordsToIndex(rMove.GetLandingRank(), rMove.GetLandingFile())];
        MovePiece(departure, landing);
    }

    if(rMove.GetEnPassant()==true)
    {
        const unsigned int file = rMove.GetLandingFile();
        const unsigned int landing_rank = rMove.GetLandingRank();
        const unsigned int en_passant_rank = (landing_rank + rMove.GetDepartureRank())/2;
        SetEnPassantTarget(en_passant_rank, file);
    }
    else
    {
        mEnPassantSquare = nullptr;
    }

    mColourToMove = OppositeColour(mColourToMove);
    mMoveCount++;
}

void Board::SetMoveCounter(const unsigned int count)
{
    mMoveCount = count;
}

Colour Board::WhoMoves() const
{
    return mColourToMove;
}


void Board::MovePiece(Square & rDeparture, Square & rLanding)
{
#ifndef NDEBUG
    // Avoiding SEGFAULT in debug mode
    if(rDeparture.IsEmpty()) CHESS_THROW << "Attempted to move from an empty square";
#endif

    rDeparture.pGetContent()->RemoveCastlingRights();
    rDeparture.pGetContent()->SetLocation(rLanding.GetRank(), rLanding.GetFile());

    rLanding.Vacate();
    rLanding.SwapContent(rDeparture);

}

Square * Board::GetEnPassantSquare()
{
    return mEnPassantSquare;
}

const Square * Board::GetEnPassantSquare() const
{
    return mEnPassantSquare;
}

void Board::SetColourToMove(const Colour c)
{
    if(c != Colour::WHITE && c!=Colour::BLACK)
    {
        CHESS_THROW << "Cannot set board colour to move to " << c <<".";
    }
    mColourToMove = c;
}

void Board::SetEnPassantTarget(const int Rank, const int File)
{
    mEnPassantSquare = &GetSquare(Rank, File);
}

/**
 * @brief Checks if the rank and file are valid, but only when debug mode is enabled.
 */
#ifndef NDEBUG
void Board::CheckBoundsDebug(const int rank, const int file)
{
    if(rank >= 8 || rank < 0 || file < 0 || file >= 8)
    {
        CHESS_THROW << "Index out of bounds (" << rank <<", " << file << ")";
    }
}
#else
void Board::CheckBoundsDebug(const int, const int) {}
#endif

}
