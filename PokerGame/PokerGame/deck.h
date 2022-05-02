#pragma once
#include <vector>
#include <exception>
#include "card.h"

using namespace std;

class Deck
{
public:
    Deck();

    class EmptyDeck : public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "Cannot deal, deck is empty";
        }
    };

void shuffle();
Card *deal();
int cardsRemaining() { return this->unused_cards.size(); };

private:
    vector<Card> unused_cards;
    vector<Card> dealt_cards;
};
