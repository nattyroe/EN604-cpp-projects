#pragma once
#include <string>
#include <vector>

class Card;

using namespace std;

// @file
// @author Nathan Roe
// Hand object for holding Cards for Poker
//
// Tracks set of cards using deal and discard functions.
// Also contains a Poker Hand Type.
class Hand
{
public:
    // Enum of posible card values
    enum class HandType
    {
        None,
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfAKind,
        Straight,
        Flush,
        FullHouse,
        FourOfAKind,
        StraightFlush
    };

    // Adds Card to hand
    //
    // @param *card - pointer to card being dealt
    void deal(const Card *card);

    // Removes Card from hand if match exists
    //
    // @param *card - pointer to match of card being discarded
    // @return the Card removed from the hand
    Card discard(const Card *card);

    // Get formatted string of cards in the hand
    //
    // @return std::string of cards giving value and suit
    string printCards();

    // Get string of hand type
    //
    // @return std::string of cards giving value and suit
    string printHandType();

    // Get the current number of cards in the hand
    //
    // @return an int containing the hand size
    int size();

    // Setter for Poker Hand Type, unvalidated
    //
    // @param handType - the HandType of the current hand
    void setHandType(HandType handType);

    // Getter for Poker Hand Type, unvalidated
    //
    // @return the HandType of the current hand
    HandType getHandType();

    // Getter for a std::vector of current Cards
    //
    // @return the current hand of Cards in a vector
    vector<Card> getCards();

private:
    // Vector for storing current hand
    vector<Card> cards;
    // Variable for storing HandType
    HandType handType = HandType::None;
};