/// @file
/// @author Nathan Roe
#pragma once
#include <stdexcept>
#include <string>
#include <vector>

class Player;
class Deck;
class Scorer;

using namespace std;

/// Game object for playing a game of 5-Card Draw Poker
/// 
/// Main game loop is played using playGame(), and there
/// can be a total of 7 players, either PCs or NPCs
class Game
{
public:
    /// Game constructor
    /// @param numPlayers - number of Human players (PCs)
    /// @param numComputers - number of Computer players (NPCs)
    /// @param buyIn - starting money amount for each player
    /// @param blind - Min starting bet for each round
    Game(int numPlayers, int numComputers, int buyIn, int blind);

    /// Error thrown when too many or too few players required
    class InvalidGameException : public std::runtime_error
    {
    public:
        InvalidGameException(int playerCount)
            : std::runtime_error("NumPlayers must be between 2 and 7, " 
                                 + to_string(playerCount) 
                                 + " were given") {}
    };

    /// Start main game loop (Bet, Draw, Bet, Score)
    /// 
    /// Plays a game of Poker on loop until only 1
    /// player remains with money
    void playGame();

    /// Getter for current amount of money in the pot
    /// Returns the amount of money in the pot
    int getCurrentPot() { return this->pot; };

private:
    const int MIN_PLAYERS = 2;
    const int MAX_PLAYERS = 7;

    enum class BetType
    {
        NONE,
        FOLD,
        CALL,
        RAISE,
        ALL_IN
    };

    vector<Player*> players;
    vector<Player*> remainingPlayers;
    vector<BetType> betTypes;
    vector<int> amountIn;

    Deck *deck;
    Scorer *scorer;

    int pot = 0;
    int blind = 0;
    int blindIdx = 0;

    /// Deal 5 cards to each player
    void dealCards();

    /// Run a round of bets
    /// 
    /// Runs betting until all players have called, folded,
    /// or are all in
    /// @param requireBlinds - indicates whether minimum
    ///    bet values should be used in the round (True
    ///    during the first round
    void conductBets(bool requireBlinds);

    /// Remove players from the round who have folded
    void dropPlayers();

    /// Handle round for redraws
    void discardRound();

    /// Score players who are still in, and distribute winnings
    void scoreRound();
};

