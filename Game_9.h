#ifndef GAME_9_H
#define GAME_9_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Class representing the board for the "SUS" game
class SUSBoard : public Board<char> {
public:
    //Constructor to initialize a SUSBoard with the given dimensions
    SUSBoard(int r = 3, int c = 3);
    //Destructor to clean up dynamically allocated memory for the board
    ~SUSBoard();
    // Updates the board at the specified position with the given symbol
    // return True if the move is valid and applied, otherwise false
    bool update_board(int x, int y, char symbol) override;

    // Displays the current state of the board to the console.
    void display_board() override;
    bool is_win() override;
    //Checks if the game is a draw.
    //A draw occurs if all moves are made and the counts of "SUS" patterns for 'S' and 'U' are equal
    bool is_draw() override;
    // Checks if the game is over (either draw or all moves used).
    // return True if the game is over, otherwise false
    bool game_is_over() override;

    // Counts the number of "SUS" patterns formed with the given symbol.
    // A "SUS" pattern consists of the sequence (symbol, 'U', symbol) along a row, column, or diagonal
    // return Number of "SUS" patterns found
    int count_sus(char symbol);

private:

    // Helper function to check if a specific line forms a "SUS" pattern
    // parameter x1, y1 Starting cell coordinates
    // parameter x2, y2 Ending cell coordinates
    // parameter symbol Character to check for
    // return True if the line forms a "SUS" pattern, otherwise false
    bool check_line(int x1, int y1, int x2, int y2, char symbol);
};

// Class representing a human player for the "SUS" game
class SUSPlayer : public Player<char> {
public:
    // Constructor to initialize a SUSPlayer
    SUSPlayer(string name, char symbol);
    void getmove(int& x, int& y) override;
};

// Class representing a random player for the "SUS" game
class SUSRandomPlayer : public RandomPlayer<char> {
public:
    // Constructor to initialize a SUSRandomPlayer
    SUSRandomPlayer(string name, char symbol);

    // Generates a random move for the player
    void getmove(int& x, int& y) override;
};

//--------------------------------------- IMPLEMENTATION

#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

SUSBoard::SUSBoard(int r, int c) {
    rows = r;
    columns = c;
    board = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];
        fill(board[i], board[i] + columns, ' ');
    }
}

SUSBoard::~SUSBoard() {
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

bool SUSBoard::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == ' ') {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    return false;
}

void SUSBoard::display_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == ' ') {
                cout << " . ";
            } else {
                cout << " " << board[i][j] << " ";
            }
            if (j < columns - 1) {
                cout << "|";
            }
        }
        cout << "\n";
        if (i < rows - 1) {
            cout << "---+---+---\n";
        }
    }
    cout << "\n";
}

bool SUSBoard::check_line(int x1, int y1, int x2, int y2, char symbol) {
    int dx = (x2 - x1) / 2;
    int dy = (y2 - y1) / 2;
    return (board[x1][y1] == symbol && board[x1 + dx][y1 + dy] == 'U' && board[x2][y2] == symbol);
}

int SUSBoard::count_sus(char symbol) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        if (check_line(i, 0, i, 2, symbol)) {
            count++;
        }
    }
    for (int j = 0; j < columns; ++j) {
        if (check_line(0, j, 2, j, symbol)) {
            count++;
        }
    }
    if (check_line(0, 0, 2, 2, symbol)) {
        count++;
    }
    if (check_line(0, 2, 2, 0, symbol)) {
        count++;
    }
    return count;
}

bool SUSBoard::is_win() {
    return false;
}

bool SUSBoard::is_draw() {
    return (n_moves == rows * columns) && (count_sus('S') == count_sus('U'));
}

bool SUSBoard::game_is_over() {
    return is_draw() || (n_moves == rows * columns);
}

SUSPlayer::SUSPlayer(string name, char symbol) : Player(name, symbol) {}

void SUSPlayer::getmove(int& x, int& y) {
    cout << name << " (" << symbol << ") enter row and column: ";
    cin >> x >> y;
    x--;
    y--;
    cout << '\n';
}

SUSRandomPlayer::SUSRandomPlayer(string name, char symbol)
    : RandomPlayer<char>(symbol) {
    this->name = "Random Player";
}

void SUSRandomPlayer::getmove(int& x, int& y) {
    srand(static_cast<unsigned int>(time(0)));
    x = rand() % 3;
    y = rand() % 3;
}

#endif // GAME_9_H