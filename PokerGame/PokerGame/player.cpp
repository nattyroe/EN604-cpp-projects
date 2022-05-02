#include "player.h"
#include "card.h"

Player::Player(Game *game, int buyIn)
{
    this->game = game;
    this->money = buyIn;
}

Player::~Player()
{
    return;
}

void Player::discardHand()
{
    while (!this->cards.empty())
    {
        const Card card = this->cards.front();
        discard(&card);
    }
}
