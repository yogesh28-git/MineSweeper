#include <iostream>
#include <cstdlib>
#include "Board.h"

class Game
{
    private:
        Board b;
        bool inputSuccess = false;
        bool isGameOver = false;


        bool rulesMessage()
        {
            char input;
            std::cout<<"+-------------------------------------------+"<<std::endl;
            std::cout<<"|               MINESWEEPER                 |"<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl<<std::endl;
            std::cout<<std::endl;
            std::cout<<"RULES:"<<std::endl<<std::endl;
            std::cout<<"1. Board of 100 cells with 10 hidden mines"<<std::endl;
            std::cout<<"2. Player wins if they manage to open all the cells which do not contain mines"<<std::endl;
            std::cout<<"3. Player loses if a mine is opened"<<std::endl;
            std::cout<<std::endl;
            std::cout<<"HOW TO PLAY:"<<std::endl<<std::endl;
            std::cout<<"1. Player is to give x and y coordinate of the cell as first two inputs"<<std::endl;
            std::cout<<"2. The next input is to open or mark the cell"<<std::endl;
            std::cout<<"3. Numbers on the cells indicate the number of mines around the cell"<<std::endl;
            std::cout<<std::endl<<std::endl;
            std::cout<<"ARE YOU READY TO PLAY (Y/N):"<<std::endl;
            
            std::cin>>input;
            system("cls");
            if(input=='Y' || input=='y'){return true;}
            else {return false;}
        }
        void welcomeMessage()
        {
            std::cout<<std::endl<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl;
            std::cout<<"|                GAME STARTS                |"<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl<<std::endl;
            std::cout<<"WELCOME TO MINESWEEPER !!!"<<std::endl<<std::endl;
            std::cout<<"PRESS ENTER TO CONTINUE:"<<std::endl;
            std::cin.ignore();
            getchar();
            system("cls");
        }
        void gameWinMessage()
        {
            std::cout<<"+-------------------------------------------+"<<std::endl;
            std::cout<<"|           CONGRATULATIONS !!!             |"<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl<<std::endl;
            std::cin.ignore();
            getchar();
        }
        void gameOverMessage()
        {
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl;
            std::cout<<"|       OOPS! YOU STEPPED ON A MINE         |"<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl<<std::endl;
        }
        void endMessage()
        {
            std::cout<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl;
            std::cout<<"|                 GAME OVER                 |"<<std::endl;
            std::cout<<"|                 THANK YOU                 |"<<std::endl;
            std::cout<<"|              SEE YOU NEXT TIME            |"<<std::endl;
            std::cout<<"+-------------------------------------------+"<<std::endl;
            std::cin.ignore();
            getchar();
        }

    public:
        void play()
        {
            if(!rulesMessage())
            {        
                endMessage();
                return;
            }
            welcomeMessage();
            
            int x,y,op;
            b.boardDisplay();
            do
            {
                do
                {
                    std::cout<<"\n\nEnter x: ";
                    std::cin>>x;
                    std::cout<<"Enter y: ";
                    std::cin>>y;
                    std::cout<<"Choose Operation: \n";
                    std::cout<<"Press 1 - Open \n";
                    std::cout<<"Press 2 - Mark/Unmark \n";
                    std::cin>>op;
                    inputSuccess = b.input(x,y,op);
                    
                }while(!inputSuccess);
                
                if(b.getGameOver())
                {
                    gameOverMessage();
                    endMessage();
                    return;
                }
                else
                {
                    system("cls");
                    b.boardDisplay();
                }
                
            }while(!b.getGameWin());

            gameWinMessage();
            return;
        }

};