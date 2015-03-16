/*
 * AUTHOR: Andrew Goulston
 * UNIQNAME: andrgoul
 * PARTNER: Summer Krinsky
 * PARTNER UNIQNAME: skrinsky
 
 */




#include "connect4.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    
    
    // for playing the game
    
    //our two players
    string p1;
    string p2;
    int move = 0;
    

    // Creates a New Game based upon a gameboard sourced from getBoard

    Board gameBoard;
    gameBoard = getBoard(p1,p2);
    
    Result var = NoResult;
    
    
    
    while (var == NoResult)
    {
        gameBoard.prettyPrintBoard(cout);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        
        
        int currentPlayer = gameBoard.toMove();
        
        string rememberPlayer;
        
        if (currentPlayer == 1)
        {
            rememberPlayer = p1;
            cout << p1 << " enter your move: ";
            cin >> move;
        }
        else
        {
            rememberPlayer = p2;
            cout << p2 << " enter your move: ";
            cin >> move;
        }
        
        
            
            if (!cin.good())
            {
                cin.clear();
                char overwrite;
                cin >> overwrite;
                
                if (overwrite == 'q' || overwrite == 'Q')
                {
                    
                    //var = IllegalMove;
                    cout << "Thanks for playing!"<< endl;
                    return 0;
                }

                
                else if ((overwrite == 'S' || overwrite == 's') && currentPlayer == 1)
                {
                    var = NoResult;
                    saveBoard(p1, p2, gameBoard);
                    gameBoard.prettyPrintBoard(cout);
                    cout << "\nEnter: the column to move, q to quit, s to save" << endl;
                    cout << p1 << " enter your move: ";
                    cin >> move;
                    move = move -1;
                    var = gameBoard.makeMove(move);

                      
                }
                else if((overwrite == 'S' || overwrite == 's') && currentPlayer == 2)
                {
                    var = NoResult;
                    saveBoard(p1, p2, gameBoard);
                    gameBoard.prettyPrintBoard(cout);
                    cout << "\nEnter: the column to move, q to quit, s to save" << endl;
                    cout << p2 << " enter your move: ";
                    cin >> move;
                    move = move -1;
                    var = gameBoard.makeMove(move);
                      
                }
                else
                {
                    cout << "ILLEGAL MOVE: Try again" << endl;
                    
                }
 
              }
            else
            {
                move = move -1;
                var = gameBoard.makeMove(move);
    
    
                if(var == IllegalMove)
                {
                    cout << "ILLEGAL MOVE: Try again" << endl;
                    
                    var = NoResult;
            
                }
            }
    }
    
    if (var == Draw)
    {
        cout << "Draw!" << endl;
        gameBoard.prettyPrintBoard(cout);
    }
    
    else if (var == Win)
    {
        string winner;
        
        if (gameBoard.toMove() == 1)
        {
            winner = p2;
        }
        else
        {
            winner = p1;
        }
        
        
        cout << "Congratulations ";
        cout << winner << "! You won!" << endl;
        gameBoard.prettyPrintBoard(cout);
    }
    
    
    
   
      return 0;
    
}
 

Board getBoard(string &p1, string &p2)
{
    cout << "Enter L to load a game, or P to play: " << flush;
    
    
    
    
    char lorp;
    
    cin >> lorp;
    
   
    
    
    
        if (lorp == 'L' || lorp == 'l')
        {
            cout << "Enter the filename: " << flush;
            
            string filename;
            cin >> filename;
            
            ifstream previousGame;

            string fenString;
            
            previousGame.open(filename.c_str());
            
            
            getline(previousGame,p1);
            getline(previousGame,p2);
            getline(previousGame,fenString);
            
            
            return Board(fenString);
            
        }
    
        else if(lorp == 'P' || lorp == 'p')
        {
            
            
            cout << "Player 1, enter your name: " << flush;
            cin >> p1;
            cout << endl << "Player 2, enter your name: " << flush;
            cin >> p2;
            Board newBoard;
    
        }
    
        else
        {
            cout << "Enter the filename: " << flush;
            
            string filename;
            cin >> filename;
            
            ifstream previousGame;
            
            string fenString;
            
            previousGame.open(filename.c_str());
            
            
            getline(previousGame,p1);
            getline(previousGame,p2);
            getline(previousGame,fenString);
            
            
            return Board(fenString);

        }
    
    
    

    
    
    return Board();
}

void saveBoard(string p1, string p2, const Board &board)
{
    cout << "Enter the filename: " << flush;
    ofstream savingGame;
    
    string savingName;
    
    cin >>  savingName;
    savingGame.open(savingName.c_str());
    
    
    
    savingGame << p1 << endl;
    savingGame << p2 << endl;
    board.printBoard_as_FENstring(savingGame);
    
    
}
