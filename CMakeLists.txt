cmake_minimum_required(VERSION 3.5)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Chess main.cpp
                     interface.cpp
                     game.cpp
                     piece.cpp
                     board/board.cpp
                     knight/knight.cpp)

add_executable(ChessTests testing/main_tests.cpp
                          testing/tester.cpp
                          testing/test_suite.cpp
                          testing/test.cpp
                          knight/test_knight.cpp
                          interface.cpp
                          game.cpp
                          piece.cpp
                          board/board.cpp
                          board/test_board.cpp
                          knight/knight.cpp)
