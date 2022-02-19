#include "Scorer.h"
#include "hand.h"
#include "card.h"
#include <vector>
#include <algorithm>

using namespace std;

int Scorer::compareHands(Hand *hand1, Hand *hand2)
{
    if (!(hand1->size() == HAND_SIZE) ||
        !(hand2->size() == HAND_SIZE))
    {
        return -1;
    }

    checkHandType(hand1);
    checkHandType(hand2);


}

vector<Card> Scorer::checkHandType(Hand* hand)
{
    vector<Card> cards = hand->getCards();
    for (Card card : cards)
    {
        if (!card.isValid())
        {
            return cards;
        }
    }

    if (hasStraightFlush(&cards))
    {
        hand->setHandType(Hand::HandType::StraightFlush);
    }
    else if (hasFourOfAKind(&cards))
    {
        hand->setHandType(Hand::HandType::FourOfAKind);
    }
    else if (hasFullHouse(&cards))
    {
        hand->setHandType(Hand::HandType::FullHouse);
    }
    else
    {
        hand->setHandType(Hand::HandType::None);
    }

    return cards;
}

bool Scorer::hasStraightFlush(vector<Card> *cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    // Special case for Ace-Low
    if (cards->at(0).value == Card::Value::Ace &&
        cards->at(1).value == Card::Value::Five)
    {
        int startVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(1).value);
        Card::Suit startSuit = cards->at(0).suit;
        for (int idx = 2; idx < cards->size(); ++idx)
        {
            int cardVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(idx).value);
            Card::Suit cardSuit = cards->at(idx).suit;
            if (!(cards->at(idx).isValid()) ||
                !(cardSuit == startSuit) ||
                !(cardVal == startVal-- - 1))
            {
                return false;
            }
        }
        Card ace = cards->front();
        cards->erase(cards->begin());
        cards->push_back(ace);
    }
    // Check Cases with no Aces
    else
    {
        int startVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(0).value);
        Card::Suit startSuit = cards->at(0).suit;
        for (int idx = 1; idx < cards->size(); ++idx)
        {
            int cardVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(idx).value);
            Card::Suit cardSuit = cards->at(idx).suit;
            if (!(cards->at(idx).isValid()) ||
                !(cardSuit == startSuit) ||
                !(cardVal == startVal-- - 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool Scorer::hasFourOfAKind(vector<Card>* cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    int FOAK = 4;
    int foundFOAK = false;
    Card::Value startVal = Card::Value::Invalid;
    for (int idx = 0; idx <= cards->size() - FOAK; ++idx)
    {
        foundFOAK = true;
        startVal = cards->at(idx).value;
        for (int innerIdx = idx + 1; innerIdx < idx + FOAK; ++innerIdx)
        {
            Card::Value cardVal = cards->at(innerIdx).value;
            if (!(cards->at(innerIdx).isValid()) ||
                !(startVal == cardVal))
            {
                foundFOAK = false;
                break;
            }
        }
        if (foundFOAK)
        {
            break;
        }
    }

    if (foundFOAK)
    {
        vector<Card> unusedCards;
        for (int idx = 0; idx < cards->size(); ++idx)
        {
            if (!(cards->at(idx).value == startVal))
            {
                unusedCards.push_back(cards->at(idx));
                cards->erase(cards->begin() + idx);
            }
        }
        sort(unusedCards.begin(), unusedCards.end());
        for (int idx = 0; idx < unusedCards.size(); ++idx)
        {
            cards->push_back(unusedCards.back());
            unusedCards.pop_back();
        }
    }

    return foundFOAK;
}

bool Scorer::hasFullHouse(vector<Card>* cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    bool foundFF = false;
    Card::Value pair = Card::Value::Invalid;
    Card::Value triple = Card::Value::Invalid;
    if (cards->at(0).value == cards->at(1).value)
    {
        if (cards->at(1).value == cards->at(2).value)
        {
            triple = cards->at(0).value;
        }
        else
        {
            pair = cards->at(0).value;
        }

        if (!(pair == Card::Value::Invalid))
        {
            if (cards->at(2).value == cards->at(3).value &&
                cards->at(3).value == cards->at(4).value)
            {
                foundFF = true;
                triple = cards->at(2).value;
                cards->push_back(cards->front());
                cards->erase(cards->begin());
                cards->push_back(cards->front());
                cards->erase(cards->begin());
            }
        }
        else if (!(triple == Card::Value::Invalid))
        {
            if (cards->at(3).value == cards->at(4).value)
            {
                foundFF = true;
                pair = cards->at(3).value;
            }
        }
    }
    return foundFF;
}