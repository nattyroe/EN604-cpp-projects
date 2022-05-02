#pragma once
#include "player.h"

class Game;

class PC : public Player
{
public:
    PC(Game *game, int buyIn) : Player(game, buyIn) {};
    int getBet(int prevRaise, int minBet = 0);
    int chooseDiscard(int maxDiscard);
};

