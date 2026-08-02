#ifndef GAME_5_H
#define GAME_5_H

#include "boardGame_classes.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Represents the board for Numerical Tic Tac Toe
template <typename T>
class NumericalBoard : public Board<T> {
private:
    vector<vector<T>> board; // 3x3 game board

public:
    NumericalBoard();
    void display_board() override; // Displays the current state of the board
    bool update_board(int x, int y, T symbol) override; // Updates the board with a player's move
    bool is_win() override; // Checks if a player has won
    bool is_draw() override; // Checks if the game is a draw
    bool game_is_over() override; // Checks if the game is over (win or draw)
};

// Represents a player in Numerical Tic Tac Toe
template <typename T>
class NumericalPlayer : public Player<T> {
private:
    bool is_odd_choice; // Indicates if the player can use odd numbers only

public:
    NumericalPlayer(const string& player_name, T player_symbol, bool odd_choice);
    void getmove(int& x, int& y, T& symbol, NumericalBoard<T>& board) const; // Prompts the player for a move
    void getmove(int& x, int& y) override; // Overrides base class method to prompt for a move
};

// Represents a random player
template <typename T>
class NumericalRandomPlayer : public RandomPlayer<T> {
private:
    vector<T> available_numbers; // Numbers the player can use
    vector<T> used_numbers; // Numbers already used during the game

public:
    NumericalRandomPlayer(T symbol, const vector<T>& numbers);
    void getmove(int& x, int& y, T& symbol, NumericalBoard<T>& board); // Generates a random move
    void getmove(int& x, int& y) override; // Overrides base class method to generate a move
};


//--------------------------------------- IMPLEMENTATION


// Delegates to the full version of 'getmove'
template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
    T symbol;
    NumericalBoard<T> board;
    getmove(x, y, symbol, board);
}

// Constructor for the random player with a list of available numbers
template <typename T>
NumericalRandomPlayer<T>::NumericalRandomPlayer(T symbol, const vector<T>& numbers)
    : RandomPlayer<T>(symbol), available_numbers(numbers) {
    this->name = "Random Player";
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
}

// Generates a random move for the random player
template <typename T>
void NumericalRandomPlayer<T>::getmove(int& x, int& y, T& symbol, NumericalBoard<T>& board) {
    vector<T> valid_numbers;
    for (T num : available_numbers) {
        if (find(used_numbers.begin(), used_numbers.end(), num) == used_numbers.end()) {
            valid_numbers.push_back(num);
        }
    }
    symbol = valid_numbers[rand() % valid_numbers.size()]; // Choose a random valid number
    const_cast<char&>(this->symbol) = symbol;
    used_numbers.push_back(symbol); // Mark it as used

    // Find a random empty cell
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board.update_board(x, y, symbol) == false);
}

// Delegates to the full version of 'getmove'
template <typename T>
void NumericalRandomPlayer<T>::getmove(int& x, int& y) {
    T symbol;
    NumericalBoard<T> board;
    getmove(x, y, symbol, board);
}

// NumericalBoard Constructor: Initializes a 3x3 board with empty values
template <typename T>
NumericalBoard<T>::NumericalBoard() {
    this->rows = 3;
    this->columns = 3;
    this->n_moves = 0;
    board = vector<vector<T>>(this->rows, vector<T>(this->columns, T()));
}

// Displays the board, with empty cells shown as '.'
template <typename T>
void NumericalBoard<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (board[i][j] == T()) {
                cout << " . ";
            } else {
                cout << " " << board[i][j] << " ";
            }
            if (j < this->columns - 1) {
                cout << "|";
            }
        }
        cout << endl;
        if (i < this->rows - 1) {
            cout << "---+---+---\n";
        }
    }
    cout << '\n';
}

// Updates the board with a symbol at the specified coordinates (x, y)
template <typename T>
bool NumericalBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false; // Invalid move (out of bounds)
    }
    if (board[x][y] != T()) {
        return false; // Invalid move (cell already occupied)
    }
    board[x][y] = symbol;
    this->n_moves++;
    return true;
}

// Checks for a win by summing rows, columns, or diagonals to see if any sum equals 15
template <typename T>
bool NumericalBoard<T>::is_win() {
    auto numeric_sum = [](T a, T b, T c) {
        return (a - '0') + (b - '0') + (c - '0'); // Convert characters to integers and sum them
    };

    // Check rows
    for (int i = 0; i < this->rows; ++i) {
        if (board[i][0] != T() && board[i][1] != T() && board[i][2] != T() &&
            numeric_sum(board[i][0], board[i][1], board[i][2]) == 15) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < this->columns; ++i) {
        if (board[0][i] != T() && board[1][i] != T() && board[2][i] != T() &&
            numeric_sum(board[0][i], board[1][i], board[2][i]) == 15) {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] != T() && board[1][1] != T() && board[2][2] != T() &&
        numeric_sum(board[0][0], board[1][1], board[2][2]) == 15) {
        return true;
    }

    if (board[0][2] != T() && board[1][1] != T() && board[2][0] != T() &&
        numeric_sum(board[0][2], board[1][1], board[2][0]) == 15) {
        return true;
    }

    return false; // No winning condition found
}

// Checks if the game is a draw (all cells are filled with no winner)
template <typename T>
bool NumericalBoard<T>::is_draw() {
    return game_is_over() && !is_win();
}

// Checks if the game is over (either a win or the board is full)
template <typename T>
bool NumericalBoard<T>::game_is_over() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (board[i][j] == T()) {
                return false; // Game is not over (empty cells remain)
            }
        }
    }
    return true;
}

// NumericalPlayer Constructor: Initializes a player with a name, symbol, and odd/even choice
template <typename T>
NumericalPlayer<T>::NumericalPlayer(const string& player_name, T player_symbol, bool odd_choice)
    : Player<T>(player_name, player_symbol), is_odd_choice(odd_choice) {}

// Prompts the player for a move and validates the input
template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y, T& symbol, NumericalBoard<T>& board) const {
    static vector<T> used_numbers; // Track numbers already used

    vector<T> available_numbers = is_odd_choice ? vector<T>{'1', '3', '5', '7', '9'} : vector<T>{'2', '4', '6', '8'};
    bool valid_move = false;

    while (!valid_move) {
        cout << '\n' << this->name << ", enter row and column: ";
        cin >> x >> y;
        x--; // Convert to 0-based index
        y--;

        while (true) {
            cout << this->name << ", enter your number: ";
            cin >> symbol;
            cout << '\n';

            if (!isdigit(symbol) || int(symbol) < '1' || int(symbol) > '9') {
                cout << "\n*Invalid input: Number must be between 1 and 9.*\n";
                continue;
            }
            if (find(available_numbers.begin(), available_numbers.end(), symbol) == available_numbers.end()) {
                cout << "\n*Invalid input: Choose an odd or even number based on your choice.*\n";
                continue;
            }
            if (find(used_numbers.begin(), used_numbers.end(), symbol) != used_numbers.end()) {
                cout << "\n*Invalid input: Number already used.*\n";
                continue;
            }
            break;
        }
        const_cast<char&>(this->symbol) = symbol;
        if (board.update_board(x, y, symbol)) {
            used_numbers.push_back(symbol); // Mark the number as used
            valid_move = true; // Valid move applied
        } else {
            cout << "\n*Invalid move: Cell already occupied. Try again.*\n";
        }
    }
}

#endif // GAME_5_H