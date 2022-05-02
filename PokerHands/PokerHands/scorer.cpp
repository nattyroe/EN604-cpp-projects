#include "scorer.h"
#include "hand.h"
#include "card.h"
#include <vector>
#include <algorithm>

using namespace std;

// Evaluates a set of hands to determine winner(s)
int Scorer::findBestHand(vector<Hand*> *hands)
{
    // Return error if not enough hands to score
    if (hands->size() < 2)
    {
        return -1;
    }

    int numTied = 0;
    // Begin with first hand as current best
    Hand *bestHand = hands->at(0);
    // Compare remaining hands to the current best hand
    for (int idx = 1; idx < hands->size(); ++idx)
    {
        int result = compareHands(bestHand, hands->at(idx));
        // If hands tie, move new hand to front section of vector
        if (result == 0)
        {
            ++numTied;
            Hand *hand = hands->at(idx);
            hands->erase(hands->begin() + idx);
            hands->insert(hands->begin() + numTied, hand);
        }
        // If current best hand is better, leave vector unchanged
        else if (result == 1)
        {
            continue;
        }
        // If new hand is better, move to front and reset number of ties
        else if (result == 2)
        {
            numTied = 0;
            Hand *hand = hands->at(idx);
            hands->erase(hands->begin() + idx);
            hands->insert(hands->begin(), hand);
        }
        // Return error for unexpected value
        else
        {
            return -1;
        }
    }
    return numTied;
} // End function findBestHand

// Compare two Hands to determine which is better
int Scorer::compareHands(Hand *hand1, Hand *hand2)
{
    // If hands are not sets of 5 cards, return error
    if (!(hand1->size() == HAND_SIZE) ||
        !(hand2->size() == HAND_SIZE))
    {
        return -1;
    }

    // Check type of each hand, and prep cards for comparison
    vector<Card> cards1 = checkHandType(hand1);
    vector<Card> cards2 = checkHandType(hand2);

    // Verify that each hand is a valid Poker Hand Type
    if (hand1->getHandType() == Hand::HandType::None ||
        hand2->getHandType() == Hand::HandType::None)
    {
        return -1;
    }

    int result = -1;

    // Check to see if one Hand is a higher rank than the other
    if (hand1->getHandType() > hand2->getHandType())
    {
        result = 1;
    }
    else if (hand1->getHandType() < hand2->getHandType())
    {
        result = 2;
    }
    // If hands are of same rank, compare cards to find best hand
    else
    {
        // Since hands are pre-sorted, iterate through cards until
        // a higher card is found
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
            // If all cards are of same value, return tie
            else
            {
                result = 0;
            }
        }
    }
    return result;
} // End function compareHands

// Determines and sets the HandType for a given poker hand
vector<Card> Scorer::checkHandType(Hand *hand)
{
    vector<Card> cards = hand->getCards();
    // Verify that all cards in the hand are valid
    for (Card card : cards)
    {
        if (!card.isValid())
        {
            return cards;
        }
    }

    // Test hand against Poker Hand Types from Best to Worst
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
    // If no valid hand type is found, assign None
    else
    {
        hand->setHandType(Hand::HandType::None);
    }

    // Return vector of cards sorted for comparison based on HandType
    return cards;
} // End function checkHandType

// Check hand for presence of Straight Flush
bool Scorer::hasStraightFlush(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards from high to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    // Special case for Ace-Low
    if (cards->at(0).value == Card::Value::Ace &&
        cards->at(1).value == Card::Value::Five)
    {
        // Set starting card value/suit to the 5
        int startVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(1).value);
        Card::Suit startSuit = cards->at(0).suit;
        // Iterate through remaining cards, and exit if not in
        // descending order and matching suit
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
        // Move ace to end
        Card ace = cards->front();
        cards->erase(cards->begin());
        cards->push_back(ace);
    }
    // Check Cases with no Aces
    else
    {
        // Set starting card value/suit
        int startVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(0).value);
        Card::Suit startSuit = cards->at(0).suit;
        // Iterate through remaining cards, and exit if not in
        // descending order and matching suit
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
} // End function hasStraightFlush

// Check hand for presence of Four of a Kind
bool Scorer::hasFourOfAKind(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards from hight to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    int FOAK = 4;
    int foundFOAK = false;
    Card::Value startVal = Card::Value::Invalid;
    // Test cards in sets (1-4) and (2-5) to see if all values match
    for (int idx = 0; idx <= cards->size() - FOAK; ++idx)
    {
        foundFOAK = true;
        startVal = cards->at(idx).value;
        // Iterate over 3 following cards and check for match
        for (int innerIdx = idx + 1; innerIdx < idx + FOAK; ++innerIdx)
        {
            Card::Value cardVal = cards->at(innerIdx).value;
            // If different value is found, no FOAK
            if (!(cards->at(innerIdx).isValid()) ||
                !(startVal == cardVal))
            {
                foundFOAK = false;
                break;
            }
        }
        // If first four cards are FOAK, break loop
        if (foundFOAK)
        {
            break;
        }
    }

    // If cards have FOAK, sort matching cards to the front
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
        // Sort non-FOAK cards low to high
        sort(unusedCards.begin(), unusedCards.end());
        // Put unused cards at the end of card set from
        // hight to low
        for (int idx = 0; idx < unusedCards.size(); ++idx)
        {
            cards->push_back(unusedCards.back());
            unusedCards.pop_back();
        }
    }

    return foundFOAK;
} // End function hasFourOfAKind

// Check hand for presence of Full House
bool Scorer::hasFullHouse(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    bool foundFF = false;
    Card::Value pair = Card::Value::Invalid;
    Card::Value triple = Card::Value::Invalid;
    // Check wether first two cards match
    if (cards->at(0).value == cards->at(1).value)
    {
        // If first two cards match, check whether
        // first three cards make a set of 3
        if (cards->at(1).value == cards->at(2).value)
        {
            triple = cards->at(0).value;
        }
        // Otherwise, set pair value as value of first card
        else
        {
            pair = cards->at(0).value;
        }

        if (!(pair == Card::Value::Invalid))
        {
            // If first two cards are a pair, check remaining
            // cards to see if they make a set of 3
            if (cards->at(2).value == cards->at(3).value &&
                cards->at(3).value == cards->at(4).value)
            {
                foundFF = true;
                triple = cards->at(2).value;
                // Move set of 3 to the front
                cards->push_back(cards->front());
                cards->erase(cards->begin());
                cards->push_back(cards->front());
                cards->erase(cards->begin());
            }
        }
        else if (!(triple == Card::Value::Invalid))
        {
            // If first three cards make a set of 3, check
            // remaining cards to see if they are a pair
            if (cards->at(3).value == cards->at(4).value)
            {
                foundFF = true;
                pair = cards->at(3).value;
            }
        }
    }
    return foundFF;
} // End function hasFullHouse

// Check hand for presence of Flush
bool Scorer::hasFlush(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards from high to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    Card::Suit startSuit = cards->at(0).suit;
    // Iterate through cards to check whether suits match
    for (int idx = 1; idx < cards->size(); ++idx)
    {
        Card::Suit cardSuit = cards->at(idx).suit;
        // If different suit is found, return false
        if (!(cards->at(idx).isValid()) ||
            !(cardSuit == startSuit))
        {
            return false;
        }
    }

    return true;
} // End function hasFlush

// Check hand for presence of Straight
bool Scorer::hasStraight(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards high to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    // Special case for Ace-Low
    if (cards->at(0).value == Card::Value::Ace &&
        cards->at(1).value == Card::Value::Five)
    {
        // Set highest card as the 5
        int startVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(1).value);
        for (int idx = 2; idx < cards->size(); ++idx)
        {
            int cardVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(idx).value);
            // Iterate through remaining cards to see if they are consecutive
            if (!(cards->at(idx).isValid()) ||
                !(cardVal == startVal-- - 1))
            {
                return false;
            }
        }
        // Move Ace to the back
        Card ace = cards->front();
        cards->erase(cards->begin());
        cards->push_back(ace);
    }
    // Check Cases with no Aces
    else
    {
        // Set starting card value
        int startVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(0).value);
        for (int idx = 1; idx < cards->size(); ++idx)
        {
            int cardVal = static_cast<typename std::underlying_type<Card::Value>::type>(cards->at(idx).value);
            // Iterate through remaining cards to see if they are consecutive
            if (!(cards->at(idx).isValid()) ||
                !(cardVal == startVal-- - 1))
            {
                return false;
            }
        }
    }
    return true;
} // End function hasStraight

// Check hand for presence of Three of a Kind
bool Scorer::hasThreeOfAKind(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards high to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    int TOAK = 3;
    int foundTOAK = false;
    Card::Value startVal = Card::Value::Invalid;
    // Check (1-3), (2-4), (3-5) for three of a kind
    for (int idx = 0; idx <= cards->size() - TOAK; ++idx)
    {
        foundTOAK = true;
        startVal = cards->at(idx).value;
        // Compare three consecutive cards for matching values
        for (int innerIdx = idx + 1; innerIdx < idx + TOAK; ++innerIdx)
        {
            Card::Value cardVal = cards->at(innerIdx).value;
            // If different value is found, move to next set of 3
            if (!(cards->at(innerIdx).isValid()) ||
                !(startVal == cardVal))
            {
                foundTOAK = false;
                break;
            }
        }
        // End search if three of a kind is found
        if (foundTOAK)
        {
            break;
        }
    }

    // If three of a kind is found, sort cards for comparison
    if (foundTOAK)
    {
        vector<Card> unusedCards;
        int cardsMoved = 0;
        // Remove cards that are not part of TOAK
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
        // Place non-TOAK cards from high-low and end of cards
        sort(unusedCards.begin(), unusedCards.end());
        size_t startSize = unusedCards.size();
        for (int idx = 0; idx < startSize; ++idx)
        {
            cards->push_back(unusedCards.back());
            unusedCards.pop_back();
        }
    }

    return foundTOAK;
} // End function hasThreeOfAKind

// Check hand for presence of Two Pair
bool Scorer::hasTwoPair(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards from high to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    bool foundTP = false;
    vector<Card> pair1;
    vector<Card> pair2;

    // Search cards for a pair
    for (int idx = 1; idx < cards->size(); ++idx)
    {
        int prevIdx = idx - 1;
        Card *card = &cards->at(idx);
        Card *prevCard = &cards->at(prevIdx);
        // If pair is found, store cards
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

    // If pair is found, search remaining cards for second pair
    if (foundTP)
    {
        foundTP = false;
        for (int idx = 1; idx < cards->size(); ++idx)
        {
            int prevIdx = idx - 1;
            Card *card = &cards->at(idx);
            Card *prevCard = &cards->at(prevIdx);
            // If pair is found, store cards
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

    // If two-pair found, sort cards highPair-lowPair-spareCard
    if (foundTP)
    {
        // Place pairs in set highest to lowest
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
        // Move spare card to the end
        cards->push_back(cards->front());
        cards->erase(cards->begin());
    }
    // Place unused pair back into card set
    else if (pair1.size() > 0)
    {
        cards->push_back(pair1.front());
        cards->push_back(pair1.back());
    }

    return foundTP;
} // End function foundTwoPair

// Check hand for presence of One Pair
bool Scorer::hasOnePair(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    bool foundPair = false;
    vector<Card> pair;

    // Search cards for pair of equal value
    for (int idx = 1; idx < cards->size(); ++idx)
    {
        int prevIdx = idx - 1;
        Card *card = &cards->at(idx);
        Card *prevCard = &cards->at(prevIdx);
        // If pair is found, store pair
        if (card->value == prevCard->value)
        {
            foundPair = true;
            pair.push_back(*prevCard);
            pair.push_back(*card);
            cards->erase(cards->begin() + prevIdx);
            cards->erase(cards->begin() + prevIdx);
            break;
        }
    }

    // If pair is found, place pair at front of cards
    if (foundPair)
    {
        cards->insert(cards->begin(), pair.front());
        cards->insert(cards->begin(), pair.back());
    }

    return foundPair;
} // End function hasOnePair

// Check hand for presence of High Card
bool Scorer::hasHighCard(vector<Card> *cards)
{
    // Return false if vector is not 5 cards
    if (!(cards->size() == HAND_SIZE))
    {
        return false;
    }

    // Sort cards from high to low
    sort(cards->begin(), cards->end());
    reverse(cards->begin(), cards->end());

    return true;
} // End function hasHighCard
