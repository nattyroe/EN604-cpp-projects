#include "Scorer.h"
#include "hand.h"
#include "card.h"
#include <vector>
#include <algorithm>

using namespace std;

int Scorer::findBestHand(vector<Hand> *hands)
{
    if (hands->size() < 2)
    {
        return -1;
    }

    int numTied = 0;
    Hand *bestHand = &hands->at(0);
    for (int idx = 1; idx < hands->size(); ++idx)
    {
        int result = compareHands(*bestHand, hands->at(idx));
        if (result == 0)
        {
            ++numTied;
            Hand hand = hands->at(idx);
            hands->erase(hands->begin() + idx);
            hands->insert(hands->begin() + numTied, hand);
        }
        else if (result == 1)
        {
            numTied = 0;
        }
        else if (result == 2)
        {
            numTied = 0;
            Hand hand = hands->at(idx);
            hands->erase(hands->begin() + idx);
            hands->insert(hands->begin(), hand);
        }
        else
        {
            return -1;
        }
    }
    return numTied;
}

int Scorer::compareHands(Hand hand1, Hand hand2)
{
    if (!(hand1.size() == HAND_SIZE) ||
        !(hand2.size() == HAND_SIZE))
    {
        return -1;
    }

    vector<Card> cards1 = checkHandType(&hand1);
    vector<Card> cards2 = checkHandType(&hand2);

    if (hand1.getHandType() == Hand::HandType::None ||
        hand2.getHandType() == Hand::HandType::None)
    {
        return -1;
    }

    int result = -1;

    if (hand1.getHandType() > hand2.getHandType())
    {
        result = 1;
    }
    else if (hand1.getHandType() < hand2.getHandType())
    {
        result = 2;
    }
    else
    {
        for (int idx = 0; idx < HAND_SIZE; ++idx)
        {
            if (cards1.at(idx) > cards2.at(idx))
            {
                result = 1;
                break;
            }
            else if (cards1.at(idx) < cards2.at(idx))
            {
                result = 2;
                break;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

vector<Card> Scorer::checkHandType(Hand *hand)
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
    else if (hasFlush(&cards))
    {
        hand->setHandType(Hand::HandType::Flush);
    }
    else if (hasStraight(&cards))
    {
        hand->setHandType(Hand::HandType::Straight);
    }
    else if (hasThreeOfAKind(&cards))
    {
        hand->setHandType(Hand::HandType::ThreeOfAKind);
    }
    else if (hasTwoPair(&cards))
    {
        hand->setHandType(Hand::HandType::TwoPair);
    }
    else if (hasOnePair(&cards))
    {
        hand->setHandType(Hand::HandType::OnePair);
    }
    else if (hasHighCard(&cards))
    {
        hand->setHandType(Hand::HandType::HighCard);
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

bool Scorer::hasFourOfAKind(vector<Card> *cards)
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

bool Scorer::hasFullHouse(vector<Card> *cards)
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

bool Scorer::hasFlush(vector<Card> *cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    Card::Suit startSuit = cards->at(0).suit;
    for (int idx = 1; idx < cards->size(); ++idx)
    {
        Card::Suit cardSuit = cards->at(idx).suit;
        if (!(cards->at(idx).isValid()) ||
            !(cardSuit == startSuit))
        {
            return false;
        }
    }

    return true;
}

bool Scorer::hasStraight(vector<Card> *cards)
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
        for (int idx = 2; idx < cards->size(); ++idx)
        {
            int cardVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(idx).value);
            if (!(cards->at(idx).isValid()) ||
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
        for (int idx = 1; idx < cards->size(); ++idx)
        {
            int cardVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(idx).value);
            if (!(cards->at(idx).isValid()) ||
                !(cardVal == startVal-- - 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool Scorer::hasThreeOfAKind(vector<Card> *cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    int TOAK = 3;
    int foundTOAK = false;
    Card::Value startVal = Card::Value::Invalid;
    for (int idx = 0; idx <= cards->size() - TOAK; ++idx)
    {
        foundTOAK = true;
        startVal = cards->at(idx).value;
        for (int innerIdx = idx + 1; innerIdx < idx + TOAK; ++innerIdx)
        {
            Card::Value cardVal = cards->at(innerIdx).value;
            if (!(cards->at(innerIdx).isValid()) ||
                !(startVal == cardVal))
            {
                foundTOAK = false;
                break;
            }
        }
        if (foundTOAK)
        {
            break;
        }
    }

    if (foundTOAK)
    {
        vector<Card> unusedCards;
        int cardsMoved = 0;
        for (int idx = 0; idx < HAND_SIZE; ++idx)
        {
            int cardIdx = idx - cardsMoved;
            if (!(cards->at(cardIdx).value == startVal))
            {
                unusedCards.push_back(cards->at(cardIdx));
                cards->erase(cards->begin() + cardIdx);
                ++cardsMoved;
            }
        }
        sort(unusedCards.begin(), unusedCards.end());
        size_t startSize = unusedCards.size();
        for (int idx = 0; idx < startSize; ++idx)
        {
            cards->push_back(unusedCards.back());
            unusedCards.pop_back();
        }
    }

    return foundTOAK;
}

bool Scorer::hasTwoPair(vector<Card> *cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    bool foundTP = false;
    vector<Card> pair1;
    vector<Card> pair2;

    for (int idx = 1; idx < cards->size(); ++idx)
    {
        int prevIdx = idx - 1;
        Card *card = &cards->at(idx);
        Card *prevCard = &cards->at(prevIdx);
        if (card->value == prevCard->value)
        {
            foundTP = true;
            pair1.push_back(*prevCard);
            pair1.push_back(*card);
            cards->erase(cards->begin() + prevIdx);
            cards->erase(cards->begin() + prevIdx);
            break;
        }
    }

    if (foundTP)
    {
        foundTP = false;
        for (int idx = 1; idx < cards->size(); ++idx)
        {
            int prevIdx = idx - 1;
            Card *card = &cards->at(idx);
            Card *prevCard = &cards->at(prevIdx);
            if (card->value == prevCard->value)
            {
                foundTP = true;
                pair2.push_back(*prevCard);
                pair2.push_back(*card);
                cards->erase(cards->begin() + prevIdx);
                cards->erase(cards->begin() + prevIdx);
            }
        }
    }

    if (foundTP)
    {
        if (pair1.front().value > pair2.front().value)
        {
            cards->push_back(pair1.front());
            cards->push_back(pair1.back());
            cards->push_back(pair2.front());
            cards->push_back(pair2.back());
        }
        else
        {
            cards->push_back(pair2.front());
            cards->push_back(pair2.back());
            cards->push_back(pair1.front());
            cards->push_back(pair1.back());
        }
        cards->push_back(cards->front());
        cards->erase(cards->begin());
    }
    else if (pair1.size() > 0)
    {
        cards->push_back(pair1.front());
        cards->push_back(pair1.back());
    }

    return foundTP;
}

bool Scorer::hasOnePair(vector<Card> *cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    bool foundPair = false;
    vector<Card> pair;

    for (int idx = 1; idx < cards->size(); ++idx)
    {
        int prevIdx = idx - 1;
        Card *card = &cards->at(idx);
        Card *prevCard = &cards->at(prevIdx);
        if (card->value == prevCard->value)
        {
            foundPair = true;
            pair.push_back(*prevCard);
            pair.push_back(*card);
            cards->erase(cards->begin() + prevIdx);
            cards->erase(cards->begin() + prevIdx);
        }
    }

    if (foundPair)
    {
        cards->insert(cards->begin(), pair.front());
        cards->insert(cards->begin(), pair.back());
    }

    return foundPair;
}

bool Scorer::hasHighCard(vector<Card> *cards)
{
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    return true;
}
