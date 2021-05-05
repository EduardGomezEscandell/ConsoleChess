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
 * Parses the move specified as a string and returns the gathered info. Unknown values are set as -1.
 * @return Whether the move is valid
 */
bool AlgebraicReader::ParseMove(PieceSet & rPiece, PieceSet & rPromotion, Move& rMove, std::string Input)
{
    // Default values
    rPromotion = PieceSet::NONE;
    rPiece = PieceSet::NONE;
    rMove = {-1,-1,-1,-1};

    static const std::regex pawn_move(R"(([a-h]x)?[a-h](([1-7])|(8=[QRBN]))[+#=]?)");
    static const std::regex piece_move(R"(([QKRBN][a-h]?[1-8]?x?[a-h][1-8])([=\+#])?)");
    static const std::regex castling(R"((O\-O(\-O)?)([=\+#])?)");
    
    if(std::regex_match(Input, pawn_move))
    {
        rPiece = PieceSet::PAWN;
        ProcessTrailingCharacters(Input);
        ProcessPawnPromotion(rPromotion, Input);
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
        CHESS_THROW << "Castling is not yet implemented";
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
 * @param rPromotion: A reference to the promotion field, to be overwritten
 * @param rInput: The string containing the move
 */
void AlgebraicReader::ProcessPawnPromotion(PieceSet & rPromotion, std::string & rInput)
{
    std::size_t size = rInput.size();
    if(rInput[size - 2] == '=')
    {
        rPromotion = CharToPiece(rInput[size-1]);
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
    rMove.landing_rank = (rInput.back() - '1');
    rInput.pop_back();
    rMove.landing_file = (rInput.back() - 'a');
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
        rMove.departure_rank = static_cast<int>(*it - '1');
        if(++it == rInput.rend()) return;
    }

    if(*it >= 'a' && *it <= 'h')
    {
        rMove.departure_file = static_cast<int>(*it - 'a');
    }  
}


} //namespace ConsoleChess