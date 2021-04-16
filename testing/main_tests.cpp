#include "tester.h"
#include "../defines.h"

int main()
{
    ConsoleChess::Tester tester(ConsoleChess::Verbosity::FULL);
    tester.Run();
}
