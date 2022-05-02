/// @file
/// @author Nathan Roe
#pragma once
#include "player.h"

class Game;

/// Player class representing Computer Poker player
class NPC : public Player
{
public:
    /// Computer Player constructor
    /// @param *game - Pointer to poker Game object
    /// @param buIn - Starting money value
    NPC(Game *game, int buyIn) : Player(game, buyIn) {};

    /// Get a bet for a betting round in Poker
    /// @param prevRaise - Last raise value, min for calling
    /// @param minBet - Minimum allowed bet, used for blinds
    /// Returns an int of the Player's bet
    int getBet(int prevRaise, int minBet = 0);

    /// Choose which cards to discard for draw phase of 5-Card draw
    /// @param maxDiscard - Maximum cards that are availible to draw
    /// Returns the number of cards discarded
    int chooseDiscard(int maxDiscard);
};
