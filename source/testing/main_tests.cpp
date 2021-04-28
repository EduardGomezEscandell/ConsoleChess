#include "tester.h"
#include "../defines.h"

int main(int argc, char *argv[])
{
    ConsoleChess::Verbosity verb = ConsoleChess::Verbosity::PROGRESS;
    int input = 0;

    switch(argc)
    {
    case 1:
        break;
    case 2:
        input = atoi(argv[1]);
        verb = static_cast<ConsoleChess::Verbosity>(input);
        break;
    default:
        std::cout << "Failed to parse arguments. Aborting." << std::endl;
        return 1;
    }

    ConsoleChess::Tester tester(verb);
    tester.Run();

    return tester.GetResult<int>();
}
