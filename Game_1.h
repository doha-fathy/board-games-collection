#ifndef GAME_1_H
#define GAME_1_H

#include <iomanip>
#include <limits>

#include "BoardGame_Classes.h"

template <typename T>
class PyramidBoard:public Board<T> {
public:
    PyramidBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class P_RandomPlayer : public RandomPlayer<T>{
public:
    P_RandomPlayer (T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
class AI_Player : public Player<T>{
public:
    AI_Player (T symbol, Board<T>* b);
    void getmove(int &x, int &y) ;
    ~AI_Player();
};

//--------------------------implementation

template<typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}


template<typename T>
bool PyramidBoard<T>::update_board (int x , int y , T symbol) {
    if(x < 0 || y < 0 || x > 2 || y > 4 || (x+y < 2) || (x+y > (x+1)*2) || (this->board[x][y] != ' ' && symbol != ' ')) {
        return false;
    }
    if(symbol == ' ') {
        this->n_moves--;
    }else {
        this->n_moves++;
    }

    this->board[x][y] = symbol;
    return true;
}

template<typename T>
void PyramidBoard<T>::display_board () {
    std::cout << "\n-- Pyramid Board --\n\n";
    int start = 2, end = 3;
    for(int i =0 ; i < 3; i++){
        std::cout << std::setw(start*4+2) << "| ";
        for(int j = start ; j < end ; j++){
            if(this->board[i][j] == ' ') {
                std::cout << (i+1)*10 + (j+1) << "| ";
            }else {
                std::cout << this->board[i][j] << " | ";
            }
        }
        std::cout <<"\n";
        start--;
        end++;
    }

}

template<typename T>
bool PyramidBoard<T>::is_win() {
    for(int i = 0; i < 3 ; i++){
        if(this-> board[2][i] != ' ' && this->board[2][i] == this->board[2][i+1] && this->board[2][i+1] == this->board[2][i+2]){
            return true;
        }
    }
    if (this->board[0][2] != ' ' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] ||
        this->board[0][2] != ' ' && this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] ||
        this->board[0][2] != ' ' && this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] ||
        this->board[1][1] != ' ' && this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] ) {
        return true;
    }

    return false;
}

template<typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();

}

template <typename T>
HumanPlayer<T>::HumanPlayer (std::string name, T symbol) : Player<T>(name, symbol) {

}
template <typename T>
void HumanPlayer<T>::getmove(int& x, int& y) {
    std::cout << "\nPlease enter your move x , y ex (13): ";
    std::cin >> x;
    y = x % 10;
    x /= 10;
    y--;
    x--;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        std::cout<< "\n*Invalid input! Please enter a valid move*\n";
    }
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
P_RandomPlayer<T>::P_RandomPlayer (T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
    this->name = "computer";
}
template<typename T>
void P_RandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % 3;
    y = rand() % 5;
}
// AI_Player
template<typename T>
AI_Player<T>::AI_Player(T symbol, Board<T>* b)
    : Player<T>("AI",symbol) {
    this->setBoard(b);
}
template<typename T>
AI_Player<T>::~AI_Player() {
    //delete this->boardPtr;
}

template<typename T>
bool check_win(Board<T>* check_board, T symbol, int& x, int& y) {
    for(int i = 0; i < 3; i++) { // row
        for(int j = 0; j < 5; j++) {
            if(check_board->update_board(i, j, symbol)) {
                if(check_board->is_win()) {
                    x = i;
                    y = j;
                    check_board->update_board(i, j, ' ');
                    return true;
                }else {
                    check_board->update_board(i, j, ' '); // remove update
                }
            }
        }
    }
    return false;
}

template<typename T>
void AI_Player<T>::getmove(int &x, int &y) {
    T other_symbol = (this->symbol == 'X') ? 'O' : 'X';

    // if there option make me win then make it
    // if there option can make other player win make it
    if(check_win(this->boardPtr, this->symbol, x, y)) {
        return;
    }

    if(check_win(this->boardPtr, other_symbol, x, y)) {
        return;
    }

    // Third priority: Strategic moves (e.g., corners or center)
    if (this->boardPtr->update_board(2, 2, this->symbol)) {
        x = 2; y = 2;
    }else if (this->boardPtr->update_board(0, 2, this->symbol)) {
        x = 0; y = 2;
    }else if ((x == 0 && y == 2) && this->boardPtr->update_board(2, 3, this->symbol)) {
        x = 2; y = 3;
    }else if (!(x == 1 && y == 1)&&this->boardPtr->update_board(2, 0, this->symbol)) {
        x = 2; y = 0;
    }else if (this->boardPtr->update_board(2, 4, this->symbol)) {
        x = 2; y = 4;
    }else do {
        x = rand() % 3;
        y = rand() % 5;
    }while(this->boardPtr->update_board(x, y, this->symbol));

    this->boardPtr->update_board(x, y, ' ');
    std::cout << "\nAI chose " << x+1 <<y+1 << "\n";

}

#endif //GAME_1_H
