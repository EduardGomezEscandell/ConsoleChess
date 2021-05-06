#include "algebraic_notation.h"
#include <regex>

namespace ConsoleChess
{

PieceSet AlgebraicReader::CharToPiece(const char c)
{
    switch (c) {
        case 'R':   return PieceSet::ROOK;
        case 'B':   return PieceSet::BISHOP;
        case 'Q':   return PieceSet::QUEEN;
        case 'K':   return PieceSet::KING;
        case 'N':   return PieceSet::KNIGHT;
    }
    return PieceSet::NONE;
}

/**
 * Parses the move specified as a string and returns the gathered info. Does not validate its legality.
 * @return Whether the move is valid
 */
bool AlgebraicReader::ParseMove(PieceSet & rPiece, Move& rMove, std::string Input)
{
    // Default values
    rPiece = PieceSet::NONE;

    static const std::regex pawn_move(R"(([a-h]x)?[a-h](([1-7])|(8=[QRBN]))[+#=]?)");
    static const std::regex piece_move(R"(([QKRBN][a-h]?[1-8]?x?[a-h][1-8])([=\+#])?)");
    static const std::regex castling(R"((O\-O(\-O)?)([=\+#])?)");
    
    if(std::regex_match(Input, pawn_move))
    {
        rPiece = PieceSet::PAWN;
        ProcessTrailingCharacters(Input);
        ProcessPawnPromotion(rMove, Input);
        ReadDestination(rMove, Input);
        ReadLeadingCharacters(rMove, Input);
        return true;
    }

    if(std::regex_match(Input, piece_move))
    {
        rPiece = CharToPiece(Input[0]);
        ProcessTrailingCharacters(Input);
        ReadDestination(rMove, Input);
        ReadLeadingCharacters(rMove, Input);
        return true;
    }

    if(std::regex_match(Input, castling))
    {
        rPiece = PieceSet::KING;
        ProcessTrailingCharacters(Input);
        if(Input == "O-O")
        {
            rMove.SetShortCastle();
        }
        else
        {
            rMove.SetLongCastle();
        }
        
        return true;
    }
    
    return false;

}

/**
 * @brief Reads the trailing check(+), mate(#) and draw (=) characters and removes them.
 * @param rInput The string containing the move
 */
void AlgebraicReader::ProcessTrailingCharacters(std::string & rInput)
{   
    static const std::regex has_trailing_chars(R"(.*[#\+=])");

    if(std::regex_match(rInput, has_trailing_chars))
    {
        rInput.pop_back();
    }
}

/**
 * @brief Reads the trailing promotion (=[QRBN]) and removes them
 * @param rMove: A reference to the move, to be overwritten
 * @param rInput: The string containing the move
 */
void AlgebraicReader::ProcessPawnPromotion(Move & rMove, std::string & rInput)
{
    std::size_t size = rInput.size();
    if(rInput[size - 2] == '=')
    {
        rMove.SetPromotion(CharToPiece(rInput[size-1]));
        rInput.pop_back();
        rInput.pop_back();
    }   

}

/**
 * @brief Reads the destination square and removes them
 * 
 * @param rMove: A reference to the move, to be overwritten
 * @param rInput: The string containing the move (without trailing characters or promotion)
 */
void AlgebraicReader::ReadDestination(Move & rMove, std::string & rInput)
{
    rMove.SetLandingRank(rInput.back() - '1');
    rInput.pop_back();
    rMove.SetLandingFile(rInput.back() - 'a');
    rInput.pop_back();
}


/**
 * @brief Reads the leading charcaters (possibly departure square and possibly capture indicator)
 * @param rMove: A reference to the move, to be overwritten
 * @param rInput: The string containing the leading characters
 */
void AlgebraicReader::ReadLeadingCharacters(Move & rMove, const std::string & rInput)
{
    if(rInput.empty()) return;
    
    std::string::const_reverse_iterator it = rInput.rbegin();

    if(*it == 'x') // Ignoring capture marker
    {
        if(++it == rInput.rend()) return;
    }
    
    if(*it > '0' && *it <= '8')
    {
        rMove.SetDepartureRank(*it - '1');
        if(++it == rInput.rend()) return;
    }

    if(*it >= 'a' && *it <= 'h')
    {
        rMove.SetDepartureFile(*it - 'a');
    }  
}


} //namespace ConsoleChess