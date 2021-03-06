#include "FEN.h"
#include "../defines.h"

#include "regex"

namespace ConsoleChess
{

std::tuple<PieceSet, Colour> GetPieceFromFEN(char c)
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


bool FEN::Validator(const char * str)
{
    static const std::regex regex(R"((([rnbqkpRNBQKP1-8]{1,8}|[1-8])\/){7}([rnbqkpRNBQKP1-8]{1,8}|[1-8])( [wb] ((K{0,1}Q{0,1}k{0,1}q{0,1})|-) (-|[a-h][36]) [0-9]+ [0-9]+){0,1})");

    bool valid = std::regex_match(str, regex);
    if(!valid) return false;

    // Ensuring all ranks have 8 files
    unsigned int counter = 0;
    for(const char * ptr = str; *ptr != '\0'; ptr++)
    {
        const char c = *ptr;
        if(c==' ') break; // End of block

        if(c=='/')
        {
            if(counter != 8) return false;
            counter=0;
        }
        else if(c > '0' && c<'9')
        {
            counter += static_cast<unsigned int>(c - '0');
        }
        else
        {
            counter++;
        }
    }

    if(counter != 8) return false; // Last rank check

    return true;
}

/**
 * @brief Returns a board from a string containing Forsyth–Edwards Notation (FEN)
 * 
 * @param str: The FEN string
 * @returns The board generated
 */
Board FEN::Reader(const char * str)
{
    Board board;

    if(!FEN::Validator(str)) CHESS_THROW << "Invalid FEN : \n    <" << str << ">\n";

    const char * it = str-1;
    
    // Reading position block
    {
        unsigned int file = 0;
        unsigned int rank = 7;

        while(*(++it) != ' ') // Iterating chars until spacebar is reached
        {
            const char c = *it;

            if(c=='\0') return board; // Short notation

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
                    CHESS_THROW << "Unexpected character when reading FEN : " << c;
                }

                board.CreatePieceInLocation(piece_type, rank, file, col);
                file++;
            }
        }
    }

    // Active colour
    it++;
    if(*it == 'b')
    {
        board.SetColourToMove(Colour::BLACK);
    }
    else
    {
        board.SetColourToMove(Colour::WHITE);
    }
    it++;

    // Castling
    {
        bool WhiteLong  = false;
        bool WhiteShort = false;
        bool BlackLong  = false;
        bool BlackShort = false;

        while(*(++it) != ' ') // Iterating chars until spacebar is reached
        {
            switch (*it)
            {
                case 'K':    WhiteShort = true;    break;
                case 'Q':    WhiteLong  = true;    break;
                case 'k':    BlackShort = true;    break;
                case 'q':    BlackLong  = true;    break;
                case '-':   break;
            }
        }

        if(!WhiteLong)
        {
            Piece * rook = board.pGetSquareContent(0,0);
            if(rook && rook->GetColour()==Colour::WHITE) rook->RemoveCastlingRights();
        }

        if(!WhiteShort)
        {
            Piece * rook = board.pGetSquareContent(0,7);
            if(rook && rook->GetColour()==Colour::WHITE) rook->RemoveCastlingRights();
        }

        if(!BlackLong)
        {
            Piece * rook = board.pGetSquareContent(7,0);
            if(rook && rook->GetColour()==Colour::BLACK) rook->RemoveCastlingRights();
        }

        if(!BlackShort)
        {
            Piece * rook = board.pGetSquareContent(7,7);
            if(rook && rook->GetColour()==Colour::BLACK) rook->RemoveCastlingRights();
        }
    }

    // En Passant target square
    it++;
    if(*it != '-')
    {
        const unsigned int file = *it - 'a';
        it++;
        const unsigned int rank = *it - '1';
        it++;
        board.SetEnPassantTarget(rank, file);
    }
    else
    {
        it++;
    }

    // Halfmove clock
    while(*(++it) != ' ') // Iterating chars until spacebar is reached;
    {
        // TODO
    }

    // Move counter
    it++;
    board.SetMoveCounter(atoi(it));

    return board;
}

bool RookCanCastle(const Board & rBoard, const int rank, const int file, Colour colour)
{
    const Piece * corner_piece = rBoard.pGetSquareContent(rank, file);
    if(!corner_piece) return false;                                     // Square is empty
    if(corner_piece->GetPieceType() != PieceSet::ROOK) return false;    // Square is occupied by another piece type
    if(corner_piece->GetColour() != colour) return false;               // Rook is enemy rook
    return corner_piece->HasCastlingRights();
}


std::string FEN::Writer(const Board & rBoard)
{
    std::stringstream output;

    // Board state
    for(int r=7; r>=0; r--)
    {
        unsigned int count = 0;

        for(int f=0; f<8; f++)
        {
            const Square & square = rBoard.GetSquare(r,f);
            if(square.IsEmpty())
            {
                count++;
            }
            else // There is a piece
            {
                if(count > 0)
                {
                    output << count;
                    count = 0;
                }
                output << square.pGetContent()->GetPieceCharacter();
            }
            
        }

        // End of rank
        if(count > 0)
        {
            output << count;
        }
        if(r != 0)
        {
            output << '/';
        }
    }
    output << ' ';

    // Active colour
    output << (rBoard.WhoMoves() == Colour::WHITE ? 'w' : 'b') << ' ';

    // Castling
    bool no_castling = true;
    if(rBoard.GetKing(Colour::WHITE) && rBoard.GetKing(Colour::WHITE)->HasCastlingRights())
    {
        if(RookCanCastle(rBoard, 0, 7, Colour::WHITE))
        {
            output << 'K';
            no_castling=false;
        }
        if(RookCanCastle(rBoard, 0, 0, Colour::WHITE))
        {
            output << 'Q';
            no_castling=false;
        }
    }
    if(rBoard.GetKing(Colour::BLACK) && rBoard.GetKing(Colour::BLACK)->HasCastlingRights())
    {
        if(RookCanCastle(rBoard, 7, 7, Colour::BLACK))
        {
            output << 'k';
            no_castling=false;
        }
        if(RookCanCastle(rBoard, 7, 0, Colour::BLACK))
        {
            output << 'q';
            no_castling=false;
        }
    }
    
    if(no_castling)
    {
        output << '-';
    }

    output << ' ';

    // En passant:
    const Square * en_passant_square = rBoard.GetEnPassantSquare();
    if(en_passant_square)
    {
        output << en_passant_square->GetName() << ' ';
    }
    else
    {
        output << "- ";
    }

    // Halfmove clock: TODO
    output << "0 ";

    // Fullmove clock
    output << rBoard.GetMoveCount();

    return output.str();
}

}