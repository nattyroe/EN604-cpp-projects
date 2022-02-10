#include "Game/game.hpp"
#include <iostream>

using namespace std;

int main()
{
    Game *newGame = new Game();
    newGame->playGame();

    return 0;
}