#include "deck.h"
#include "card.h"
#include <array>
#include <list>
#include <algorithm>
#include <stdlib.h>

using namespace std;

// Deck object for responsible for tracking all cards
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

    // Create one card of each value/suit combination
    for (Card::Suit suit : suits)
    {
        for (Card::Value value : values)
        {
            Card *card = new Card(value, suit);
            this->unusedCards.push_back(*card);
        }
    }
} // End Deck constructor

// Shuffle deck; returns previously dealt cards to deck
void Deck::shuffle()
{
    // Return dealt cards to deck
    while (!this->dealtCards.empty())
    {
        this->unusedCards.push_back(this->dealtCards.back());
        this->dealtCards.pop_back();
    }
    sort(this->unusedCards.begin(), this->unusedCards.end());

    // Shuffle using Fisher-Yates (https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
    for (unsigned int idx = 0; idx < this->unusedCards.size(); ++idx)
    {
        int swapIdx = rand() % this->unusedCards.size();
        swap(this->unusedCards[idx], this->unusedCards[swapIdx]);
    }
} // End function shuffle

// Deal a card
Card *Deck::deal()
{
    if (!this->unusedCards.empty())
    {
        // Shift card from unused to dealt
        this->dealtCards.push_back(this->unusedCards.back());
        this->unusedCards.pop_back();
        // Return pointer to dealt card
        return &this->dealtCards.back();
    }
    // Throw error if deck is empty
    else
    {
        throw EmptyDeck();
    }
} // End function deal
