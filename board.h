/*
 * AUTHOR: Andrew Goulston
 * UNIQNAME: andrgoul
 * PARTNER: Summer Krinsky
 * PARTNER UNIQNAME: skrinsky
 
 */


#ifndef BOARD_H__
#define BOARD_H__

#include <ostream>
using namespace std;

// The result of the last move.
enum Result {
    IllegalMove, Draw, Win, NoResult
};

// Represents the type of occupant at a location
enum PieceType {
    Empty, Player1, Player2
};

const int NUM_ROWS = 6,
NUM_COLS = 7;

// Number of pieces in-line for a win.
const int NUM_FOR_WIN = 4;

// The way each respective piece should be represented.
const char PLAYER1_TOKEN = 'x',
PLAYER2_TOKEN = 'o',
EMPTY_TOKEN = ' ';

class Board {
public:
    // Modifies: private data members
    // Effects: Constructs an empty board with Player1 to move.
    // Difficulty: Easy
    // Topics: class constructors, array initialization
    Board();
    
    // Requires: a legal FEN string
    // Modifies: private data members
    // Effects: Constructs a board using a "fen" string. This format is based
    // on the Forsyth-Edwards notation commonly used in chess. It allows
    // a game state to be represented in a minimal way. The advantage of
    // having this constructor is for testing (ability to encode game states
    // for easier tests) and to allow games to be loaded to/from files.
    // FEN strings are explained further in the spec
    // Difficulty: Medium-Hard
    // Topics: class constructors, string parsing, testing
    Board(const std::string &fen);
    
    // Requires: os has been opened
    // Effects: Prints the board as a "fen" string (described in spec), to the specified
    // stream. This allows games to be saved to files.
    // Difficulty: Hard
    // Topics: array traversal, nested loops, streams
    void printBoard_as_FENstring(std::ostream &os) const;
    
    // Requires: os has been opened
    // This one is written for you
    // Difficulty: Super simple since it is already written
    // Topics: array traversal, streams
    void prettyPrintBoard(std::ostream &os) const;
    
    // Effects: Returns the player to move (1 for player 1, 2 for player 2)
    // Difficulty: Easy
    // Topics: member functions
    int toMove() const;
    
    
    // Note: col represents array index
    // Effects: Makes the move, returning the appropriate result -- IllegalMove, Win, Draw, NoResult.
    // The function itself is pretty simple, as it uses
    // several helper functions.
    // Difficulty: Easy-Medium
    // Topics: Use of private helper functions
    // Calls: getFirstFreeRow, updateToMove, isBoardFull, isWin
    Result makeMove(int col);


private:
    // Requires: col must be inbounds of array
    // Effects: Returns the lowest row that is Empty
    // Returns NUM_ROWS if there are no rows free.
    // Difficulty: Easy-Medium
    // Topics: array traversal
    int getFirstFreeRow(int col) const;
    
    // Effects: Changes the piece to move to the next
    //   player to move,e.g., if Player1 just moved
    //   changes piece to move to Player2
    // Returns the old one,e.g., returns Player1
    // Difficulty: Easy
    // Topics: enums, invariant maintenance
    PieceType updateToMove();
    
    // Requires: there is not a win
    // Effects: Returns true iff the game is a draw, i.e.,
    //     the board is full
    // Difficulty: Easy-Medium
    // Topics: array traversal
    bool isBoardFull() const;
    
    // Helper for piecesInDirection.
    // Effects: Returns true iff (row,col) is in bounds.
    // Difficulty: Easy
    // Topics: predicate functions
    bool inBounds(int row, int col) const;
    
    // Requires: row and col are within bounds of the array
    // Helper function for isWin.
    // Effects: Counts the number of consecutive pieces in the direction
    // of the vector, which are the same type as the piece at (row, col).
    // It DOES NOT count the piece at (row, col).
    // Returns the count
    // Difficulty: Medium
    // Topics: Array traversal (bounds checking), loop logic
    // calls: inBounds
    // sample calls:
    // int count1 = piecesInDirection(row, col, 0, -1);
    // int count2 = piecesInDirection(row, col, 1, 0);
    // Note: thinking in terms of Cartesian coordiates,
    //       dRow is the change in the row
    //       dCol is the change in the col
    int piecesInDirection(int row, int col, int dRow, int dCol) const;
    
    // Requires: row and col are within bounds of the array
    // Effects: returns true iff the piece placed at (row, col) caused a win.
    // Difficulty: Medium
    // Topics: logic/reading directions
    // Calls: piecesInDirection,
    bool isWin(int row, int col) const;
    
    // Since a board is made up of pieces, this array stores the moves
    PieceType data[NUM_ROWS][NUM_COLS];
    
    // next player to move
    PieceType nextPlayer_to_move;
};

#endif
