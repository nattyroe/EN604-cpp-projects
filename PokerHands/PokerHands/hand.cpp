#include "hand.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "card.h"

using namespace std;

void Hand::deal(const Card& card)
{
    this->cards.push_back(card);
    sort(this->cards.begin(), this->cards.end());
    reverse(this->cards.begin(), this->cards.end());
}

Card Hand::discard(const Card& card)
{
    Card discard;
    for (unsigned int idx = 0; idx < this->cards.size(); ++idx)
    {
        Card currCard = this->cards[idx];
        if (currCard.suit == card.suit &&
            currCard.value == card.value)
        {
            discard = this->cards[idx];
            this->cards.erase(this->cards.begin() + idx);
        }
    }
    return discard;
}

void Hand::printCards()
{
    for (Card card : this->cards)
    {
        cout << static_cast<underlying_type<Card::Value>::type>(card.value) << " " << (char)static_cast<underlying_type<Card::Suit>::type>(card.suit) << ", ";
    }
    cout << endl;
}
