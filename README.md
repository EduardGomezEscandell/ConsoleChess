# ConsoleChess

This project aims to create a console application to play chess. In the future, I'll attempt to create a rudimentary chess engine.

## Progress
This project is a work in progress.

So far the program can:
- Perform most moves:
  - Pieces
  - Pawn capture, single and double advance, promotion and capture en passant.
  - Castling
- Disallow moving the king into check.
- Display the board on the console.
- Parse a move in algebraic input notation.
- Validate if a player is in check.
- Export the game-state in FEN format (except half-move clock: 0 is printed).
- Import the game-state in FEN format (except half-move clock: it is ignored).
- Run the game between two players (except end of game).

Short-term goals:
- Implement missing movement rules:
  - Invalidate moves that put a player in check (pins)
- Output a move in algebraic notation
- Check for end-game conditions:
  - Stalemate
  - Checkmate
  - Draw by repetition
  - Draw via the 50 move rule
  - Draw by agreement
  - Resignation

Mid-term goals:
- Import and export of games in PGN format.
- Show stats during the game:
  - Captured pieces
  - Move history
  - Valid moves

Long term goals:
- Implement a rudimentary chess engine
- Use stockfish as an opponent
- Implement a rudimentary accuracy score
- Implement a GUI

## How to ...

### Build
Compilation script `build.sh` is provided for Linux users. For other platforms, you can use the file in `source/CMakeLists.txt`.

### Test
If you build it, two executables are generated. `build/Release/ConsoleChess` runs the game. `build/Release/ChessTests <verbosity>` runs the unit tests. Call it with different levels of verbosity (0--2) to see more or fewer details.

### Play
Build the project and run `ConsoleChess`.Input your moves as requested. Either find a friend to play with or wait for a while longer while I implement an AI.
You can use commands for various purposes. Use `/help` when asked for a move for a summary of possible commands. You can, for instance, export your game state in FEN format with `/fen`.

Note that some features are missing (see previous sections).
