cmake_minimum_required(VERSION 3.5)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting warning levels
if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Compiling game
add_executable(ConsoleChess main.cpp
                            defines.cpp
                            interface/interface.cpp
                            game.cpp
                            piece.cpp
                            move.cpp
                            square.cpp
                            board/board.cpp
                            knight/knight.cpp
                            king/king.cpp
                            rook/rook.cpp
                            bishop/bishop.cpp
                            queen/queen.cpp
                            pawn/pawn.cpp
                            algebraic_notation/algebraic_notation.cpp
)

# Compiling unit tests
add_executable(ConsoleChessTests testing/main_tests.cpp
                                 testing/tester.cpp
                                 testing/test_suite.cpp
                                 testing/test.cpp
                                 defines.cpp
                                 interface/interface.cpp
                                 interface/test_interface.cpp
                                 game.cpp
                                 piece.cpp
                                 move.cpp
                                 square.cpp
                                 board/board.cpp
                                 board/test_board.cpp
                                 knight/knight.cpp
                                 knight/test_knight.cpp
                                 king/king.cpp
                                 king/test_king.cpp
                                 rook/rook.cpp
                                 rook/test_rook.cpp
                                 bishop/bishop.cpp
                                 bishop/test_bishop.cpp
                                 queen/queen.cpp
                                 queen/test_queen.cpp
                                 pawn/pawn.cpp
                                 pawn/test_pawn.cpp
                                 algebraic_notation/algebraic_notation.cpp
                                 algebraic_notation/test_algebraic.cpp
)
