#pragma once
#include <stdexcept>
#include <string>
#include <vector>

class Player;
class Deck;
class Scorer;

using namespace std;

class Game
{
public:
    Game(int numPlayers, int numComputers, int buyIn, int blind);

    class InvalidGameException : public std::runtime_error
    {
    public:
        InvalidGameException(int playerCount)
            : std::runtime_error("NumPlayers must be between 2 and 7, " 
                                 + to_string(playerCount) 
                                 + " were given") {}
    };

    void playGame();

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

    void dealCards();
    void conductBets(bool requireBlinds);
    void dropPlayers();
    void discardRound();
    void scoreRound();
};

