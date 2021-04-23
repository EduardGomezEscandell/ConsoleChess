#include "test_interface.h"
#include "interface.h"
#include <string>

namespace ConsoleChess {

namespace InterfaceTests {

/**
 * Tests if the move parser can read the moves, does not validate if they are legal
 * 
 */
CHESS_DEFINE_TEST(MoveParser)
{
    std::string input;
    PieceSet piece, promotion;
    int departure_rank, departure_file , landing_rank, landing_file;
    bool valid_move;

    // EXAMPLE 1
    input = "e5+";
    valid_move = Interface::ParseMove(piece, promotion, departure_rank, departure_file, landing_rank, landing_file, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 1");
    this->AssertEqual(piece, PieceSet::PAWN, "Failed to read the piece in example 1");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to read the promotion in example 1");
    this->AssertEqual(departure_file, -1, "Failed to read the departure_file in example 1");
    this->AssertEqual(departure_rank, -1, "Failed to read the departure_rank in example 1");
    this->AssertEqual(landing_rank, 4, "Failed to read the landing_rank in example 1");
    this->AssertEqual(landing_file, 4, "Failed to read the landing_file in example 1");

    // EXAMPLE 2
    input = "Rxc6";
    valid_move = Interface::ParseMove(piece, promotion, departure_rank, departure_file, landing_rank, landing_file, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 2");
    this->AssertEqual(piece, PieceSet::ROOK, "Failed to read the piece in example 2");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to read the promotion in example 2");
    this->AssertEqual(departure_file, -1, "Failed to read the departure_file in example 2");
    this->AssertEqual(departure_rank, -1, "Failed to read the departure_rank in example 2");
    this->AssertEqual(landing_rank, 5, "Failed to read the landing_rank in example 2");
    this->AssertEqual(landing_file, 2, "Failed to read the landing_file in example 2");


    // EXAMPLE 3
    input = "Rexc6=";
    valid_move = Interface::ParseMove(piece, promotion, departure_rank, departure_file, landing_rank, landing_file, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 3");
    this->AssertEqual(piece, PieceSet::ROOK, "Failed to read the piece in example 3");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to read the promotion in example 3");
    this->AssertEqual(departure_file, 4, "Failed to read the departure_file in example 3");
    this->AssertEqual(departure_rank, -1, "Failed to read the departure_rank in example 3");
    this->AssertEqual(landing_rank, 5, "Failed to read the landing_rank in example 3");
    this->AssertEqual(landing_file, 2, "Failed to read the landing_file in example 3");

    // EXAMPLE 4
    input = "gxh8=Q#";
    valid_move = Interface::ParseMove(piece, promotion, departure_rank, departure_file, landing_rank, landing_file, input);
    
    this->AssertEqual(valid_move, true, "Failed to recognize the validity of example 4");
    this->AssertEqual(piece, PieceSet::PAWN, "Failed to read the piece in example 4");
    this->AssertEqual(promotion, PieceSet::QUEEN, "Failed to read the promotion in example 4");
    this->AssertEqual(departure_file, 6, "Failed to read the departure_file in example 4");
    this->AssertEqual(departure_rank, -1, "Failed to read the departure_rank in example 4");
    this->AssertEqual(landing_rank, 7, "Failed to read the landing_rank in example 4");
    this->AssertEqual(landing_file, 7, "Failed to read the landing_file in example 4");


    // EXAMPLE 5
    input = "qh8"; // this move is a typo, should be Qh8
    valid_move = Interface::ParseMove(piece, promotion, departure_rank, departure_file, landing_rank, landing_file, input);
    
    this->AssertEqual(valid_move, false, "Failed to recognize the non-validity of example 5");
    this->AssertEqual(piece, PieceSet::NONE, "Failed to read the piece in example 5");
    this->AssertEqual(promotion, PieceSet::NONE, "Failed to clean up the promotion in example 5");
    this->AssertEqual(departure_file, -1, "Failed to clean up the departure_file in example 5");
    this->AssertEqual(departure_rank, -1, "Failed to clean up the departure_rank in example 5");
    this->AssertEqual(landing_rank, -1, "Failed to clean up the landing_rank in example 5");
    this->AssertEqual(landing_file, -1, "Failed to clean up the landing_file in example 5");
    
    
}


}



CHESS_TEST_LIST(InterfaceTestSuite)
{
    CHESS_TEST_LIST_ITEM(InterfaceTests::MoveParser)
}


}
