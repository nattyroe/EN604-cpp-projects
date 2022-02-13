#include "Game/game.hpp"
#include <iostream>

using namespace std;

int main()
{
    Game *newGame = new Game();

    cout << "Welcome to Tic Tac Toe" << endl;
    cout << "You will play as x and you're up First" << endl;
    cout << "Enter your Move as <row column>, ie '1 2'" << endl;
    newGame->playGame();

    cout << "Game Over!" << endl;

    return 0;
}