#include "pc.h"
#include <iostream>

using namespace std;

int PC::getBet(int prevRaise, int minBet)
{
    int bet = 0;
    cout << "Player " << this << "'s Turn" << endl;
    cout << "Your Cards: " << this->printCards() << endl;
    while (true)
    {
        if (minBet > 0)
        {
            cout << "Minimum Bet is $" << minBet << endl;
        }
        cout << "The previous raise was $" << prevRaise << endl;
        cout << "You have $" << this->money << endl;
        cout << "Enter your bet, or $0 to fold: ";
        cin >> bet;

        if (bet >= minBet && bet >= prevRaise && bet <= this->money)
        {
            break;
        }
        else if (bet == this->money)
        {
            break;
        }
        else if (bet == 0 && minBet == 0)
        {
            break;
        }
        else if (bet > this->money)
        {
            cout << "Please bet an amount of $" << this->money << " or less" << endl;
        }
        else if (bet < minBet)
        {
            cout << "Please bet at leat $" << minBet <<", or go All In" << endl;
        }
        else
        {
            cout << "Bet at least $" << prevRaise << " to Call/Raise" << endl;
        }
    }

    this->money -= bet;
    return bet;
}

int PC::chooseDiscard(int maxDiscard)
{
    if (maxDiscard > this->cards.size())
    {
        maxDiscard = this->cards.size();
    }
    cout << "Player " << this << "'s Turn to Discard" << endl;
    cout << "You may discard up to " << maxDiscard << " cards." << endl;

    int cardSelection = 0;
    int numDiscarded = 0;
    while (numDiscarded < maxDiscard)
    {
        cout << this->printCards() << endl;
        cout << "Choose a card to discard (1-" << this->cards.size() << "), or 0 to Stop: ";
        cin >> cardSelection;
        if (cardSelection == 0)
        {
            break;
        }
        if (cardSelection > 0 && cardSelection <= this->cards.size())
        {
            this->cards.erase(this->cards.begin() + cardSelection - 1);
            ++numDiscarded;
        }
    }
    return numDiscarded;
}
