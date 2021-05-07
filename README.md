# ConsoleChess

This project aims to create a console application to play chess. In the future I'll attempt to create a rudimentary chess engine.

## Progress
This project is a work in progress.

So far the program can:
- Perform most moves:
  - Pieces
  - Pawn capture, single and double advance and promotion.
  - Castling
- Disallow moving the king into check.
- Display the board on console.
- Parse a move in algebraic input notation.
- Validate if a player is in check.
- Export the gamestate in FEN format.
- Import the gamestate in FEN format (UI not implemented).

Short-term goals:
- Implement missing movement rules:
  - Invalidate moves that put a player in check (pins)
  - En passant
- Output a move in algebraic notation
- Check for end-game conditions:
  - Stalemate
  - Checkmate
  - Draw by repetition
  - Draw via the 50 move rule
  - Draw by agreement
  - Resignation

Mid-term goals:
- Impement the gameflow
- Import and export of games in PGN format.
- Show stats during the game:
  - Captured pieces
  - Move history
  - Valid moves

Long term goals:
- Implement a rudimentary chess engine
- Use stockfish as an oponent
- Implement a rudimentary accuracy score
- Implement a GUI

## How-to ...

### Build
CMake can be used. Compilation script `build.sh` is provided for linux users. For other platforms you can use the file in `source/CMakeLists.txt`.

### Test
If you build it, two executables are generated. `build/Release/ConsoleChess` runs the game. `build/Release/ChessTests <verbosity>` runs the unit tests. Call it with different levels of verbosity (0--2) to see more or fewer details.

### Play
Build the project and run `ConsoleChess`.Input your moves as requested. Either find a friend to play with or wait for a while longer while I implement an AI.
You can use commands for varius reasons. Use `/help` when asked for a move for a summary of possible commands. You can, for instance, export your gamestate in FEN format with `/fen`.

Note that some features are missing (see previous sections)
