#include "hand.h"
#include "card.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Adds Card to hand
void Hand::deal(const Card *card)
{
    this->cards.push_back(*card);
} // End function deal

// Removes Card from hand if match exists
Card Hand::discard(const Card *card)
{
    Card discard;
    // Iterate through hand to find matching card
    for (unsigned int idx = 0; idx < this->cards.size(); ++idx)
    {
        Card currCard = this->cards[idx];
        // If card value and suit match, store card, and remove from hand
        if (currCard.suit == card->suit &&
            currCard.value == card->value)
        {
            discard = this->cards[idx];
            this->cards.erase(this->cards.begin() + idx);
        }
    }
    return discard;
} // End function discard

// Get the current number of cards in the hand
int Hand::size()
{
    return static_cast<int>(this->cards.size());
} // End function size

// Get formatted string of cards in the hand
std::string Hand::printCards()
{
    std::string result = "";
    // Print Value
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

        // Print suit
        switch (card.suit)
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

    // Remove the extra ", " from end of string
    return result.substr(0, result.size() - 2);
} // End function printCards

void Hand::setHandType(HandType handType)
{
    this->handType = handType;
}

// Getter for Poker Hand Type, unvalidated
Hand::HandType Hand::getHandType()
{
    return this->handType;
} // End function getHandType

// Getter for a std::vector of current Cards
vector<Card> Hand::getCards()
{
    return this->cards;
} // End function getHandType
