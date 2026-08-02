#ifndef GAME_7_H
#define GAME_7_H
#include "BoardGame_Classes.h"

template <typename T>
class Game_7_Board:public Board<T> {
public:
     Game_7_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    static bool turn;
    static int x;
    static int y;
    static int counter;


};

template <typename T>
class  Game_7_Player : public Player<T> {
protected:
    T mark;
public:
     Game_7_Player (string name, T symbol);
    void getmove(int& x, int& y) ;


};

template <typename T>
class  Game_7_Random_Player : public RandomPlayer<T>{
public:
     Game_7_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Constructor for X_O_Board
template <typename T>
 Game_7_Board<T>:: Game_7_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->board[0][0]=this->board[0][2]=this->board[3][1]=this->board[3][3]='O';
    this->board[0][1]=this->board[0][3]=this->board[3][0]=this->board[3][2]='X';


    this->n_moves = 0;
}

template <typename T>
bool  Game_7_Board<T>::update_board(int x, int y, T mark) {

    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == mark& & mark != 0) {

            while(true) {
                int i, j;
                if(counter==1) {
                    cout << "\nPlease enter your  i and j for token (0 to 3) separated by space: ";
                    cin >> i >> j;

                }

                if(counter==2) {
                    i = rand() % this->rows;  // Random number between 0 and 3
                    j = rand() % this->columns;


                }
                if(i >= 0 && i < this->rows && j >= 0 && j < this->columns && this->board[i][j] == 0 & & mark != 0
                  && this->board[x][y]==toupper(mark) &&((i==x-1 && y==j)  ||  (i==x+1 && y==j ) || (i==x && y==j-1)  ||  (i==x && y==j+1 ))){
                    this->board[x][y]=0;
                    this->board[i][j]=toupper(mark);
                    turn =true;
                    return true;

                     }
                return false;


            }



    }



    return false;
}

// Display the board and the pieces on it
template <typename T>
void  Game_7_Board<T>::display_board() {
    cout <<"    0    1    2    3";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n"<<i <<" |";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << this->board[i][j] << " |";
        }
        cout << "\n  ---------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool  Game_7_Board<T>::is_win() {
    // Check rows and columns
    int j=0;
    while(j!=this->rows-2) {
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0 )||
                 (this->board[j][i] == this->board[j+1][i] && this->board[j+1][i] == this->board[j+2][i] && this->board[j][i] != 0)) {
                return true;

            }
        }j++;
    }

    // Check diagonals
    for (int i = 0; i < this->rows-2; i++) {
        if (this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i][j] != 0 ) {
            return true;
        }

    }


    if ((this->board[0][1] == this->board[1][2] && this->board[1][2] == this->board[2][3] && this->board[0][1] != 0)||
         (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)||
         (this->board[1][3] == this->board[2][2] && this->board[2][2] == this->board[3][1] && this->board[1][3] != 0)||
         (this->board[1][0] == this->board[2][1] && this->board[2][1] == this->board[3][2] && this->board[1][0] != 0)||
        (this->board[0][3] == this->board[1][2] && this->board[1][2] == this->board[2][1] && this->board[0][3] != 0)||
        (this->board[3][0] == this->board[2][1] && this->board[2][1] == this->board[1][2] && this->board[3][0] != 0)
        ) {
        return true;
    }



    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Game_7_Board<T>::is_draw() {
    return  false;
}

template <typename T>
bool  Game_7_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
 Game_7_Player<T>:: Game_7_Player(string name, T symbol) : Player<T>(name, symbol) {
}

template <typename T>
void  Game_7_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your  x and y for token (0 to 3) separated by space: ";
    cin >> x >> y;
    Game_7_Board<T>::counter=1;

}

// Constructor for X_O_Random_Player
template <typename T>
 Game_7_Random_Player<T>:: Game_7_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void  Game_7_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    Game_7_Board<T>::counter=2;


}


template <typename T>
bool Game_7_Board<T>::turn = false;
template <typename T>

int Game_7_Board<T>::x = 0;
template <typename T>

int Game_7_Board<T>::y = 0;

template <typename T>
int Game_7_Board<T>::counter = 0;


#endif //GAME_7_H
