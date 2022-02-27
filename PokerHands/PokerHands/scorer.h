#pragma once
#include <vector>

class Card;
class Hand;

using namespace std;

// @file
// @author Nathan Roe
// Class to assess and find winner for set of Poker Hands.
//
// Given a set of hands, will evaluate the Poker Hand Type
// and determine the winner or winners.
class Scorer
{
public:
    // Evaluates a set of hands to determine winner(s)
    //
    // Accepts a vector of Hands and moves winner or
    //    winners to the front of the vector. The return
    //    value indicates the last index of a winner.
    //    One winner returns 0, two-way tie returns 1, etc.
    //    Returns -1 for error
    // @param *hands - pointer to vector of Hands to evaluate and rank
    // @return the index of the final winner in the partially
    //     sorted vector
    int findBestHand(vector<Hand> *hands);

    // Determines and sets the HandType for a given poker hand
    //
    // @param *hand - Hand for which to set HandType
    // @return vector of Cards sorted for comparison based on HandType
    vector<Card> checkHandType(Hand *hand);

private:
    const int HAND_SIZE = 5;

    // Compare two Hands to determine which is better
    //
    // @param hand1 - First Hand for comparing
    // @param hand2 - Second Hand for comparing
    // @return 1 for hand1, 2 for hand2, 0 for tie,
    //    or -1 for error
    int compareHands(Hand *hand1, Hand *hand2);

    // Check hand for presence of Straight Flush
    //
    // If type is present, sort cards for comparison to
    // similar sets of cards
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasStraightFlush(vector<Card> *cards);

    // Check hand for presence of Four of a Kind
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasFourOfAKind(vector<Card> *cards);

    // Check hand for presence of Full House
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasFullHouse(vector<Card> *cards);

    // Check hand for presence of Flush
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasFlush(vector<Card> *cards);

    // Check hand for presence of Straight
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasStraight(vector<Card> *cards);

    // Check hand for presence of Three of a Kind
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasThreeOfAKind(vector<Card> *cards);

    // Check hand for presence of Two Pair
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasTwoPair(vector<Card> *cards);

    // Check hand for presence of One Pair
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasOnePair(vector<Card> *cards);

    // Check hand for presence of High Card
    //
    // If type is present, sort cards for comparison
    // @param *cards - pointer to vector of cards to check
    // @return true if hand type is present, false otherwise
    bool hasHighCard(vector<Card> *cards);
};
