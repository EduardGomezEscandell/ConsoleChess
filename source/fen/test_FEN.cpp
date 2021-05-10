#include "test_FEN.h"
#include "FEN.h"

namespace ConsoleChess {

namespace FENTests {

CHESS_DEFINE_TEST(Reader)
{
    Board board_fen = FEN::Reader("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"); // Starting position
    
    Board board_std;
    board_std.SetUpInitialPieces();

    for(unsigned int rank=0; rank<Board::NumberOfRanks; rank++)
    {
        for(unsigned int file=0; file<Board::NumberOfFiles; file++)
        {
            Piece * piece_fen = board_fen.pGetSquareContent(rank, file);
            Piece * piece_std = board_std.pGetSquareContent(rank, file);

            // Asserting same full/emptyness
            std::stringstream ss;
            ss << "Disagreement on whether " << Square::GetName(rank, file) << " is full or empty \n";
            AssertEqual<bool, bool, std::string>(piece_fen, piece_std, ss.str());
            if(piece_fen == nullptr) continue; // Both agree square is empty

            // Neither is empty
            ss << "Standard board and FEN disagree on constents of square " << Square::GetName(rank, file) << "\n";
            AssertEqual(piece_fen->GetPieceType(), piece_std->GetPieceType(), ss.str());
        }
    }
}

CHESS_DEFINE_TEST(ReaderNoCastling)
{
    Board board_fen = FEN::Reader("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1"); // Starting position
    
    Board board_std;
    board_std.SetUpInitialPieces();

    board_std.GetKing(Colour::WHITE)->RemoveCastlingRights();
    board_std.GetKing(Colour::BLACK)->RemoveCastlingRights();

    for(unsigned int rank=0; rank<Board::NumberOfRanks; rank++)
    {
        for(unsigned int file=0; file<Board::NumberOfFiles; file++)
        {
            Piece * piece_fen = board_fen.pGetSquareContent(rank, file);
            Piece * piece_std = board_std.pGetSquareContent(rank, file);

            // Asserting same full/emptyness
            std::stringstream ss;
            ss << "Disagreement on whether " << Square::GetName(rank, file) << " is full or empty \n";
            AssertEqual<bool, bool, std::string>(piece_fen, piece_std, ss.str());
            if(piece_fen == nullptr) continue; // Both agree square is empty

            // Neither is empty
            ss << "Standard board and FEN disagree on constents of square " << Square::GetName(rank, file) << "\n";
            AssertEqual(piece_fen->GetPieceType(), piece_std->GetPieceType(), ss.str());
        }
    }
}

CHESS_DEFINE_TEST(ReaderSomeCastling)
{
    Board board_fen = FEN::Reader("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w kq - 0 1"); // Starting position but white can't castle
    
    Board board_std;
    board_std.SetUpInitialPieces();

    board_std.GetKing(Colour::WHITE)->RemoveCastlingRights();

    for(unsigned int rank=0; rank<Board::NumberOfRanks; rank++)
    {
        for(unsigned int file=0; file<Board::NumberOfFiles; file++)
        {
            Piece * piece_fen = board_fen.pGetSquareContent(rank, file);
            Piece * piece_std = board_std.pGetSquareContent(rank, file);

            // Asserting same full/emptyness
            std::stringstream ss;
            ss << "Disagreement on whether " << Square::GetName(rank, file) << " is full or empty \n";
            AssertEqual<bool, bool, std::string>(piece_fen, piece_std, ss.str());
            if(piece_fen == nullptr) continue; // Both agree square is empty

            // Neither is empty
            ss << "Standard board and FEN disagree on constents of square " << Square::GetName(rank, file) << "\n";
            AssertEqual(piece_fen->GetPieceType(), piece_std->GetPieceType(), ss.str());
        }
    }
}

CHESS_DEFINE_TEST(ReaderExtraFields)
{
    Board board_fen = FEN::Reader("rnbqkbnr/ppp1pppp/8/3p4/8/8/PPPPPPPP/RNBQKBNR b KQkq d3 0 2"); // Position after 1d4
    
    AssertEqual(board_fen.WhoMoves(), Colour::BLACK, "Failed to read whose turn it is to move");
    AssertEqual(board_fen.GetMoveCount(), (unsigned int) 2, "Failed to read the move count");

    Square * square = board_fen.GetEnPassantSquare();

    AssertTrue(square, "Failed to parse en passant square");
    AssertEqual(square->GetRank(), 2u, "Failed to read en passant square's rank");
    AssertEqual(square->GetFile(), 3u, "Failed to read en passant square's file");
}

CHESS_DEFINE_TEST(Writer)
{
    Board board;
    board.SetUpInitialPieces();

    const std::string fen = FEN::Writer(board);
    const std::string fen_expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    AssertEqual(fen, fen_expected, "Failed to generate FEN string for initial position");
}

}



CHESS_TEST_LIST(FENTestSuite)
{
    CHESS_TEST_LIST_ITEM(FENTests::Reader)
    CHESS_TEST_LIST_ITEM(FENTests::ReaderNoCastling)
    CHESS_TEST_LIST_ITEM(FENTests::ReaderSomeCastling)
    CHESS_TEST_LIST_ITEM(FENTests::ReaderExtraFields)
    CHESS_TEST_LIST_ITEM(FENTests::Writer)
}


}
