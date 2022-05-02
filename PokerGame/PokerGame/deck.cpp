#include "deck.h"
#include "card.h"
#include <array>
#include <list>
#include <algorithm>
#include <stdlib.h>

using namespace std;

Deck::Deck()
{
    const int RAND_SEED = 7;
    srand(RAND_SEED);

    array<Card::Value, 13> values = { Card::Value::Two, Card::Value::Three, Card::Value::Four,
                                      Card::Value::Five, Card::Value::Six, Card::Value::Seven,
                                      Card::Value::Eight, Card::Value::Nine, Card::Value::Ten,
                                      Card::Value::Jack, Card::Value::Queen, Card::Value::King,
                                      Card::Value::Ace };
    array<Card::Suit, 4> suits = { Card::Suit::Clubs, Card::Suit::Diamonds,
                                   Card::Suit::Hearts, Card::Suit::Spades };

    for (Card::Suit suit : suits)
    {
        for (Card::Value value : values)
        {
            Card *card = new Card(value, suit);
            this->unused_cards.push_back(*card);
        }
    }
}

void Deck::shuffle()
{
    while (!this->dealt_cards.empty())
    {
        this->unused_cards.push_back(this->dealt_cards.back());
        this->dealt_cards.pop_back();
    }
    sort(this->unused_cards.begin(), this->unused_cards.end());

    for (unsigned int idx = 0; idx < this->unused_cards.size(); ++idx)
    {
        int swapIdx = rand() % this->unused_cards.size();
        swap(this->unused_cards[idx], this->unused_cards[swapIdx]);
    }
}

Card *Deck::deal()
{
    if (!this->unused_cards.empty())
    {
        this->dealt_cards.push_back(this->unused_cards.back());
        this->unused_cards.pop_back();
        return &this->dealt_cards.back();
    }
    else
    {
        throw EmptyDeck();
    }
}
