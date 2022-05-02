#include "pc.h"
#include <iostream>

using namespace std;

// Get a bet for a betting round in Poker
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

        // Verify bet is a valid bet when a required bet is needed
        if (bet >= minBet && bet >= prevRaise && bet <= this->money)
        {
            break;
        }
        // Accept All In bets
        else if (bet == this->money)
        {
            break;
        }
        // Accept fold/calls when no min bet is needed
        else if (bet == 0 && minBet == 0)
        {
            break;
        }
        // Catch error for betting unavailible money
        else if (bet > this->money)
        {
            cout << "Please bet an amount of $" << this->money << " or less" << endl;
        }
        // Catch error for betting under required value
        else if (bet < minBet)
        {
            cout << "Please bet at leat $" << minBet <<", or go All In" << endl;
        }
        // Catch error for not Calling or Folding
        else
        {
            cout << "Bet at least $" << prevRaise << " to Call/Raise" << endl;
        }
    }

    this->money -= bet;
    return bet;
} // End function getBet

// Choose which cards to discard for draw phase of 5-Card draw
int PC::chooseDiscard(int maxDiscard)
{
    // Find max possible discards
    if (maxDiscard > this->cards.size())
    {
        maxDiscard = this->cards.size();
    }
    cout << "Player " << this << "'s Turn to Discard" << endl;
    cout << "You may discard up to " << maxDiscard << " cards." << endl;

    int cardSelection = 0;
    int numDiscarded = 0;
    // Discard up to max cards, or until player exits loop
    while (numDiscarded < maxDiscard)
    {
        cout << this->printCards() << endl;
        cout << "Choose a card to discard (1-" << this->cards.size() << "), or 0 to Stop: ";
        cin >> cardSelection;
        // Exit Loop condition
        if (cardSelection == 0)
        {
            break;
        }
        // Player selects valid card for discard
        if (cardSelection > 0 && cardSelection <= this->cards.size())
        {
            // Discard indexed from 1-N, not by 0
            this->cards.erase(this->cards.begin() + cardSelection - 1);
            ++numDiscarded;
        }
    }
    return numDiscarded;
} // End function chooseDiscard
