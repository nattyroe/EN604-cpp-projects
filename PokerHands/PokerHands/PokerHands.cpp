#include "card.h"
#include "hand.h"
#include "Scorer.h"
#include <iostream>
#include <vector>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

Card makeCard(int value, std::string suit)
{
    Card::Value cardValue = Card::Value::Invalid;
    Card::Suit cardSuit = Card::Suit::Invalid;
    try
    {
        cardValue = static_cast<Card::Value>(value);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
        cout << "Invalid Card Value: " << value << endl;
        cardValue = Card::Value::Invalid;
    }

    if (suit.size() > 0)
    {
        char cardChar = suit[0];
        switch (cardChar)
        {
        case 'C':
            cardSuit = Card::Suit::Clubs;
            break;
        case 'D':
            cardSuit = Card::Suit::Diamonds;
            break;
        case 'H':
            cardSuit = Card::Suit::Hearts;
            break;
        case 'S':
            cardSuit = Card::Suit::Spades;
            break;
        default:
            cardSuit = Card::Suit::Invalid;
            break;
        }
    }

    return Card(cardValue, cardSuit);
}

Card makeCard(std::string value, std::string suit)
{
    Card::Value cardValue = Card::Value::Invalid;
    Card::Suit cardSuit = Card::Suit::Invalid;

    if (value == "Ten" || value == "T")
    {
        cardValue = Card::Value::Ten;
    }
    else if (value == "Jack" || value == "J")
    {
        cardValue = Card::Value::Jack;
    }
    else if (value == "Queen" || value == "Q")
    {
        cardValue = Card::Value::Queen;
    }
    else if (value == "King" || value == "K")
    {
        cardValue = Card::Value::King;
    }
    else if (value == "Ace" || value == "A")
    {
        cardValue = Card::Value::Ace;
    }
    else
    {
        try
        {

            cardValue = static_cast<Card::Value>(stoi(value));
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid Card Value: " << value << endl;
            cardValue = Card::Value::Invalid;
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
            cardValue = Card::Value::Invalid;
        }
    }

    if (suit.size() > 0)
    {
        char cardChar = suit[0];
        switch (cardChar)
        {
        case 'C':
            cardSuit = Card::Suit::Clubs;
            break;
        case 'D':
            cardSuit = Card::Suit::Diamonds;
            break;
        case 'H':
            cardSuit = Card::Suit::Hearts;
            break;
        case 'S':
            cardSuit = Card::Suit::Spades;
            break;
        default:
            cardSuit = Card::Suit::Invalid;
            break;
        }
    }

    return Card(cardValue, cardSuit);
}

void printResults(int lastWinIdx, vector<Hand> *players)
{
    cout << "(" << players->at(0).printCards() << ")";
    for (int idx = 1; idx <= lastWinIdx; ++idx)
    {
        cout << ", " << "(" << players->at(idx).printCards() << ")";
    }
    if (lastWinIdx > 0)
    {
        cout << " Tie for the Win.";
    }
    else
    {
        cout << " Wins.";
    }

    bool multiLoser = false;
    for (int idx = lastWinIdx + 1; idx < players->size(); ++idx)
    {
        cout << " " << "(" << players->at(idx).printCards() << ")";
        if (idx < players->size() - 1)
        {
            multiLoser = true;
            cout << " and";
        }
    }
    if (multiLoser)
    {
        cout << " Lose.";
    }
    else
    {
        cout << " Loses.";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    Scorer *scorer = new Scorer();

    for (int idx = 1; idx < argc; ++idx)
    {
        Config *cfg = new Config();
        char *path = argv[idx];

        try
        {
            cout << path << endl;
            cfg->readFile(path);
        }
        catch (const FileIOException &fioex)
        {
            cerr << fioex.what() << " while reading file " << path << endl;
            return (EXIT_FAILURE);
        }
        catch (const ParseException &pex)
        {
            cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                 << " - " << pex.getError() << endl;
            return (EXIT_FAILURE);
        }

        vector<Hand> *players = new vector<Hand>;

        const Setting &root = cfg->getRoot();
        try
        {
            const Setting &hands = root["hands"];
            int numHands = hands.getLength();

            for (int handIdx = 0; handIdx < numHands; ++handIdx)
            {

                Hand *hand = new Hand();

                const Setting &cards = hands[handIdx];
                int numCards = cards.getLength();
                for (int cardIdx = 0; cardIdx < numCards; ++cardIdx)
                {
                    const Setting &card = cards[cardIdx];

                    std::string suit;
                    bool suitFound = false;
                    bool valueFound = false;

                    suitFound = card.lookupValue("suit", suit);
                    if (suitFound)
                    {
                        int value;
                        std::string valueString;
                        valueFound = card.lookupValue("value", value);
                        if (valueFound)
                        {
                            Card card = makeCard(value, suit);
                            if (card.isValid())
                            {
                                hand->deal(card);
                            }
                        }
                        else
                        {
                            valueFound = card.lookupValue("value", valueString);
                            if (valueFound)
                            {
                                Card card = makeCard(valueString, suit);
                                if (card.isValid())
                                {
                                    hand->deal(card);
                                }
                            }
                        }
                    }
                    if (!(valueFound && suitFound))
                    {
                        cout << "Could not find 'suit' and/or 'value' in Hand " << handIdx + 1 << " Card " << cardIdx + 1 << endl;
                    }
                }
                players->push_back(*hand);
            }

            if (players->size() > 1)
            {
                int winnerIdx = scorer->findBestHand(players);
                printResults(winnerIdx, players);
            }
        }
        catch (const SettingNotFoundException &nfex)
        {
            cout << nfex.what() << ": Could not find 'hands' in " << path << endl;
        }
    }
    return 0;
}