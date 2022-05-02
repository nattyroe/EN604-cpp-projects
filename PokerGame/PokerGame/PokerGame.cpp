// PokerGame

#include <iostream>
#include "deck.h"
#include "game.h"

int main()
{
    const int NUM_COMPUTERS = 2;
    const int NUM_PLAYERS = 1;
    const int BUY_IN = 100;
    const int BLIND = 3;

    Game *game = new Game(NUM_PLAYERS, NUM_COMPUTERS, BUY_IN, BLIND);
    game->playGame();
}
