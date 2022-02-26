#include "card.h"

// Constructs empty, invalid card
Card::Card() {}

// Constructs card using Suit/Value enum parameters
Card::Card(Value value, Suit suit)
{
    this->value = value;
    this->suit = suit;
} // End Card constructor

// Check whether Card has valid suit and value
bool Card::isValid()
{
    return (!(this->suit == Card::Suit::Invalid) &&
            !(this->value == Card::Value::Invalid));
} // End function isValid

// Less-than operator for comparing Cards
bool Card::operator<(const Card &card)
{
    return this->value < card.value;
} // End < operator override

// Greater-than operator for comparing Cards
bool Card::operator>(const Card &card)
{
    return this->value > card.value;
} // End > operator override

// Equality operator for comparing Cards
bool Card::operator==(const Card &card)
{
    return this->value == card.value;
} // End == operator override
