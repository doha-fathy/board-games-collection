#ifndef GAME_8_H
#define GAME_8_H

#include "BoardGame_Classes.h"
#include "X_O.h"

template <typename T>
class UltimateBoard:public Board<T> {
protected:
    vector<vector<X_O_Board<T>*>> boards;
public:
    UltimateBoard();
    bool update_board(int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    ~UltimateBoard();

};

template <typename T>
class UltimatePlayer : public Player<T> {
public:
    UltimatePlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class U_RandomPlayer : public RandomPlayer<T>{
public:
    U_RandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <cctype>

template <typename T>
UltimateBoard<T>::UltimateBoard() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;

    for(int i=0; i < 3; i++) {
        std::vector<X_O_Board<T>*> row;
        for(int j=0; j < 3; j++) {
            row.push_back(new X_O_Board<T>());
        }
        boards.push_back(row);
    }

}
template <typename T>
UltimateBoard<T>::~UltimateBoard() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            delete boards[i][j];
        }
    }
    boards.clear();
}

template <typename T>
bool UltimateBoard<T>::update_board(int x, int y, T symbol) {
    if(x < 0 || x > 8 || y < 0 || y > 8) {
        return false;
    }
    int board_x = x / 3;
    int board_y = y / 3;

    // Check if the move is allowed: either the sub-board is not already won, or it is allowed for reuse
    if (boards[board_x][board_y]->is_win()) {
        return false; // Disallow moves on won boards
    }

    if(boards[board_x][board_y]->update_board(x%3, y%3, symbol)) {
        if(boards[board_x][board_y]->is_win()) {
            this->board[board_x][board_y] = symbol;
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void UltimateBoard<T>::display_board() {
    cout << "\nUltimate Tic-Tac-Toe Board:\n\n";

    cout << "   "; // Indent for row numbers
    for (int col = 1; col <= 9; ++col) {
        cout << col << "   ";
        if (col % 3 == 0) cout << "  "; // Extra space after every third column for separation
    }
    cout << "\n";

    for (int big_row = 0; big_row < 3; ++big_row) { // Big board rows
        for (int small_row = 0; small_row < 3; ++small_row) { // Small board rows
            cout << (big_row * 3 + small_row + 1) << " ";
            for (int big_col = 0; big_col < 3; ++big_col) { // Big board columns
                for (int small_col = 0; small_col < 3; ++small_col) { // Small board columns
                    // Display cell content or placeholder
                    if (boards[big_row][big_col]->getBoard()[small_row][small_col] == ' ')
                        cout << " . ";
                    else
                        cout << " " << boards[big_row][big_col]->getBoard()[small_row][small_col] << " ";

                    if (small_col < 2) cout << "|"; // Add column separators within small boards
                }
                cout << "   "; // Separate small boards horizontally
            }
            cout << "\n  "; // Move to the next small board row

            // Print row separators within each small board
            if (small_row < 2) {
                for (int big_col = 0; big_col < 3; ++big_col) {
                    cout << "---+---+---   "; // Separator for small board rows
                }
                cout << "\n";
            }
        }
        cout << "\n"; // Move to the next big board row
    }
}


// Returns true if there is any winner
template <typename T>
bool UltimateBoard<T>::is_win(){
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
        return true;
    }

    return false;
}


template <typename T>
bool UltimateBoard<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool UltimateBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------


template <typename T>
UltimatePlayer<T>::UltimatePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void UltimatePlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y ex (11): ";
    cin >> x;
    y = x % 10;
    x /= 10;
    x--;
    y--;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        std::cout<< "\nInvalid input! Please enter a valid move\n";
    }
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
U_RandomPlayer<T>::U_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void U_RandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif
