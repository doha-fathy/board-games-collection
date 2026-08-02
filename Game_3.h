

#ifndef GAME_3_H
#define GAME_3_H

#include "BoardGame_Classes.h"

template <typename T>
class Game_3_Board:public Board<T> {
public:
    Game_3_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    static int player_1;
    static int player_2;
    static string name_X;
    static string name_O;
    static  bool check;
    static  bool check2;




    void counting(int i, int j);


};

template <typename T>
class Game_3_Player : public Player<T> {
public:
    Game_3_Player (string name, T symbol);
    void getmove(int& x, int& y) ;


};

template <typename T>
class Game_3_Random_Player : public RandomPlayer<T>{
public:
   Game_3_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Game_3_Board<T>::Game_3_Board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Game_3_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if(check==false) {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
            if (mark == 0) {
                this->n_moves--;
                this->board[x][y] = 0;
            } else {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
            }
            return true;
        }

        return false;
    }

    return true;


}

// Display the board and the pieces on it
template <typename T>
void Game_3_Board<T>::display_board() {
    if(check==false) {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n---------------------------------------------";
        }
    }
    cout<<endl;

}

// Returns true if there is any winner
template <typename T>
bool Game_3_Board<T>::is_win() {
    // Check rows and columns
    if( check==true && check2==true) {
        if(player_1 !=player_2) {
            cout<<player_1<<" "<<player_2<<endl;
            return true;
        }

    }
   if(this->n_moves==24) {
        int j=0;
        while(j!=this->rows-2) {
            for (int i = 0; i < this->rows; i++) {
                if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != 0) {
                    counting(i,j);
                }
                else if (this->board[j][i] == this->board[j+1][i] && this->board[j+1][i] == this->board[j+2][i] && this->board[j][i] != 0) {
                    counting(j,i);
                }
            }j++;
        }

        // Check diagonals
        for(int i=0;i<this->rows-2;i++) {
            if (this->board[i][i] == this->board[i+1][i+1] && this->board[i+1][i+1] == this->board[i+2][i+2] && this->board[i][i] != 0) {
                counting(i,i);
            }

        }
        int k=0;
        for(int i=this->rows-1;i>=2;--i) {
            if (this->board[k][i] == this->board[k+1][i-1] && this->board[k+1][i-1] == this->board[k+2][i-2] && this->board[k][i] != 0) {
                counting(k,i);
            }
            k++;

        }

        for(int i=0;i<this->rows-3;i++) {
            if (this->board[i][i+1] == this->board[i+1][i+2] && this->board[i+1][i+2] == this->board[i+2][i+3] && this->board[i][i+1] != 0) {
                counting(i,i+1);
            }
            if (this->board[i+1][i] == this->board[i+2][i+1] && this->board[i+2][i+1] == this->board[i+3][i+2] && this->board[i+1][i] != 0) {
                counting(i+1,i);
            }
        }
        for(int i=0;i<this->rows-3;i++) {
            if (this->board[i][i+3] == this->board[i+1][i+2] && this->board[i+1][i+2] == this->board[i+2][i+1] && this->board[i][i+3] != 0) {
                counting(i,i+3);
            }
        }

        for(int i=1;i<this->rows-2;i++) {
            if (this->board[i][i+1] == this->board[i+1][i] && this->board[i+1][i] == this->board[i+2][i-1] && this->board[i][i+1] != 0) {
                counting(i,i+1);
            }
        }

        if (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != 0) {
            counting(0,2);

        }
        if (this->board[2][0] == this->board[3][1] && this->board[3][1] == this->board[4][2] && this->board[2][0] != 0) {
            counting(2,0);

        }
        if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) {
            counting(0,2);

        }
        if (this->board[2][4] == this->board[3][3] && this->board[3][3] == this->board[4][2] && this->board[2][4] != 0) {
            counting(2,4);

        }
       check= true;;
    }

    return false;


}

// Return true if  moves are done and no winner
template <typename T>
bool Game_3_Board<T>::is_draw() {
    if(player_1 ==player_2 && this->n_moves==24) {
        return  true;
    }
    return false;
}

template <typename T>
bool Game_3_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Game_3_Player<T>::Game_3_Player(string name, T symbol) : Player<T>(name, symbol) {
    if(symbol=='X') {
       Game_3_Board<T>::name_X=name;
}
    if(symbol=='O') {
        Game_3_Board<T>::name_O=name;



    }
}

template <typename T>
void Game_3_Player<T>::getmove(int& x, int& y) {
    if(Game_3_Board<T>::check==true && Game_3_Board<T>::check2==false  ) {
        if(Game_3_Board<T>::player_1>Game_3_Board<T>::player_2) {
            this->name=Game_3_Board<T>::name_X;
            Game_3_Board<T>::check2=true;


        }
        else if(Game_3_Board<T>::player_2>Game_3_Board<T>::player_1) {
            this->name=Game_3_Board<T>::name_O;
            Game_3_Board<T>::check2=true;


        }
    }

    if(Game_3_Board<T>::check==false && Game_3_Board<T>::check2==false  ) {
            cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
            cin >> x >> y;
        }
    }




// Constructor for X_O_Random_Player
template <typename T>
Game_3_Random_Player<T>::Game_3_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Game_3_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template <typename T>
int Game_3_Board<T>::player_1 = 0;
template <typename T>
int Game_3_Board<T>::player_2 = 0;
template <typename T>
string Game_3_Board<T>::name_X = "";
template <typename T>
string Game_3_Board<T>::name_O ="";

template <typename T>
bool  Game_3_Board<T>::check =false;
template <typename T>
bool  Game_3_Board<T>::check2 =false;
template <typename T>

void Game_3_Board<T>:: counting(int i, int j) {
    if(this->board[i][j]=='X') {
        player_1++;
    }
    else if(this->board[i][j]=='O'){
        player_2++;
    }
}




#endif GAME_3_H
