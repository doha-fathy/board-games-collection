
#ifndef X_O_H
#define X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    T** getBoard() const;
    bool is_win() ;
    void display_board ();
    bool is_draw() ;
    bool game_is_over();

};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
T** X_O_Board<T>::getBoard() const{
    return this->board;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] != ' ' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) ||
            (this->board[0][i] != ' ' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i])) {
            return true;
            }
    }

    // Check diagonals
    if ((this->board[0][0] != ' ' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]) ||
        (this->board[0][2] != ' ' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0])) {
        return true;
        }

    return false;
}

template <typename T>
void X_O_Board<T>::display_board () {

}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

#endif //X_O_H

