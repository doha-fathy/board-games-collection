#include "Game_1.h"
#include "Game_2.h"
#include "Game_3.h"
#include "Game_4.h"
#include "Game_5.h"
#include "Game_6.h"
#include "Game_7.h"
#include "Game_8.h"
#include "Game_9.h"
#include "X_O.h"
#include "BoardGame_Classes.h"
using namespace std;

// Prototype functions
void Pyramid_X_O(); // Game 1
void playConnectFourGame(); // Game 2
void Tic_Tac_Toe_5x5(); // Game 3
void words_Tic(); // Game 4
void playNumericalTictactoe(); // Game 5
void Misere_Tic_Tac_Toe(); // Game 6
void Tic_Tac_Toe_4x4 (); // Game 7
void Ultimate_X_O(); // Game 8
void playSUSGame(); // Game 9




#include <iostream>
using namespace std;

#include <iostream>
using namespace std;

int main() {
    cout << "******************************************************\n";
    cout << "*          Welcome to the Ultimate Game Hub!        *\n";
    cout << "*  Explore a variety of exciting games to play and  *\n";
    cout << "*             have fun! Let's get started!          *\n";
    cout << "******************************************************\n\n";

    while (true) {
        cout << "Select a game to play:\n";
        cout << "1. Pyramid X-O\n2. Connect Four\n3. 5x5 Tic Tac Toe\n";
        cout << "4. Words Tic Tac Toe\n5. Numerical Tic Tac Toe\n6. Misere Tic Tac Toe\n";
        cout << "7. 4x4 Tic Tac Toe\n8. Ultimate X-O\n9. SUS Game\n10. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            Pyramid_X_O();
        } else if (choice == 2) {
            playConnectFourGame();
        } else if (choice == 3) {
            Tic_Tac_Toe_5x5();
        } else if (choice == 4) {
            words_Tic();
        } else if (choice == 5) {
            playNumericalTictactoe();
        } else if (choice == 6) {
            Misere_Tic_Tac_Toe();
        } else if (choice == 7) {
            Tic_Tac_Toe_4x4();
        } else if (choice == 8) {
            Ultimate_X_O();
        } else if (choice == 9) {
            playSUSGame();
        } else if (choice == 10) {
            cout << "\nThank you for playing! See you next time!\n";
            return 0; // Exit the program
        } else {
            cout << "\n**Invalid choice. Please try again**\n";
        }
    }
}





void Pyramid_X_O() {
    string choice;
    Player<char>* players[2];
    Board<char>* B = new PyramidBoard<char>();
    string playerName;

    cout << "\nWelcome to pyramid X-O Game. :)\n";

    string character = "XO";
    int player = 1;

    while (player <= 2) {
        cout << "\nPlayer " << character[player-1] <<" type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. AI Player\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == "1") {
            cout << "Enter Player " << character[player-1] <<" name: ";
            cin >> playerName;
            players[player-1] = new HumanPlayer(playerName, character[player-1]);
        }else if (choice == "2") {
            players[player-1] = new P_RandomPlayer(character[player-1]);
        }else if (choice == "3") {
            players[player-1] = new AI_Player<char>(character[player-1], B);
        }else {
            cout << "\n** Invalid choice **\n";
            continue;
        }
        player++;
    }

    // Create the game manager and run the game
    GameManager<char> prymid(B, players);
    prymid.run();

    // Clean up
    delete B;
    delete players[0];
    delete players[1];
}


void playConnectFourGame() {
    ConnectFourBoard* board = new ConnectFourBoard();
    Player<char>* players[2] = {nullptr, nullptr};

    cout << "\n--- Welcome to Connect Four! ---\n";
    cout << "RULES:\n";
    cout << "1. Players take turns dropping discs into a column.\n";
    cout << "2. The first to align 4 discs horizontally, vertically, or diagonally wins.\n\n";
    cout << "Let's get started!\n";

    char choice;
    do {
        cout << "\nSelect the game mode:\nA) Real Player vs Real Player\n";
        cout << "B) Real Player vs Random AI\nC) Real Player vs Smart AI\nEnter your choice: ";
        cin >> choice;
        choice = toupper(choice);
    } while (choice != 'A' && choice != 'B' && choice != 'C');

    cout << "\nEnter name for Player 1: ";
    string player1_name;
    cin >> player1_name;

    cout << "\nWhat disc you want to play with (enter 'X' or 'O'): ";
    char player_symbol;
    cin >> player_symbol;
    player_symbol = toupper(player_symbol);

    while (player_symbol != 'X' && player_symbol != 'O') {
        cout << "Invalid choice. Please enter X or O: ";
        cin >> player_symbol;
        player_symbol = toupper(player_symbol);
    }

    players[0] = new ConnectFourPlayer(player1_name, player_symbol);
    players[0]->setBoard(board);

    char player2_symbol = (player_symbol == 'X') ? 'O' : 'X';
    if (choice == 'A') {
        cout << "\nEnter name for Player 2: ";
        string player2_name;
        cin >> player2_name;

        players[1] = new ConnectFourPlayer(player2_name, player2_symbol);
    } else if (choice == 'B') {
        players[1] = new ConnectRandomPlayer<char>(player2_symbol);
    } else if (choice == 'C') {
        players[1] = new ConnectFourAIPlayer(player2_symbol, player_symbol);
    }

    players[1]->setBoard(board);

    cout << "\n" << player1_name << " will play as " << player_symbol << endl;
    cout << players[1]->getname() << " will play as " << player2_symbol << "\n\n";

    GameManager<char> game(board, players);
    game.run();

    delete board;
    delete players[0];
    delete players[1];
}

void Tic_Tac_Toe_5x5() {
    string choice;
    Player<char>* players[2];
    Game_3_Board<char>* B = new Game_3_Board<char>();
    string player1Name, player2Name;

    cout << "========= Welcome to 5 x 5 Tic Tac Toe =========\n";

    // Set up player 1
    cout << "Enter Player 1 name:";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";

    while(true){
        cout << "1] Human\n";
        cout << "2] Random Computer\n";
        cout<<"Enter choice :";
        cin>>choice;
        if(choice=="1") {
            players[0] = new Game_3_Player<char>( player1Name, 'X');  // Pass the board reference here
            break;
        }
        if(choice=="2") {
            players[0] = new Game_3_Random_Player<char>('X');  // No need for board reference

            break;
        }
        cout << "Invalid choice \n";
    }

    // Set up player 2
    cout << "Enter Player 2 name:";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";

    while(true){

        cout << "1] Human\n";
        cout << "2] Random Computer\n";
        cout<<"Enter choice :";

        cin>>choice;
        if(choice=="1") {
            players[1] = new Game_3_Player<char>( player2Name, 'O');  // Pass the board reference here
            break;
        }
        if(choice=="2") {
            players[1] = new Game_3_Random_Player<char>('O');  // No need for board reference

            break;
        }

        cout << "\nInvalid choice \n";
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}

void words_Tic() {
    string choice;
    Player<char>* players[2];
    Board<char>* B = new WordBoard<char>();
    string playerName;

    cout << "\nWelcome to words Tic Tac Toe Game. :)\n";

    int player = 1;

    while (player <= 2) {
        cout << "\nPlayer " << player <<" type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == "1") {
            cout << "Enter Player " << player <<" name: ";
            cin >> playerName;
            players[player-1] = new WordPlayer<char>(playerName);
        }else if (choice == "2") {
            players[player-1] = new W_RandomPlayer<char>();
        }else {
            cout << "\n** Invalid choice **\n";
            continue;
        }
        player++;
    }

    // Create the game manager and run the game
    GameManager<char> Word(B, players);
    Word.run();

    // Clean up
    delete B;
    delete players[0];
    delete players[1];
}

void playNumericalTictactoe() {
    cout << "\n--- Welcome to Numerical Tic-Tac-Toe! ---\n";
    cout << "This game is a numerical variation of the classic Tic-Tac-Toe game.\n\n";
    cout << "RULES:\n";
    cout << "1. The game is played on a 3x3 grid.\n";
    cout << "2. Player 1 chooses to play with either 'odd' or 'even' numbers.\n";
    cout << "   - Odd numbers: 1, 3, 5, 7, 9\n";
    cout << "   - Even numbers: 2, 4, 6, 8\n";
    cout << "3. Players take turns placing their chosen numbers on the grid.\n";
    cout << "4. A position can only hold one number, and no number can be reused.\n";
    cout << "5. To win, a player must make the sum of three numbers in a row, column, or diagonal equal to 15.\n";
    cout << "Let's get started!\n";

    char choice;
    do {
        cout << "\nSelect the game mode:\nA) Real Player vs Real Player\n";
        cout << "B) Real Player vs Random AI\nEnter your choice: ";
        cin >> choice;
        choice = toupper(choice);
    } while (choice != 'A' && choice != 'B');

    cout << "\nEnter name for Player 1: ";
    string player1_name;
    cin >> player1_name;

    bool player1_odd_choice;
    cout << '\n' << player1_name << ", do you want to play with odd or even numbers? (Enter 'odd' or 'even'): ";
    string odd_even_choice;
    while (true) {
        cin >> odd_even_choice;
        transform(odd_even_choice.begin(), odd_even_choice.end(), odd_even_choice.begin(), ::tolower);

        if (odd_even_choice == "odd") {
            player1_odd_choice = true;
            break;
        } else if (odd_even_choice == "even") {
            player1_odd_choice = false;
            break;
        } else {
            cout << "\nInvalid choice. Please enter 'odd' or 'even': ";
        }
    }
    NumericalPlayer<char>* player1 = new NumericalPlayer<char>(player1_name, ' ', player1_odd_choice);
    NumericalPlayer<char>* player2_real = nullptr;
    NumericalRandomPlayer<char>* player2_random = nullptr;
    string player2_name;
    vector<char> ai_numbers = player1_odd_choice ? vector<char>{'2', '4', '6', '8'} : vector<char>{'1', '3', '5', '7', '9'};
    while (true) {
        if (choice == 'A') {
            cout << "\nEnter name for Player 2: ";
            cin >> player2_name;
            player2_real = new NumericalPlayer<char>(player2_name, ' ', !player1_odd_choice);
            break;
        } else if (choice == 'B') {
            player2_name = "Random AI";
            player2_random = new NumericalRandomPlayer<char>(' ', ai_numbers);
            break;
        } else {
            cout << "\n**Invalid choice. Please choose from A to B**" << endl;
            continue;
        }
    }

    cout << "\n" << player1_name << " will play with " << (player1_odd_choice ? "odd" : "even") << " numbers.\n";
    cout << player2_name << " will play with " << (!player1_odd_choice ? "odd" : "even") << " numbers.\n\n";

    NumericalBoard<char>* board = new NumericalBoard<char>();
    Player<char>* players[2];
    players[0] = player1;

    if (choice == 'A') {
        players[1] = player2_real;
    } else if (choice == 'B') {
        players[1] = player2_random;
    }
    GameManager<char> game(board, players);
    game.run();

    delete player1;
    delete board;
    if (choice == 'A') {
        delete player2_real;
    } else if (choice == 'B') {
        delete player2_random;
    }
}

void Misere_Tic_Tac_Toe() {

    string choice;
    Player<char>* players[2];
    Game_6_Board<char>* B = new Game_6_Board<char>();
    string player1Name, player2Name;

    cout << "========= Welcome to Misere Tic Tac Toe =========\n";

    // Set up player 1
    cout << "Enter Player 1 name:";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";

    while(true){
        cout << "1] Human\n";
        cout << "2] Random Computer\n";
        cout<<"Enter choice :";
        cin>>choice;
        if(choice=="1") {
            players[0] = new Game_6_Player<char>( player1Name, 'X');  // Pass the board reference here
            break;
        }
        if(choice=="2") {
            players[0] = new Game_6_Random_Player<char>('X');  // No need for board reference

                break;
            }
            cout << "Invalid choice \n";
        }

        // Set up player 2
        cout << "Enter Player 2 name:";
        cin >> player2Name;
        cout << "Choose Player 2 type:\n";

        while(true){

            cout << "1] Human\n";
            cout << "2] Random Computer\n";
            cout<<"Enter choice :";

            cin>>choice;
            if(choice=="1") {
                players[1] = new Game_6_Player<char>( player2Name, 'O');  // Pass the board reference here
                break;
            }
            if(choice=="2") {
                players[1] = new Game_6_Random_Player<char>('O');  // No need for board reference

                break;
            }

            cout << "\nInvalid choice \n";
        }

        // Create the game manager and run the game
        GameManager<char> x_o_game(B, players);
        x_o_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

}

void Tic_Tac_Toe_4x4 () {
    string choice;
    Player<char>* players[2];
    Game_7_Board<char>* B = new Game_7_Board<char>();
    string player1Name, player2Name;

    cout << "============= 4x4 Tic Tac Toe =============\n";

    // Set up player 1
    cout << "Enter Player 1 name:";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";

    while(true){
        cout << "1] Human\n";
        cout << "2] Random Computer\n";
        cin>>choice;
        if(choice=="1") {
            players[0] = new Game_7_Player<char>( player1Name, 'X');  // Pass the board reference here
            break;
        }
        if(choice=="2") {
            players[0] = new Game_7_Random_Player<char>('X');  // No need for board reference

            break;
        }

        cout << "Invalid choice \n";
    }

    // Set up player 2
    cout << "Enter Player 2 name:";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";

    while(true){

        cout << "1] Human\n";
        cout << "2] Random Computer\n";
        cin>>choice;
        if(choice=="1") {
            players[1] = new Game_7_Player<char>( player2Name, 'O');  // Pass the board reference here
            break;
        }
        if(choice=="2") {
            players[1] = new Game_7_Random_Player<char>('O');  // No need for board reference

            break;
        }

        cout << "Invalid choice \n";
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Ultimate_X_O() {
    string choice;
    Player<char>* players[2];
    Board<char>* B = new UltimateBoard<char>();
    string playerName;

    cout << "\nWelcome to Ultimate X-O Game. :)\n";

    string character = "XO";
    int player = 1;

    while (player <= 2) {
        cout << "\nPlayer " << character[player-1] <<" type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == "1") {
            cout << "Enter Player " << character[player-1] <<" name: ";
            cin >> playerName;
            players[player-1] = new UltimatePlayer<char>(playerName, character[player-1]);
        }else if (choice == "2") {
            players[player-1] = new U_RandomPlayer(character[player-1]);
        }else {
            cout << "\n** Invalid choice **\n";
            continue;
        }
        player++;
    }

    // Create the game manager and run the game
    GameManager<char> Ultimate(B, players);
    Ultimate.run();

    // Clean up
    delete B;
    delete players[0];
    delete players[1];
}

void playSUSGame() {
    SUSBoard* board = new SUSBoard();
    Player<char>* players[2] = {nullptr, nullptr};

    cout << "\n--- Welcome to the SUS Game! ---\n";
    cout << "RULES:\n";
    cout << "1. Players take turns placing their symbols (S, U).\n";
    cout << "2. Players try to complete 'SUS' patterns on the board.\n";
    cout << "3. The player with the most valid 'SUS' patterns wins!\n\n";
    cout << "Let's get started!\n";

    char choice;
    do {
        cout << "\nSelect the game mode:\nA) Real Player vs Real Player\n";
        cout << "B) Real Player vs Random Player\nEnter your choice: ";
        cin >> choice;
        choice = toupper(choice);
    } while (choice != 'A' && choice != 'B');

    cout << "\nEnter name for Player 1: ";
    string player1_name;
    cin >> player1_name;

    cout << "\nWhat symbol do you want to play with (enter 'S' or 'U'): ";
    char player_symbol;
    cin >> player_symbol;
    player_symbol = toupper(player_symbol);

    while (player_symbol != 'S' && player_symbol != 'U') {
        cout << "Invalid choice. Please enter S or U: ";
        cin >> player_symbol;
        player_symbol = toupper(player_symbol);
    }

    players[0] = new SUSPlayer(player1_name, player_symbol);
    players[0]->setBoard(board);

    char player2_symbol = (player_symbol == 'S') ? 'U' : 'S';
    if (choice == 'A') {
        cout << "\nEnter name for Player 2: ";
        string player2_name;
        cin >> player2_name;

        players[1] = new SUSPlayer(player2_name, player2_symbol);
    } else if (choice == 'B') {
        string player2_name = "RandomPlayer";
        players[1] = new SUSRandomPlayer(player2_name, player2_symbol);
    }

    players[1]->setBoard(board);

    cout << "\n" << player1_name << " will play as " << player_symbol << endl;
    cout << players[1]->getname() << " will play as " << player2_symbol << "\n\n";

    GameManager<char> game(board, players);
    game.run();

    int score1 = board->count_sus(player_symbol);
    int score2 = board->count_sus(player2_symbol);

    cout << "\nGame Over! Final Results:\n";
    cout << player1_name << "'s Score (" << player_symbol << "): " << score1 << endl;
    cout << players[1]->getname() << "'s Score (" << player2_symbol << "): " << score2 << endl;

    if (score1 > score2) {
        cout << player1_name << " wins!\n";
    } else if (score2 > score1) {
        cout << players[1]->getname() << " wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    delete board;
    delete players[0];
    delete players[1];
}