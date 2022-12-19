#include<iostream>
#include <conio.h>    //for input()
#include <windows.h>    //Sleep()

using namespace std;

bool gameOver;
const int width = 30;       //cannot be left un-initialized, cannot be assigned value anywhere in the program
const int height = 30;
int x, y, fruitX, fruitY, score;         //x, y = head position, fruitX, fruitY = fruit position

int tailX[100], tailY[100];    //x and y coordinate of tail
int nTail;    //length of the tail

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};      //we want the variable dir to select any one from the set of values
eDirection dir;


void setup()
{
    gameOver = false;
    dir = STOP;      //the snake will not move until we start the game
    x = width/2;     //snake head will be at the center of the map
    y = height/2;
    fruitX = rand() % width;     //random number between 0 to width-1  ---> for fruit position
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
    system("cls");         //clear the screen/terminal
    for( int i = 0; i<width+2; i++)     //to display the top border of our map
    {
        cout<<"#";
    }
    cout<<endl;

    for (int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            if ( j== 0)             //left wall print
                cout<<"#"; 

            if ( i == y && j == x)      //head 
                cout<<"0";   

            else if(i == fruitY && j == fruitX)      //fruit
                cout<<"F";  

            else
            {
                bool print = false;       //
                for( int k =0; k < nTail; k++)       //to print the tail
                {
                    if(tailX[k] == j && tailY[k] == i)    // if the tailX[k] = current x coordinate and tailY[k] = current y coordinate  -----> print
                    {
                        cout<<"o";
                        print = true;      //
                    }
                }
                if ( !print)             //to print space
                    cout<<" ";
            }
            
            if( j == width-1)           ///right wall print
            {
                cout<<"#";
            }
        }
        cout<<endl;
    }

    for( int i = 0; i<width+2; i++)     //to display the bottom border of our map
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"Score : "<<score<<endl;
}

void input()    //handle controls
{
    //functions from conio.h
    //function for getting a character from a console window
    
    if(_kbhit())  //return +ve no. if character on keyboard is pressed and returns 0 if nothing is pressed
    {
        switch(_getch())     //read character input from keyboard
        {
            case 'y':
                dir = UP;
                break;
            case 'l':
                dir = RIGHT;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'b':
                dir = DOWN;
                break;
            case 'x':
                gameOver =  true;
                break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];    //storing the prev x coordinate of tail
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;         //tail to follow our head
    tailY[0] = y;

    for(int i = 1; i<nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case UP:
        y--;
        break;

    case RIGHT:
        x++;    //increase x coordinate of the snake
        break;
    
    case LEFT:
        x--;     //decrease x coordinate of the snake
        break;

    case DOWN:
        y++;
        break;
    
    default:
        break;
    }
    //if (x > width || x<0 || y > height || y<0)     //gameover if head touches the wall
        //gameOver = true;

    if (x>=width)         //to pass the head through the wall
        x = 0; 
    else if (x<0)
        x = width -1;        

    if (y>=height)
        y = 0; 
    else if (y<0)
        y = height -1;

    for(int i = 0; i<nTail; i++)
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY){      //if head reaches fruit, score is inc by 1
        score += 10;
        fruitX = rand() % width;        //after that, a new fruit is placed
        fruitY = rand() % height;
        nTail++;           //inc tail by 1 segment
    }
}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(500);     //slow down the game
    }
    return 0;
}