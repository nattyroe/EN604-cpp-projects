#include "game.h"
#include "deck.h"
#include "player.h"
#include "pc.h"
#include "npc.h"
#include "Scorer.h"
#include <iostream>

/// Game object for playing a game of 5-Card Draw Poker
Game::Game(int numHumans, int numComputers, int buyIn, int blind)
{
    int numPlayers = numHumans + numComputers;
    if (numPlayers < MIN_PLAYERS ||
        numPlayers > MAX_PLAYERS)
    {
        throw InvalidGameException(numPlayers);
    }

    // Add PCs
    for (int num = 0; num < numHumans; ++num)
    {
        Player *player = new PC(this, buyIn);
        this->players.push_back(player);
    }
    // Add NPCs
    for (int num = 0; num < numComputers; ++num)
    {
        Player *player = new NPC(this, buyIn);
        this->players.push_back(player);
    }

    this->blind = blind;
    this->scorer = new Scorer();
    this->deck = new Deck();
} // End Game constructor

/// Start main game loop (Bet, Draw, Bet, Score)
void Game::playGame()
{
    while (players.size() > 1)
    {
        // Setup Current Players
        vector<Player*>::iterator iter = this->players.begin();
        while (iter != this->players.end())
        {
            this->remainingPlayers.push_back(*iter++);
        }
        vector<BetType> startBet(this->remainingPlayers.size(), BetType::NONE);
        this->betTypes = startBet;
        vector<int> startCash(this->remainingPlayers.size(), 0);
        this->amountIn = startCash;

        // Deal out initial cards
        dealCards();

        // Accept first round of bets
        conductBets(true);
        dropPlayers();

        // Let players redraw
        discardRound();

        // Betting round, no blinds
        vector<BetType> newBets(this->remainingPlayers.size(), BetType::NONE);
        this->betTypes = newBets;
        conductBets(false);
        dropPlayers();

        // Score round
        scoreRound();

        // Discard hands at end of round
        for (Player *player : this->players)
        {
            player->discardHand();
        }
        this->remainingPlayers.clear();

        // Remove Players who lost
        iter = this->players.begin();
        while (iter != this->players.end())
        {
            Player *p = *iter;
            if (p->isBroke())
            {
                cout << "Player " << p << " is out of funds." << endl;
                iter = this->players.erase(iter);
            }
            else
            {
                ++iter;
            }
        }

        // Increment Blind position player
        ++this->blindIdx;
        this->blindIdx %= this->players.size();
    }
} // End function playGame

// Remove players from the round who have folded
void Game::dropPlayers()
{
    vector<Player*>::iterator iter = this->remainingPlayers.begin();
    vector<BetType>::iterator betIter = this->betTypes.begin();
    vector<int>::iterator cashIter = this->amountIn.begin();
    while (iter != this->remainingPlayers.end())
    {
        BetType b = *betIter;
        // Remove Players who folded
        if (b == BetType::FOLD)
        {
            iter = this->remainingPlayers.erase(iter);
            betIter = this->betTypes.erase(betIter);
            cashIter = this->amountIn.erase(cashIter);
        }
        else
        {
            ++iter;
            ++betIter;
            ++cashIter;
        }
    }
} // End function dropPlayers

// Deal 5 cards to each player
void Game::dealCards()
{
    this->deck->shuffle();
    const int NUM_CARDS = 5;
    for (int n = 0; n < NUM_CARDS; n++)
    {
        for (Player *player : this->players)
        {
            player->deal(this->deck->deal());
        }
    }
} // End function dealCards

// Run a round of bets
void Game::conductBets(bool requireBlinds)
{
    // Exit if too few players
    if (this->remainingPlayers.size() < 2)
    {
        return;
    }

    int playerIdx = this->blindIdx;
    playerIdx %= this->remainingPlayers.size();
    int bet = 0;
    int baseBet = this->amountIn[playerIdx];
    int amountToCall = 0;
    Player *p;

    if (requireBlinds)
    {
        // Handle Small Blind
        p = this->remainingPlayers[playerIdx];
        cout << "Player " << p << " is the Small Blind" << endl;
        bet = p->getBet(0, this->blind);
        cout << "Player " << p << " bet $" << bet << endl << endl;
        pot += bet;
        this->amountIn[playerIdx] += bet;
        // Handle scenario when player can't afford small blind
        if (bet < this->blind)
        {
            this->betTypes[playerIdx] = BetType::ALL_IN;
        }
        else
        {
            this->betTypes[playerIdx] = BetType::RAISE;
        }
        ++playerIdx;
        playerIdx %= this->remainingPlayers.size();
        baseBet = bet;

        // Handle Big Blind
        p = this->remainingPlayers[playerIdx];
        cout << "Player " << p << " is the Big Blind" << endl;
        amountToCall = baseBet - this->amountIn[playerIdx];
        bet = p->getBet(amountToCall, 2 * this->blind);
        cout << "Player " << p << " bet $" << bet << endl << endl;
        pot += bet;
        if (bet >= amountToCall)
        {
            baseBet += (bet - amountToCall);
        }
        this->amountIn[playerIdx] += bet;
        // Handle scenario when player can't afford big blind
        if (bet < 2 * this->blind)
        {
            this->betTypes[playerIdx] = BetType::ALL_IN;
        }
        else
        {
            this->betTypes[playerIdx] = BetType::RAISE;
        }
        ++playerIdx;
        playerIdx %= this->remainingPlayers.size();
    }

    // Main betting loop
    while (true)
    {
        // Check whether player needs to bet
        if (!(this->betTypes[playerIdx] == BetType::FOLD ||
              this->betTypes[playerIdx] == BetType::ALL_IN))
        {
            p = this->remainingPlayers[playerIdx];
            // Get required bet amount to avoid folding
            amountToCall = baseBet - this->amountIn[playerIdx];
            bet = p->getBet(amountToCall);
            pot += bet;
            // See if bet is a raise or a call
            if (bet >= amountToCall)
            {
                baseBet += (bet - amountToCall);
            }
            this->amountIn[playerIdx] += bet;
            // Handle Calls
            if (bet == amountToCall)
            {
                this->betTypes[playerIdx] = BetType::CALL;
                cout << "Player " << p << " Calls" << endl << endl;
            }
            // Handle All In
            else if (p->getRemainingFunds() == 0)
            {
                this->betTypes[playerIdx] = BetType::ALL_IN;
                cout << "Player " << p << " is All In" << endl << endl;
            }
            // Handle Folds
            else if (bet == 0)
            {
                this->betTypes[playerIdx] = BetType::FOLD;
                cout << "Player " << p << " Folds" << endl << endl;
            }
            // Other bets are raises
            else
            {
                this->betTypes[playerIdx] = BetType::RAISE;
                cout << "Player " << p << " Raises $" << bet - amountToCall << endl << endl;
            }
        }

        // Check to see if bets are over
        int numRaises = 0;
        for (BetType betType : this->betTypes)
        {
            if (betType == BetType::RAISE || betType == BetType::NONE)
            {
                ++numRaises;
            }
        }
        if (numRaises == 0)
        {
            break;
        }

        ++playerIdx;
        playerIdx %= this->remainingPlayers.size();
    }
} // End function conductBets

// Handle round for redraws
void Game::discardRound()
{
    int discardingPlayers = this->remainingPlayers.size();
    // Find cards availible to redraw
    int remainingCards = this->deck->cardsRemaining();
    int playerIdx = 0;
    int discard = 0;
    Player *p;
    // Let each player discard
    for (int idx = 0; idx < discardingPlayers; ++idx)
    {
        playerIdx = (this->blindIdx + idx) % discardingPlayers;
        p = this->remainingPlayers.at(playerIdx);
        discard = p->chooseDiscard(remainingCards);
        cout << "Player " << p << " discarded " << discard << " cards" << endl << endl;
        // Deal new card for each discard
        for (int n = 0; n < discard; n++)
        {
            p->deal(this->deck->deal());
        }
    }
} // End function discardRound

// Score players who are still in, and distribute winnings
void Game::scoreRound()
{
    int winIdx = -1;
    vector<Hand*> temp(this->remainingPlayers.begin(), this->remainingPlayers.end());
    // Print player hands
    for (Player *p : this->remainingPlayers)
    {
        cout << "Player " << p << "'s hand: " << p->printCards() << endl;
    }

    // Find number of winning hands, and bring winners to front
    if (this->remainingPlayers.size() > 1)
    {
        winIdx = this->scorer->findBestHand(&temp);
    }

    // If only one player is left, give pot to player
    if (this->remainingPlayers.size() == 1)
    {
        int idx = 0;
        Player* p = static_cast<Player*>(temp[idx]);
        p->addWinnings(this->pot);
        cout << "Player " << p << " Wins $" << this->pot << endl << endl;
        this->pot = 0;
    }
    // If multiple players left, distribute winnings amongst winners
    else if (winIdx >= 0)
    {
        int winnings = this->pot / (winIdx + 1);
        for (int idx = 0; idx <= winIdx; ++idx)
        {
            Player* p = static_cast<Player*>(temp[idx]);
            p->addWinnings(winnings);
            this->pot -= winnings;
            cout << "Player " << p << " Wins $" << winnings << endl << endl;
        }
    }
} // End function scoreRound
