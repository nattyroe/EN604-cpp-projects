#include "npc.h"
#include <algorithm>

int NPC::getBet(int prevRaise, int minBet)
{
    if (minBet > 0)
    {
        if (this->money > minBet)
        {
            this->money -= minBet;
            return minBet;
        }
        else
        {
            int prevFunds = this->money;
            this->money = 0;
            return prevFunds;
        }
    }

    if (prevRaise < this->money)
    {
        this->money -= prevRaise;
        return prevRaise;
    }
    else
    {
        return 0;
    }
}

int NPC::chooseDiscard(int maxDiscard)
{
    if (maxDiscard > this->cards.size())
    {
        maxDiscard = this->cards.size();
    }
    int numDiscard = rand() % maxDiscard;
    sort(this->cards.begin(), this->cards.end());
    for (int count = 0; count < numDiscard; ++count)
    {
        this->cards.erase(this->cards.end() - 1);
    }
    return numDiscard;
}
