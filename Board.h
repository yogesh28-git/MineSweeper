#ifndef Board_HEADER
#define Board_HEADER

#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <chrono> 
#include <thread>
#include <string>
#include "Cells.h"

std::chrono::milliseconds gameoverDuration(1500);

enum Operations
{
    open,
    markOrUnmark
};

struct Position
{
    short x;
    short y;
};

class Board
{
    private:
        Cell board[10][10];
        bool minesDistributed = false;
        std::vector<Position> mines;
        bool gameOver = false;
        short openCellCount = 0;
        bool gameWin = false;

        std::vector<Position> surroundingsChecker(Position pos, cellValue value, bool excluding = false)
        {
            std::vector<Position> vec;
            for(short i= pos.x-1; i<= pos.x +1; ++i)
            {
                if(i<0 || i>9){continue;} //out of bounds
                for(short j= pos.y-1; j<=pos.y +1; ++j)
                {
                    if(j<0 || j>9){continue;} //out of bounds
                    if(i==pos.x && j==pos.y){continue;}    // skip the middle cell. we are checking only its surroundings
                    if((excluding && board[i][j].getValue() != value) || (!excluding && board[i][j].getValue() == value))
                    { // an XOR gate
                        Position p1;
                        p1.x = i;
                        p1.y = j;
                        vec.push_back(p1);
                    }
                }
            }
            return vec;
        }

        void distributeMines(Position exclude)
        {
            //Create 10 mines
            int count = 0;
            Position p1;
            srand(time(0));
            
            while(count<10)
            {
                p1.x = rand() % 10 ;
                p1.y = rand() % 10 ;
                
                if(p1.x == exclude.x && p1.y == exclude.y) //exclusion of first input
                continue;                                             
                else if(board[p1.x][p1.y].getValue() == cellValue::mine)  //if already a mine was there
                continue;                                             
                else
                {
                    board[p1.x][p1.y].setValue(cellValue::mine);
                    mines.push_back(p1); 
                    ++count; 
                }
            }
            setRemainingValues();
             
        }

        void setRemainingValues()
        {
            for(int i=0; i<mines.size(); i++)
            {
                // get surrounding cells which are not mines. They are to be numbered.
                std::vector<Position> surrVector = surroundingsChecker(mines[i], cellValue::mine, true);

                for(int j=0; j<surrVector.size(); j++)
                {
                    //increment the number by one. enum cellValues defined according to the numbers
                    short tempValue = static_cast<short>( board[surrVector[j].x][surrVector[j].y].getValue() );
                    tempValue++;
                    board[surrVector[j].x][surrVector[j].y].setValue(static_cast<cellValue>(tempValue));
                }
            }
        }

        void openCell(Position p)
        {
            //distribute mines only once after the first input. x and y to be excluded.
            if(!minesDistributed)
            {
                minesDistributed = true;
                distributeMines(p);
            }
            cellValue currValue = board[p.x][p.y].getValue();

            switch(currValue)
            {
                case cellValue::mine: //gameover condition
                    board[p.x][p.y].setState(cellState::opened);
                    gameOver = true;
                    cleanUP();
                    break;
                case cellValue::space: //we need to display all spaces and numbers around the space.
                    openSpaces(p);
                    break;
                default: //it's a number, so simply open it.
                    board[p.x][p.y].setState(cellState::opened);
                    openCellCount++;
                    break;
            }
                    
            if(openCellCount == 90)
            {
                gameWin = true;
            }
        }
        void openSpaces(Position p)
        {
            std::queue<Position> q;
            q.push(p);
            board[p.x][p.y].setState(cellState::opened);
            openCellCount++;
            while(!q.empty())
            {
                Position temp = q.front();
                std::vector<Position> surrVec = surroundingsChecker(temp, cellValue::invalid, true); //get all surrounding values
                for(auto iter: surrVec)
                {
                    cellState currState = board[iter.x][iter.y].getState();
                    if(currState == cellState::opened)
                    {
                        continue;  //skip those that are already opened
                    }
                    cellValue currValue = board[iter.x][iter.y].getValue();
                    if(currValue == cellValue::space)
                    {
                        q.push(iter);
                    }
                    board[iter.x][iter.y].setState(cellState::opened);
                    openCellCount++;
                }
                q.pop();
            }
        }
        void cleanUP()
        {
            system("cls");
            boardDisplay();
            std::cout<<std::endl;
            std::this_thread::sleep_for(gameoverDuration);
            for(auto iter: mines)
            {
                board[iter.x][iter.y].setState(cellState::opened);
            }
            system("cls");
            boardDisplay();
        }

    public:
        
        //Constructor
        Board()
        {
            
        }
        bool getGameOver()
        {
            return gameOver;
        }
        bool getGameWin()
        {
            return gameWin;
        }

        //Handling Input and Setting States
        bool input(int _x, int _y, int op) //[bool return meant for success and failure]
        {
            Position p;
            p.x = _x ;
            p.y = _y ;

            if(op != 1 && op != 2)
            {
                std::cout<<"Wrong Operation!\n";
                return false;
            }
            if(p.x < 0 || p.x >9 || p.y <0 || p.y>9)
            {
                std::cout<<"Out of Bounds! Try again.\n";
                return false;
            }

            Operations operation = static_cast<Operations>(op-1);

            cellState currentState = board[p.x][p.y].getState();

            switch(currentState)
            {
                case cellState::opened: 
                    std::cout<<"Cell is already opened!\n";
                    return false;
                case cellState::marked:
                    if(operation == Operations::open)
                        openCell(p);
                    else
                        board[p.x][p.y].setState(cellState::hidden);
                    return true;
                case cellState::hidden:
                    if(operation == Operations::open)
                        openCell(p);
                    else
                        board[p.x][p.y].setState(cellState::marked);
                    return true;
            }
            return true;
        }

        //Displays the board 
        void boardDisplay()
        {
            std::cout<<"\n   0 1 2 3 4 5 6 7 8 9";
            
            for(int i=0; i<10; ++i)
            {
                std::cout<<"\n"<<i<<" |";
                for(int j=0; j<10; ++j)
                {
                    char ch = board[i][j].getDisplayChar();
                    std::string str(1, ch);
                    std::string colorString = std::to_string(board[i][j].getColor()); 
                    std::string outputString = "\033["+ colorString +"m"+ str + "\033[0m";
                    std::cout<<outputString<<"|";
                }
            }
        }
};

#endif