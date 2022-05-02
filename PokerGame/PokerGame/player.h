/// @file
/// @author Nathan Roe
#pragma once
#include "hand.h"

class Game;

/// Abstract Player class representing Poker player
/// 
/// Handles money, betting and discards for 5-Card
/// draw poker. Card information inherited from Hand
class Player : public Hand
{
public:
    /// Player constructor
    /// @param *game - Pointer to poker Game object
    /// @param buIn - Starting money value
    Player(Game *game, int buyIn);

    /// Player destructor
    virtual ~Player();

    /// Remove all cards from hand
    void discardHand();

    /// Check whether player has funds
    /// Returns True if player has no money, false otherwise
    bool isBroke() { return this->money <= 0; };

    /// Getter for amount of money remaining
    /// Returns an int of remaining money
    int getRemainingFunds() { return this->money; };

    /// Get a bet for a betting round in Poker
    /// @param prevRaise - Last raise value, min for calling
    /// @param minBet - Minimum allowed bet, used for blinds
    /// Returns an int of the Player's bet
    virtual int getBet(int prevRaise, int minBet = 0) = 0;

    /// Adds Winnings to the Player's pool of funds
    /// @param winnings - amount of money won in round
    void addWinnings(int winnings) { this->money += winnings; };

    /// Choose which cards to discard for draw phase of 5-Card draw
    /// @param maxDiscard - Maximum cards that are availible to draw
    /// Returns the number of cards discarded
    virtual int chooseDiscard(int maxDiscard) = 0;

protected:
    Game *game;
    int money = 0;
};

