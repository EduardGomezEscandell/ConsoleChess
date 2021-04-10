#ifndef DEFINES_H
#define DEFINES_H



namespace ConsoleChess {


enum Colour
{
    White,
    Black,
    Undefined
};

enum File
{
    a = 0,
    b = 1,
    c = 2,
    d = 3,
    e = 4,
    f = 5,
    g = 6,
    h = 7,
    undefined = -1
};

struct Move
{
    const int delta_rank;
    const int delta_file;
};



}

#endif // DEFINES_H
