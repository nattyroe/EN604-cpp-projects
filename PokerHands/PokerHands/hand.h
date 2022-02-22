#pragma once
#include <string>
#include <vector>

class Card;

using namespace std;

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
    string printCards();
    int size();
    void setHandType(HandType handType);
    HandType getHandType();
    vector<Card> getCards();

private:
    vector<Card> cards;
    HandType handType = HandType::None;
};