/// Run a 5-Card Draw Poker Game
#include <iostream>
#include "deck.h"
#include "game.h"

/// Run main game loop, with compile-time parameters
int main()
{
    // Set number of Human/Computer Players
    const int NUM_COMPUTERS = 2;
    const int NUM_PLAYERS = 1;
    // Set starting money amount
    const int BUY_IN = 100;
    // Set minimum bet values
    const int BLIND = 3;

    // Run Poker Game
    Game *game = new Game(NUM_PLAYERS, NUM_COMPUTERS, BUY_IN, BLIND);
    game->playGame();
} // End function main
