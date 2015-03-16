#ifndef connect4_h__
#define connect4_h__

#include "board.h"
#include <string>
using namespace std;

// Effects: Lets the user choose whether to start a new game, or load an
// existing one. Returns the game board. modifies p1 and p2 to be
// the player names.
// Difficulty: Easy-Medium
// Topics: Basic/IO, pass by reference, class construction
// Note: you may assume that the file will always open
//       you may put in error checking if you wish -- make your own
//       decisions on wha should happen wih error checking
// Note: the format of the file is:
//     name1
//     name2
//     FENstring
Board getBoard(string &p1, string &p2);

// Prompts the user for the filename, and saves the board.
// Difficulty: Easy
// Topics: streams
// Note: you may assume that the file will always open
//       you may put in error checking if you wish -- make your own
//       decisions on what should happen with error checking
// Note: the format of the file is:
//     name1
//     name2
//     FENstring
void saveBoard(string p1, string p2, const Board &board);

#endif

