#pragma once
#include <vector>
class Hand;
class Card;

using namespace std;

class Scorer
{
public:
    int findBestHand(vector<Hand> *hands);
    int compareHands(Hand hand1, Hand hand2);
    vector<Card> checkHandType(Hand *hand);

private:
    const int HAND_SIZE = 5;
    bool hasStraightFlush(vector<Card> *cards);
    bool hasFourOfAKind(vector<Card> *cards);
    bool hasFullHouse(vector<Card> *cards);
    bool hasFlush(vector<Card> *cards);
    bool hasStraight(vector<Card> *cards);
    bool hasThreeOfAKind(vector<Card> *cards);
    bool hasTwoPair(vector<Card> *cards);
    bool hasOnePair(vector<Card> *cards);
    bool hasHighCard(vector<Card> *cards);
};