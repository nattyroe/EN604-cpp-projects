#include "player.h"
#include "card.h"

/// Abstract Player class representing Poker player
Player::Player(Game *game, int buyIn)
{
    this->game = game;
    this->money = buyIn;
} // End Player constructor

/// Default Player destructor
Player::~Player()
{
    return;
} // End Player destructor

/// Discard all cards in hand
void Player::discardHand()
{
    while (!this->cards.empty())
    {
        const Card card = this->cards.front();
        discard(&card);
    }
} // End function discardHand
