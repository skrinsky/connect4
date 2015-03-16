/*
 * AUTHOR: Andrew Goulston
 * UNIQNAME: andrgoul
 * PARTNER: Summer Krinsky
 * PARTNER UNIQNAME: skrinsky
 
 */


#include "board.h"


Board::Board() //Tested
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for ( int j = 0; j < NUM_COLS; j++)
        {
            data[i][j] = Empty;
        }
    }
    
    nextPlayer_to_move = Player1;
}




Board::Board(const string &fen) // working
{
    int row=0;
    int col=0;
    
    
    
    
    for(int spot=0; spot<fen.length()-2; spot++)
    {
        
        
            if(fen[spot]==PLAYER1_TOKEN)
            {
                
                data[row][col]=Player1;
                col++;
                
            }
            
            else if(fen[spot]==PLAYER2_TOKEN)
            {
                
                data[row][col]=Player2;
                col++;
                
            }
            
            else if(fen[spot]=='/')
            {
                
                row++;
                col=0;
                
            }
            
            else
            {
                
                int white= fen[spot]-'0';
                for(int i=0; i<white; i++)
                {
                    data[row][col]=Empty;
                    col++;
                    
                }
                
            }
    }
    
    if (fen.at(fen.length()-1) == 'x')
    {
        nextPlayer_to_move = Player1;
        
    }
    else if (fen.at(fen.length()-1) == 'o')
    {
        nextPlayer_to_move = Player2;
    }
    else
    {
        
    }

    
    
}









void Board::printBoard_as_FENstring(ostream &os) const
{
    int empty_count = 0;
    
    
    for (int i = 0; i < NUM_ROWS; i++)
    {
        if (i != 0)
            os << '/';
    
    
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (data[i][j] == Player1)
            {
                if (empty_count != 0)
                {
                    os <<empty_count;
                    empty_count = 0;
                }
                os << PLAYER1_TOKEN;
            }
            
            else if (data[i][j] == Player2)
            {
                if (empty_count != 0)
                {
                    os << empty_count;
                    empty_count =0;
                }
                os << PLAYER2_TOKEN;
            }
            
            else
            {
                empty_count++;
            }
            
        }
        
        
        if (empty_count != 0)
        {
            os << empty_count;
            empty_count = 0;
        }
        
    }
    
    if (nextPlayer_to_move == Player1)
    {
        os << " x";
    }
    else
    {
        os << " o";
    }

}


void Board::prettyPrintBoard(ostream &os) const // Given and therefore tested do not change this under any circumstance
{
    
	os << endl;
    for (int row = NUM_ROWS - 1; row >= 0; row--)
    {
        os << "     +---+---+---+---+---+---+---+"
        << endl
        << "    ";
        
        for (int col = 0; col < NUM_COLS; col++)
        {
            os << " | " ;
            if ( data[row][col] == Player1)
                os <<  PLAYER1_TOKEN;
            else if (data[row][col] == Player2)
                os << PLAYER2_TOKEN;
            else
                os << EMPTY_TOKEN;
        }
        os << " |" << endl;
    }
    os << "     +---+---+---+---+---+---+---+" << endl
    <<"  col  1   2   3   4   5   6   7" << endl;
    return;
}


Result Board::makeMove(int col)
{

        //Partner does not have this if statement did not need it
    
        int row=getFirstFreeRow(col);
        
        if(col < 0 || col > 6 || row == 6)
        {
            return IllegalMove;
        }
        
        else if ((data[row][col]= nextPlayer_to_move))
        {
            
            
            if (isWin(row, col)==true)
            {
                updateToMove();// told to add these
                return Win;
            }
            
            else if (isBoardFull()==true)
            {
                updateToMove(); //told to add these
                return Draw;
            }
            
            else
            {
                updateToMove();
                return NoResult;
            }
        }
        
        return NoResult;
}





int Board::toMove() const // Tested by changing nextPlayer_to_move in Board() above
{
    
    
    if (nextPlayer_to_move == Player1)
    {
        return 1;
    }
    else if (nextPlayer_to_move == Player2)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}



// - Private Functions below

int Board::getFirstFreeRow(int col) const // tested
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        if ( data[i][col] == Empty)
        {
            return i;
        }
    }
    return NUM_ROWS;
}




PieceType Board::updateToMove()
{
    if (toMove()==2)
    {
        nextPlayer_to_move=Player1;
        return Player2;
    }
    else if (toMove()==1)
    {
        nextPlayer_to_move=Player2;
        return Player1;
    }
    else
    {
        return Empty;
    }
    
}



bool Board::isBoardFull() const
{
    for ( int i = 0; i < NUM_ROWS; i++)
    {
        for ( int j = 0; j < NUM_COLS; j++)
        {
            if (data[i][j] == Empty)
            {
                return false;
            }
            
        }
    }
    return true;
}




bool Board::inBounds(int row, int col) const // tested via testingInBounds()
{
    if ( row > NUM_ROWS-1 || col > NUM_COLS-1 || row < 0 || col < 0)
    {
        return false;
    }
    
    return true;
}




int Board::piecesInDirection(int row, int col, int dRow, int dCol) const
{
    
    int count1 = 0;

    PieceType player = data[row][col];
    
    
    row += dRow;
    col += dCol;
    
    while (inBounds(row, col) && data[row][col]== player)
    {
                
        count1++;
        row += dRow;
        col += dCol;
    }
    return count1;
     
}
    
bool Board::isWin(int row, int col) const
{
    
    // Measures on the Horizontal Right + Left
    if (piecesInDirection(row, col, 0, 1) + piecesInDirection(row, col, 0, -1) >= 3 )
    {
        
        return true;
    }
    //measures vertical up + Vertical Down
    else if (piecesInDirection(row, col, 1, 0) + piecesInDirection(row, col, -1, 0) >= 3)
    {
        
        return true;
    }
    // measures diagnol up left + diagnol down right
    else if(piecesInDirection(row, col, 1, -1) + piecesInDirection(row, col, -1, 1) >= 3)
    {
        
        return true;
    }
    
    // measures diagnol Up Right + diagnol down left
    else if (piecesInDirection(row, col, 1, 1) + piecesInDirection(row, col, -1, -1) >= 3)
    {
        
        return true;
    }
    else
    {
        return false;
    }
    return false;
    
}
    

