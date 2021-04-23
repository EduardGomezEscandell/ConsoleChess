# ConsoleChess

This project aims to create a console application to play chess. In the future I'll attempt to create a rudimentary chess engine.

## Progress
This project is a work in progress.

So far the program can:
- Compute simple moves for all pieces
- Display the board on console

Short-term goals:
- Validate if a player is in check
- Invalidate moves that put a player in check (pins)
- Implement castling rules
- Implement en passant
- Implement algebraic notation IO
- Check for end-game conditions:
  - Stalemate
  - Checkmate
  - Draw by repetition
  - Draw via the 50 move rule
  - Draw by agreement
  - Resignation

Mid-term goals:
- Impement the gameflow
- Import and output with FEN and PGN formats
- Showing stats during the game (captured pieces, etc)

Long term goals:
- Implement a rudimentary chess engine
- Use stockfish as an oponent
- Implement a rudimentary evaluation score
- Implement a GUI

## How-to ...

### Build
CMake can be used. Compilation script `build.sh` is provided for linux users. For other platforms you can use the file in `source/CMakeLists.txt`.

### Test
If you build it, two executables are generated. `ConsoleChess` runs the game. `build/ChessTests <verbosity>` runs the unit tests. Call it with different levels of verbosity (0--2) to see more or fewer details.

### Play
Wait for a few weeks while I implement the features in my free time. Then build the project and run `ConsoleChess`. Pick a colour and input your moves as requested. Either find a friend to play with or wait for a while longer while I implement an AI.
