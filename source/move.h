#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <ostream>
#include "defines.h"

namespace ConsoleChess {

/**
 * @brief Class Move
 * Contains information to make a move.
 * Indicates if the departure file and or rank are unknown (useful to parse algebraic notation that only indicates destination).
 * 
 * It's a wrapper around a uint16_t+uint8_t, so it's very lightweight. It may seem needlessly convoluted but this'll
 * allow it to be used in chess engines (which are notoriously memory-hungry).
 */
class Move
{
    uint16_t mData16 = 0;
    uint8_t  mData8 = 0;


    /*

    *** mData16 ***

    000 000 000 000 00 00
    |   |   |   |   |  |
    |   |   |   |   |  Known DR, DF
    |   |   |   |   Castling
    |   |   |   Landing file
    |   |   Landing rank
    |   Departure file
    Departure rank

    
    *** mData8 ***

    0000 0 000
    |    | |
    |    | Promotion*
    |    En passant target
    Unused

    >Promotion:
        0xx None
        100 Queen
        101 Rook
        110 Bishop
        111 Knight

    */

    static constexpr uint16_t DepRank_mask     = 0b1110000000000000;
    static constexpr uint16_t DepFile_mask     = 0b0001110000000000;
    static constexpr uint16_t LanRank_mask     = 0b0000001110000000;
    static constexpr uint16_t LanFile_mask     = 0b0000000001110000;
    static constexpr uint16_t ShortCastle_mask = 0b0000000000001000;
    static constexpr uint16_t LongCastle_mask  = 0b0000000000000100;
    static constexpr uint16_t KnownDR_mask     = 0b0000000000000010;
    static constexpr uint16_t KnownDF_mask     = 0b0000000000000001;
    static constexpr uint16_t ThreeDigit_mask  = 0b0000000000000111;

    static constexpr uint8_t Promotion_mask   =         0b00000111;
    static constexpr uint8_t EnPassant_mask   =         0b00001000;

    friend bool operator==(const Move & rLHS, const Move & rRHS);

    static Move MoveFromBits(uint16_t data16, uint8_t data8);

public:
    Move(const int & departure_rank,
         const int & departure_file,
         const int & landing_rank,
         const int & landing_file,
         const PieceSet promotion = PieceSet::NONE);

    Move(const int & landing_rank,
         const int & landing_file,
         const PieceSet promotion = PieceSet::NONE);

    Move();

    static Move ShortCastle();
    static Move LongCastle();
    static Move PawnDoublePush(const int & landing_rank, const int & landing_file, const Colour colour);

    void SetDepartureRank(unsigned int rank);
    void SetDepartureFile(unsigned int file);
    void SetLandingRank(unsigned int rank);
    void SetLandingFile(unsigned int file);
    void UnsetDepartureRank();
    void UnsetDepartureFile();
    void SetShortCastle(bool set=true);
    void SetLongCastle(bool set=true);
    void SetPromotion(PieceSet piece);
    void SetPawnDoublePush(bool set=true);

    int GetDepartureRank() const;
    int GetDepartureFile() const;
    int GetLandingRank() const;
    int GetLandingFile() const;
    bool IsDepartureRankKnown() const;
    bool IsDepartureFileKnown() const;
    bool GetShortCastle() const;
    bool GetLongCastle() const;
    PieceSet GetPromotion() const;
    bool GetPawnDoublePush() const;
};

std::ostream& operator<<(std::ostream& os, const Move& m);

bool operator==(const Move &, const Move &);

}

#endif // CHESS_MOVE_H
