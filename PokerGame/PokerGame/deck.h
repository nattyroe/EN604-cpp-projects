/// @file
/// @author Nathan Roe
#pragma once
#include <vector>
#include <exception>
#include "card.h"

using namespace std;

// Deck object for responsible for tracking all cards
//
// Allows for shuffling and dealing of cards. Dealing
// from an empty deck throws and error.
class Deck
{
public:
    /// Deck Constructor
    Deck();

    /// Error thrown when dealing from empty deck
    class EmptyDeck : public std::exception
    {
    public:
        virtual const char* what() const throw()
        {
            return "Cannot deal, deck is empty";
        }
    };

    /// Shuffle deck; returns previously dealt cards to deck
    void shuffle();

    /// Deal a card
    /// 
    /// Returns a pointer to the dealt card
    Card *deal();

    /// Getter for cards left in deck
    /// Return the number of cards remaining in the deck
    int cardsRemaining() { return this->unused_cards.size(); };

private:
    vector<Card> unused_cards;
    vector<Card> dealt_cards;
};
