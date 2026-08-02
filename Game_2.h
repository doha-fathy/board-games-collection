#ifndef GAME_2_H
#define GAME_2_H

#include "boardgame_classes.h"
#include <vector>
#include <string>

class ConnectFourBoard : public Board<char> {
public:
    ConnectFourBoard();
    void display_board() override;
    bool update_board(int x, int y, char symbol) override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    const vector<vector<char>>& get_board() const;

private:
    vector<vector<char>> board;
};

class ConnectFourPlayer : public Player<char> {
public:
    ConnectFourPlayer(const string& name, char symbol);
    void getmove(int& x, int& y) override;
};

class ConnectFourAIPlayer : public Player<char> {
public:
    ConnectFourAIPlayer(char symbol, char opponentSymbol);

    void getmove(int& x, int& y) override;

private:
    char opponentSymbol;
    bool can_win(const ConnectFourBoard& board, int column, char symbol);
};

template <typename T>
class ConnectRandomPlayer : public RandomPlayer<T>{
public:
    ConnectRandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
ConnectRandomPlayer<T>::ConnectRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ConnectRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = 0;
}

//-------------------------

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


ConnectFourBoard::ConnectFourBoard() {
    rows = 6;
    columns = 7;
    n_moves = 0;
    board = vector<vector<char>>(rows, vector<char>(columns, ' '));
}

void ConnectFourBoard::display_board() {
    for (int r = rows - 1; r >= 0; --r) {
        for (int c = 0; c < columns; ++c) {
            cout << "| " << board[r][c] << " ";
        }
        cout << "|\n";
    }
    cout << "-----------------------------\n";
    cout << "  1   2   3   4   5   6   7\n";
}

bool ConnectFourBoard::update_board(int x, int y, char symbol) {
    if (x < 0 || x >= columns) {
        return false;
    }
    for (int r = 0; r < rows; ++r) {
        if (board[r][x] == ' ') {
            board[r][x] = symbol;
            n_moves++;
            return true;
        }
    }
    return false;
}

bool ConnectFourBoard::is_win() {
    // Check horizontal wins
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            char current = board[r][c];
            if (current != ' ' &&
                current == board[r][c + 1] &&
                current == board[r][c + 2] &&
                current == board[r][c + 3]) {
                return true;
            }
        }
    }

    // Check vertical wins
    for (int c = 0; c < columns; ++c) {
        for (int r = 0; r <= rows - 4; ++r) {
            char current = board[r][c];
            if (current != ' ' &&
                current == board[r + 1][c] &&
                current == board[r + 2][c] &&
                current == board[r + 3][c]) {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int r = 0; r <= rows - 4; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            char current = board[r][c];
            if (current != ' ' &&
                current == board[r + 1][c + 1] &&
                current == board[r + 2][c + 2] &&
                current == board[r + 3][c + 3]) {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int r = 3; r < rows; ++r) {
        for (int c = 0; c <= columns - 4; ++c) {
            char current = board[r][c];
            if (current != ' ' &&
                current == board[r - 1][c + 1] &&
                current == board[r - 2][c + 2] &&
                current == board[r - 3][c + 3]) {
                return true;
            }
        }
    }

    return false;
}

bool ConnectFourBoard::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool ConnectFourBoard::game_is_over() {
    return is_win() || is_draw();
}

const vector<vector<char>>& ConnectFourBoard::get_board() const {
    return board;
}

ConnectFourPlayer::ConnectFourPlayer(const string& name, char symbol) : Player<char>(name, symbol) {}

void ConnectFourPlayer::getmove(int& x, int& y) {
    cout << this->name << ", enter the column (1-7): ";
    cin >> x;
    x--;
    y = 0;
}


ConnectFourAIPlayer::ConnectFourAIPlayer(char symbol, char opponentSymbol)
    : Player<char>("AI", symbol), opponentSymbol(opponentSymbol) {}

void ConnectFourAIPlayer::getmove(int& x, int& y) {
    auto boardPtr = dynamic_cast<ConnectFourBoard*>(this->boardPtr);
    // Try to find a winning move
    for (int col = 0; col < 7; ++col) {
        if (can_win(*boardPtr, col, this->symbol)) {
            x = col;
            y = 0;
            return;
        }
    }
    // Try to block opponent's winning move
    for (int col = 0; col < 7; ++col) {
        if (can_win(*boardPtr, col, opponentSymbol)) {
            x = col;
            y = 0;
            return;
        }
    }
    // Otherwise, make a random move
    ConnectRandomPlayer<char> randomPlayer(this->symbol);
    randomPlayer.getmove(x, y);
}

bool ConnectFourAIPlayer::can_win(const ConnectFourBoard& board, int column, char symbol) {
    if (column < 0 || column >= 7) return false;

    auto tempBoard = board.get_board();
    for (int r = 0; r < 6; ++r) {
        if (tempBoard[r][column] == ' ') {
            tempBoard[r][column] = symbol;

            ConnectFourBoard tempBoard;
            tempBoard = board; // Copy original board
            tempBoard.update_board(column, 0, symbol); // Simulate move

            if (tempBoard.is_win()) {
                return true;
            }
            break;
        }
    }
    return false;
}
#endif //GAME_2_H
