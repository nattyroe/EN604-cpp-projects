#include "npc.h"
#include <algorithm>

// Get a bet for a betting round in Poker
int NPC::getBet(int prevRaise, int minBet)
{
    // If required bet, bet minimum amount
    if (minBet > 0)
    {
        // Bet required value
        if (this->money > minBet)
        {
            this->money -= minBet;
            return minBet;
        }
        // Bet remaining money if less than required
        else
        {
            int prevFunds = this->money;
            this->money = 0;
            return prevFunds;
        }
    }

    // Call if funds are availible
    if (prevRaise < this->money)
    {
        this->money -= prevRaise;
        return prevRaise;
    }
    // Otherwise, fold
    else
    {
        return 0;
    }
} // End function getBet

// Choose which cards to discard for draw phase of 5-Card draw
int NPC::chooseDiscard(int maxDiscard)
{
    if (maxDiscard > this->cards.size())
    {
        maxDiscard = this->cards.size();
    }
    int numDiscard = rand() % maxDiscard;
    // Sort cards High to Low
    sort(this->cards.begin(), this->cards.end());
    // Randomly select some number of cards to discard
    for (int count = 0; count < numDiscard; ++count)
    {
        // Discard lowest n cards
        this->cards.erase(this->cards.end() - 1);
    }
    return numDiscard;
} // End function chooseDiscard
