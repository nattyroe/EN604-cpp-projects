#pragma once

class Card
{
public:
    enum class Value
    {
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

    enum class Suit
    {
        Clubs = 'C',
        Diamonds = 'D',
        Hearts = 'H',
        Spades = 'S'
    };

    Card();
    Card(Value value, Suit suit);
    Card(int value, char suit);

    bool operator<(const Card &card);
    bool operator>(const Card &card);
    bool operator==(const Card &card);

    Suit suit;
    Value value;
};