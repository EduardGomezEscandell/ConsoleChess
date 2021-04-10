cmake_minimum_required(VERSION 3.5)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Chess main.cpp
                     interface.cpp
                     game.cpp
                     piece.cpp
                     board.cpp)
