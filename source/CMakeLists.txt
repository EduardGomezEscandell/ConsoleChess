cmake_minimum_required(VERSION 3.5)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ConsoleChess main.cpp
                     defines.cpp
                     interface.cpp
                     game.cpp
                     piece.cpp
                     move.cpp
                     board/board.cpp
                     knight/knight.cpp
                     king/king.cpp
                     rook/rook.cpp
                     bishop/bishop.cpp
                     queen/queen.cpp
                     pawn/pawn.cpp)

add_executable(ConsoleChessTests testing/main_tests.cpp
                          testing/tester.cpp
                          testing/test_suite.cpp
                          testing/test.cpp
                          defines.cpp
                          interface.cpp
                          game.cpp
                          piece.cpp
                          move.cpp
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
                          pawn/test_pawn.cpp)
