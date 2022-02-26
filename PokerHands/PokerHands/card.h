#pragma once

// @file
// @author Nathan Roe
// Card object for standard Ace-high playing cards
//
// Each card has a Value and Suit, and operator
// overloads so that cards can be compared against
// each other.
class Card
{
public:
    // Enum of posible card values
    enum class Value
    {
        Invalid = 0,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13,
        Ace = 14
    };

    // Enum of posible card suits
    enum class Suit
    {
        Invalid = ' ',
        Clubs = 'C',
        Diamonds = 'D',
        Hearts = 'H',
        Spades = 'S'
    };

    // Constructs empty, invalid card
    Card();

    // Constructs card using Suit/Value enum parameters
    Card(Value value, Suit suit);

    // Check whether Card has valid suit and value
    //
    // @return True if both suit and value are valid, otherwise false
    bool isValid();

    // Override comparitor operators to compare cards
    bool operator<(const Card &card);
    bool operator>(const Card &card);
    bool operator==(const Card &card);

    // Card Suit
    Suit suit = Suit::Invalid;
    // Card Value
    Value value = Value::Invalid;
};