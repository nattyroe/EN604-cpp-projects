#include "card.hpp"

Card::Card() {}

Card::Card(Value value, Suit suit)
{
    this->value = value;
    this->suit = suit;
}

Card::Card(int value, char suit)
{
    this->value = static_cast<Value>(value);
    this->suit = static_cast<Suit>(suit);
}

bool Card::operator<(const Card &card)
{
    return this->value < card.value;
}

bool Card::operator>(const Card &card)
{
    return this->value > card.value;
}

bool Card::operator==(const Card &card)
{
    return this->value == card.value;
}
