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

    // TODO: Test other FEN fields

}

CHESS_DEFINE_TEST(Writer)
{
    Board board;
    board.SetUpInitialPieces();

    const std::string fen = FEN::Writer(board);
    const std::string fen_expected = "RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w KQkq - 0 1";

    AssertEqual(fen, fen_expected, "Failed to generate FEN string for initial position");
}

}



CHESS_TEST_LIST(FENTestSuite)
{
    CHESS_TEST_LIST_ITEM(FENTests::Reader)
    CHESS_TEST_LIST_ITEM(FENTests::Writer)
}


}
