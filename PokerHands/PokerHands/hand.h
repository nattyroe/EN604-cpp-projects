#pragma once
#include <vector>

using namespace std;

class Card;

class Hand
{
public:
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
    void deal(const Card& card);
    Card discard(const Card& card);
    void printCards();
    int size();
    void setHandType(HandType handType);
    HandType getHandType();
    vector<Card> getCards();

private:
    vector<Card> cards;
    HandType handType = HandType::None;
};