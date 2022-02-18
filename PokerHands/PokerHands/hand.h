#pragma once
#include <vector>

using namespace std;

class Card;

class Hand
{
public:
    void deal(const Card& card);
    Card discard(const Card& card);
    void printCards();

private:
    vector<Card> cards;
};