#include "game.h"
#include "deck.h"
#include "player.h"
#include "pc.h"
#include "npc.h"
#include "Scorer.h"
#include <iostream>

Game::Game(int numHumans, int numComputers, int buyIn, int blind)
{
    int numPlayers = numHumans + numComputers;
    if (numPlayers < MIN_PLAYERS ||
        numPlayers > MAX_PLAYERS)
    {
        throw InvalidGameException(numPlayers);
    }

    for (int num = 0; num < numHumans; ++num)
    {
        Player *player = new PC(this, buyIn);
        this->players.push_back(player);
    }
    for (int num = 0; num < numComputers; ++num)
    {
        Player *player = new NPC(this, buyIn);
        this->players.push_back(player);
    }

    this->blind = blind;
    this->scorer = new Scorer();
    this->deck = new Deck();
}

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

        // Betting rounds
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
}

void Game::dropPlayers()
{
    // Remove Players who folded
    vector<Player*>::iterator iter = this->remainingPlayers.begin();
    vector<BetType>::iterator betIter = this->betTypes.begin();
    vector<int>::iterator cashIter = this->amountIn.begin();
    while (iter != this->remainingPlayers.end())
    {
        BetType b = *betIter;
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
}

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
}

void Game::conductBets(bool requireBlinds)
{
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

    while (true)
    {
        if (!(this->betTypes[playerIdx] == BetType::FOLD ||
              this->betTypes[playerIdx] == BetType::ALL_IN))
        {
            p = this->remainingPlayers[playerIdx];
            amountToCall = baseBet - this->amountIn[playerIdx];
            bet = p->getBet(amountToCall);
            pot += bet;
            if (bet >= amountToCall)
            {
                baseBet += (bet - amountToCall);
            }
            this->amountIn[playerIdx] += bet;
            if (bet == amountToCall)
            {
                this->betTypes[playerIdx] = BetType::CALL;
                cout << "Player " << p << " Calls" << endl << endl;
            }
            else if (p->getRemainingFunds() == 0)
            {
                this->betTypes[playerIdx] = BetType::ALL_IN;
                cout << "Player " << p << " is All In" << endl << endl;
            }
            else if (bet == 0)
            {
                this->betTypes[playerIdx] = BetType::FOLD;
                cout << "Player " << p << " Folds" << endl << endl;
            }
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
}

void Game::discardRound()
{
    int discardingPlayers = this->remainingPlayers.size();
    int remainingCards = this->deck->cardsRemaining();
    int playerIdx = 0;
    int discard = 0;
    Player *p;
    for (int idx = 0; idx < discardingPlayers; ++idx)
    {
        playerIdx = (this->blindIdx + idx) % discardingPlayers;
        p = this->remainingPlayers.at(playerIdx);
        discard = p->chooseDiscard(remainingCards);
        cout << "Player " << p << " discarded " << discard << " cards" << endl << endl;
        for (int n = 0; n < discard; n++)
        {
            p->deal(this->deck->deal());
        }
    }
}

void Game::scoreRound()
{
    int winIdx = -1;
    vector<Hand*> temp(this->remainingPlayers.begin(), this->remainingPlayers.end());
    for (Player *p : this->remainingPlayers)
    {
        cout << "Player " << p << "'s hand: " << p->printCards() << endl;
    }

    if (this->remainingPlayers.size() > 1)
    {
        winIdx = this->scorer->findBestHand(&temp);
    }

    if (this->remainingPlayers.size() == 1)
    {
        int idx = 0;
        Player* p = static_cast<Player*>(temp[idx]);
        p->addWinnings(this->pot);
        cout << "Player " << p << " Wins $" << this->pot << endl << endl;
        this->pot = 0;
    }
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
}
