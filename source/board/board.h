#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../piece.h"
#include "../defines.h"
#include "../square.h"

#include <list>
#include <memory>
#include <string>
#include <optional>

namespace ConsoleChess {

class Board
{
public:
    // Constructors
    Board();
    Board(const Board & rRHS);

    // Access
    Square & GetSquare(const int & rank, const int & file);
    const Square & GetSquare(const int & rank, const int & file) const;

    Piece * pGetSquareContent(const int & square);
    const Piece * pGetSquareContent(const int & square) const;
    Piece * pGetSquareContent(const int & rank, const int & file);
    const Piece * pGetSquareContent(const int & rank, const int & file) const;

    Piece * GetKing(Colour colour);
    const Piece * GetKing(Colour colour) const;

    unsigned int GetMoveCount() const;
    Square * GetEnPassantSquare();
    const Square * GetEnPassantSquare() const;

    // Editors
    void DoMove(const Move & Move);

    Piece * CreatePieceInLocation(PieceSet piece_type, const int & rank, const int & file, const Colour & colour);
    void SetUpInitialPieces();

    void SetAttack(const unsigned int rank, const unsigned int file, const Colour attacker);
    void UnSetAttack(const unsigned int rank, const unsigned int file, const Colour attacker);
    void ResetAttack(const unsigned int rank, const unsigned int file);

    void ResetAttacks();
    void UpdateLegalMoves();

    // Queries
    Colour WhoMoves() const;
    bool SquareIsEmpty(const int & rank, const int & file);
    Colour GetColourOccupied(const int & rank, const int & file) const;
    bool IsInCheck(Colour colour) const;

    bool IsAttackedBy(const unsigned int rank, const unsigned int file, const Colour attacker);

    static void CheckBoundsDebug(const int rank, const int file);

    // Output
    std::string Display() const;

    // Others
    bool ValidateAndCompleteMove(Move & rMove, const PieceSet piece) const;

    static constexpr int NumberOfFiles = 8;
    static constexpr int NumberOfRanks = 8;
    static constexpr int NumberOfSquares = NumberOfRanks * NumberOfFiles;

protected:
    unsigned int mMoveCount = 1;
    Square * mEnPassantSquare = nullptr;
    Square mSquares[NumberOfSquares];
    std::list<std::unique_ptr<Piece>> mPieces;
    Piece * mWhiteKing = nullptr;
    Piece * mBlackKing = nullptr;
    static std::tuple<PieceSet, Colour> GetPieceFromFEN(char c);
    Colour mColourToMove = Colour::WHITE;

    static unsigned int CoordsToIndex(const unsigned int rank, const unsigned int file);
    static void MovePiece(Square & rDeparture, Square & rLanding);
};

std::ostream& operator<<(std::ostream& os, const Board& b);

}

#endif // CHESS_BOARD_H
