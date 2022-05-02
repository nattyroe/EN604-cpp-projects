#pragma once
#include "hand.h"

class Game;

class Player : public Hand
{
public:
    Player(Game *game, int buyIn);
    virtual ~Player();

    void discardHand();

    bool isBroke() { return this->money <= 0; };
    int getRemainingFunds() { return this->money; };

    virtual int getBet(int prevRaise, int minBet = 0) = 0;
    void addWinnings(int winnings) { this->money += winnings; };

    virtual int chooseDiscard(int maxDiscard) = 0;

protected:
    Game *game;
    int money = 0;
};

