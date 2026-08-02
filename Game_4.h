#ifndef GAME_4_H
#define GAME_4_H

#include <fstream>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>

#include "BoardGame_Classes.h"

template <typename T>
class WordBoard:public Board<T> {
public:
    WordBoard ();
    bool update_board (int x , int y , T symbol) override;
    void display_board () override;
    bool is_win() override;
    bool is_draw()override;
    bool game_is_over() override;
};

template <typename T>
class WordPlayer : public Player<T> {
public:
    WordPlayer(std::string name, T symbol = ' ');
    void getmove(int& x, int& y) override;

};

template <typename T>
class W_RandomPlayer : public RandomPlayer<T>{
public:
    W_RandomPlayer();
    void getmove(int &x, int &y) ;
};
//---------------implementation

#include "game_4.h"

template<typename T>
WordBoard<T>::WordBoard() {
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

template<typename T>
bool WordBoard<T>::update_board (int x , int y , T symbol) {
    if(x < 0 || y < 0 || x > 2 || y > 2  || (this->board[x][y] != ' ' && symbol != ' ') || !std::isalpha(symbol)) {
        return false;
    }
    if(symbol == ' ') {
        this->n_moves--;
    }else {
        this->n_moves++;
    }

    this->board[x][y] = toupper(symbol);
    return true;
}

template<typename T>
void WordBoard<T>::display_board () {
    std::cout << "\n-- Board --\n\n";
    for(int i =0 ; i < 3; i++){
        for(int j = 0 ; j < 3 ; j++){
            if(this->board[i][j] == ' ') {
                std::cout << " . ";
            }else {
                std::cout << ' ' << this->board[i][j] << ' ';
            }
            if(j < 2) {
                std::cout << '|';
            }
        }
        std::cout <<"\n";
        if(i<2) {
            std::cout <<"---+---+---\n";
        }

    }
}
//search from file
bool search(std::string words, int start){
    ifstream file("dic.txt", std::ios::in);
    if(!file.is_open()) {
        std::cout << "\nPlease check if file 'dic.txt' in the same direction of the code. then try again\n";
        return false;
    }
    std::string currentWord;
    file.seekg (start, std::ios::beg);
    for(int i = 0 ; file >> currentWord;i++) {
        if(currentWord == words) {
            return true;
        }
    }
    return false;
}
bool is_word(string word) {
    std::string reword = word;
    std::reverse(reword.begin(), reword.end());

    // Calculate start positions
    int start1 = (word[0]-'A') * 38;
    int start2 = (reword[0]-'A') * 38;
    
    return search(word, start1) || search(reword, start2);
}

template<typename T>
bool WordBoard<T>::is_win() {
    std::string word1, word2;
    for (int i = 0; i < this->rows; i++) {
        word1 = std::string()+this->board[i][0] + this->board[i][1] + this->board[i][2];
        word2 = std::string()+this->board[i][2] + this->board[i][0] + this->board[i][1];

        if ((this->board[i][0] != ' ' && this->board[i][1] != ' ' && this->board[i][2] != ' ' && is_word(word1) ) ||
            (this->board[0][i] != ' ' && this->board[1][i] != ' ' && this->board[2][i] != ' ' && is_word(word2) )) {
            return true;
        }
    }

    word1 = std::string()+this->board[0][0] + this->board[1][1] + this->board[2][2];
    word2 = std::string()+this->board[0][2] + this->board[1][1] + this->board[2][0];

    if ((this->board[0][0] != ' ' && this->board[1][1] != ' ' && this->board[2][2] != ' ' && is_word(word1)) ||
        (this->board[0][2] != ' ' && this->board[1][1] != ' ' && this->board[2][0] != ' ' && is_word(word2))) {
        return true;
    }

    return false;
}

template<typename T>
bool WordBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool WordBoard<T>::game_is_over() {
    return is_win() || is_draw();

}

template <typename T>
WordPlayer<T>::WordPlayer (std::string name, T symbol) : Player<T>(name, symbol) {

}
template <typename T>
void WordPlayer<T>::getmove(int& x, int& y) {\
    T sy;
    std::cout << "\nPlease enter your move x , y and the letter ex(13 C): ";
    std::cin >> x >> sy;
    this->symbol = toupper(sy);
    y = x % 10;
    x /= 10;
    x--;
    y--;
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        std::cout<< "\n*Invalid input! Please enter a valid move*\n";
    }
    std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
W_RandomPlayer<T>::W_RandomPlayer() : RandomPlayer<T>(' '){
    srand(static_cast<unsigned int>(time(0)));
}
template<typename T>
void W_RandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % 3;
    y = rand() % 3;
    this->symbol = 'A' + (rand() % 26);
}

#endif //WORD_TIC_H