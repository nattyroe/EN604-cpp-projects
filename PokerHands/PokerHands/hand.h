#pragma 
#include <string>
#include <vector>

class string;
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
    std::string printCards();
    int size();
    void setHandType(HandType handType);
    HandType getHandType();
    std::vector<Card> getCards();

private:
    std::vector<Card> cards;
    HandType handType = HandType::None;
};