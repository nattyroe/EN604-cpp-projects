#include "Hand/card.hpp"
#include "Hand/hand.hpp"

int main()
{
    Hand *hand = new Hand();
    hand->deal(Card(Card::Value::Eight, Card::Suit::Clubs));
    hand->deal(Card(Card::Value::Ace, Card::Suit::Clubs));
    hand->deal(Card(Card::Value::Three, Card::Suit::Diamonds));
    hand->deal(Card(Card::Value::Three, Card::Suit::Diamonds));

    hand->printCards();

    return 0;
}