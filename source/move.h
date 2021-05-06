#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <ostream>

namespace ConsoleChess {


class Move
{
    typedef uint16_t DataType;
    DataType mData = 0;

    /* Data:
    000 000 000 000 00 00
    |   |   |   |   || |
    |   |   |   |   || |
    |   |   |   |   || Known DR, DF
    |   |   |   |   |Long castle
    |   |   |   |   Short castle
    |   |   |   | Landing file
    |   |   Landing rank
    |   Departure file
    Departure rank
    */

    static constexpr DataType DepRank_mask     = 0b1110000000000000;
    static constexpr DataType DepFile_mask     = 0b0001110000000000;
    static constexpr DataType LanRank_mask     = 0b0000001110000000;
    static constexpr DataType LanFile_mask     = 0b0000000001110000;
    static constexpr DataType ShortCastle_mask = 0b0000000000001000;
    static constexpr DataType LongCastle_mask  = 0b0000000000000100;
    static constexpr DataType KnownDR_mask     = 0b0000000000000010;
    static constexpr DataType KnownDF_mask     = 0b0000000000000001;
    static constexpr DataType ThreeDigit_mask  = 0b0000000000000111;

    friend bool operator==(const Move & rLHS, const Move & rRHS);

    Move(DataType data);

public:
    Move(const int & departure_rank,
         const int & departure_file,
         const int & landing_rank,
         const int & landing_file);

    Move(const int & landing_rank,
         const int & landing_file);

    Move();

    static Move ShortCastle();
    static Move LongCastle();

    void SetDepartureRank(unsigned int rank);
    void SetDepartureFile(unsigned int file);
    void SetLandingRank(unsigned int rank);
    void SetLandingFile(unsigned int file);
    void UnsetDepartureRank();
    void UnsetDepartureFile();
    void SetShortCastle(bool set=true);
    void SetLongCastle(bool set=true);

    int GetDepartureRank() const;
    int GetDepartureFile() const;
    int GetLandingRank() const;
    int GetLandingFile() const;
    bool IsDepartureRankKnown() const;
    bool IsDepartureFileKnown() const;
    bool GetShortCastle() const;
    bool GetLongCastle() const;
};

std::ostream& operator<<(std::ostream& os, const Move& m);

bool operator==(const Move &, const Move &);

}

#endif // CHESS_MOVE_H
