#include "hand.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "card.h"

using namespace std;

void Hand::deal(const Card& card)
{
    this->cards.push_back(card);
    //sort(this->cards.begin(), this->cards.end());
    //reverse(this->cards.begin(), this->cards.end());
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

int Hand::size()
{
    return static_cast<int>(this->cards.size());
}

std::string Hand::printCards()
{
    std::string result = "";
    for (Card card : this->cards)
    {
        switch (card.value)
        {
        case Card::Value::Two:
            result += "2 of ";
            break;
        case Card::Value::Three:
            result += "3 of ";
            break;
        case Card::Value::Four:
            result += "4 of ";
            break;
        case Card::Value::Five:
            result += "5 of ";
            break;
        case Card::Value::Six:
            result += "6 of ";
            break;
        case Card::Value::Seven:
            result += "7 of ";
            break;
        case Card::Value::Eight:
            result += "8 of ";
            break;
        case Card::Value::Nine:
            result += "9 of ";
            break;
        case Card::Value::Ten:
            result += "10 of ";
            break;
        case Card::Value::Jack:
            result += "J of ";
            break;
        case Card::Value::Queen:
            result += "Q of ";
            break;
        case Card::Value::King:
            result += "K of ";
            break;
        case Card::Value::Ace:
            result += "A of ";
            break;
        default:
            result += "ERROR of ";
            break;
        };

        switch(card.suit)
        {
        case Card::Suit::Clubs:
            result += "Clubs, ";
            break;
        case Card::Suit::Diamonds:
            result += "Diamonds, ";
            break;
        case Card::Suit::Hearts:
            result += "Hearts, ";
            break;
        case Card::Suit::Spades:
            result += "Spades, ";
            break;
        default:
            result += "ERROR, ";
            break;
        };
    }
    return result.substr(0, result.size() - 2);
}

void Hand::setHandType(HandType handType)
{
    this->handType = handType;
}

Hand::HandType Hand::getHandType()
{
    return this->handType;
}

vector<Card> Hand::getCards()
{
    return this->cards;
}
