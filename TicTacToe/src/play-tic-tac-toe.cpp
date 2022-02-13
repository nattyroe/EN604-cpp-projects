/// @file
/// @author Nathan Roe
/// Single-Player Tic-Tac-Toe Game
///
/// Player plays as 'X' and enters moves in the form "# #"
/// for the row, column of their move, and the software
/// plays as 'O'.

#include "Game/game.hpp"
#include <iostream>

using namespace std;

/// Main function; runs gameplay loop
int main()
{
    Game *newGame = new Game();

    cout << "Welcome to Tic Tac Toe" << endl;
    cout << "You will play as x and you're up First" << endl;
    cout << "Enter your Move as <row column>, ie '1 2'" << endl;
    // Kick-off new game
    newGame->playGame();

    cout << "Game Over!" << endl;

    return 0;
} // End function main