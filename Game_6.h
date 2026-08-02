#ifndef GAME_6_H
#define GAME_6_H
#include "BoardGame_Classes.h"

void Check_stop(int i, int j, bool f);
template < typename T >
  class Game_6_Board: public Board < T > {
    public:
    static bool check;
    static bool first;

    Game_6_Board();
    bool update_board(int x, int y, T symbol);
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void display_board();
    void check_stop(int i, int j);

  };

template < typename T >
  class Game_6_Player: public Player < T > {
    public:
    Game_6_Player(string name, T symbol);
    void getmove(int & x, int & y);
  };

template < typename T >
  class Game_6_Random_Player: public RandomPlayer < T > {
    public:
    Game_6_Random_Player(T symbol);
    void getmove(int & x, int & y);
  };

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor for Game_6_Board
template < typename T >
  Game_6_Board < T > ::Game_6_Board() {
    this -> rows = this -> columns = 3;
    this -> board = new char * [this -> rows];  // Dynamically allocate memory for the board
    for (int i = 0; i < this -> rows; i++) {
      this -> board[i] = new char[this -> columns];
      for (int j = 0; j < this -> columns; j++) {
        this -> board[i][j] = 0;
      }
    }
    this -> n_moves = 0;
  }

template < typename T >
  bool Game_6_Board < T > ::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (check == false) {
      if (x >= 0 && x < this -> rows && y >= 0 && y < this -> columns && this -> board[x][y] == 0 && mark != 0) {

        this -> n_moves++;
        this -> board[x][y] = toupper(mark);

        return true; // Move was valid
      }

      cout<<"\nInvalid move\n";
      return false; // Move was invalid
    }

    return true; // Game is already over

  }

// Display the board and the pieces on it
template < typename T >
  void Game_6_Board < T > ::display_board() {
    if (check == false) {
      cout << "    0    1    2";
      for (int i = 0; i < this -> rows; i++) {
        cout << "\n" << i << " |";
        for (int j = 0; j < this -> columns; j++) {

          cout << setw(3) << this -> board[i][j] << " |";
        }
        cout << "\n  ----------------";
      }
      cout << "\n\n";
    }

  }

// Returns true if there is any winner
template < typename T >
  bool Game_6_Board < T > ::is_win() {
    // If the game is already marked as over, return true
    if (check == true) {
      return true;
    }
    // Check rows and columns for a winner
    for (int i = 0; i < this -> rows; i++) {

      if (this -> board[i][0] == this -> board[i][1] && this -> board[i][1] == this -> board[i][2] && this -> board[i][0] != 0) {
        check_stop(i, 0); // Stop the game if a winner is found

      }
      if (this -> board[0][i] == this -> board[1][i] && this -> board[1][i] == this -> board[2][i] && this -> board[0][i] != 0) {
        check_stop(0, i); // Stop the game if a winner is found

      }
    }

    // Check diagonals for a winner
    if ((this -> board[0][0] == this -> board[1][1] && this -> board[1][1] == this -> board[2][2] && this -> board[0][0] != 0) ||
      (this -> board[0][2] == this -> board[1][1] && this -> board[1][1] == this -> board[2][0] && this -> board[0][2] != 0)) {
      if (this -> board[0][0]) {
        check_stop(0, 0); // Stop the game if a winner is found

      }
      if (this -> board[0][2]) {
        check_stop(0, 2); // Stop the game if a winner is found

      }
    }

    return false; // No winner found
  }

// Return true if 9 moves are done and no winner
template < typename T >
  bool Game_6_Board < T > ::is_draw() {
    return (this -> n_moves == 9 && !is_win());
  }

template < typename T >
  bool Game_6_Board < T > ::game_is_over() {
    return is_win() || is_draw();
  }

//--------------------------------------

// Constructor for Game_6_Player
template < typename T >
  Game_6_Player < T > ::Game_6_Player(string name, T symbol): Player < T > (name, symbol) {}

template < typename T >
  void Game_6_Player < T > ::getmove(int & x, int & y) {
    if (Game_6_Board < T > ::check == false) {

      cout << this -> getname() << "(" << this -> getsymbol() << ") please enter your move row and col: ";
      cin >> x >> y;

    }

  }

// Constructor for Game_6_Random_Player
template < typename T >
  Game_6_Random_Player < T > ::Game_6_Random_Player(T symbol): RandomPlayer < T > (symbol) {
    this -> dimension = 3;
    this -> name = "Random Computer Player";
    srand(static_cast < unsigned int > (time(0))); // Seed the random number generator
  }

template < typename T >
  void Game_6_Random_Player < T > ::getmove(int & x, int & y) {
    if (Game_6_Board < T > ::check == false) {
      x = rand() % this -> dimension; // Random number between 0 and 2
      y = rand() % this -> dimension;
    }
  }

// Function to stop the game
template < typename T >
  void Game_6_Board < T > ::check_stop(int i, int j) {
    if (this -> board[i][j] == 'X' && first == false) {
      first = true;
      check = true;

    } else if (this -> board[i][j] == 'O' && first == false) {
      first = true;

    } else if (this -> board[i][j] == 'O' && first == true) {
      check = true;

    }
  }

// Static variable definitions
template < typename T >
  bool Game_6_Board < T > ::check = false;
template < typename T >
  bool Game_6_Board < T > ::first = false;

#endif //GAME_6_H
