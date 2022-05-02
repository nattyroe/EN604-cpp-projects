#include "card.h"
#include "hand.h"
#include "scorer.h"
#include <iostream>
#include <vector>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;
// @file
// @author Nathan Roe
// Compares Poker Hands provided in file to find winners
//
// Given a set of hands, will evaluate the Poker Hand Type
// and determine the winner or winners.

// Creates Card object using integer value and string suit
Card makeCard(int value, string suit)
{
    Card::Value cardValue = Card::Value::Invalid;
    Card::Suit cardSuit = Card::Suit::Invalid;
    // Set card value
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

    // Set card suit
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
} // End function makeCard

// Creates Card object using string value and suit
Card makeCard(string value, string suit)
{
    Card::Value cardValue = Card::Value::Invalid;
    Card::Suit cardSuit = Card::Suit::Invalid;

    // Set value for Ten through Ace
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
    // If card is not 10-Ace, try to set based on numerical value
    else
    {
        try
        {
            cardValue = static_cast<Card::Value>(stoi(value));
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << ": Invalid Card Value: " << value << endl;
            cardValue = Card::Value::Invalid;
        }
        catch (const exception &e)
        {
            cout << e.what() << ": Invalid Card Value: " << value << endl;
            cardValue = Card::Value::Invalid;
        }
    }

    // Set suit value
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
} // End function makeCard

// Format and print test results for input files
void printResults(int lastWinIdx, vector<Hand*> *players)
{
    // Print out error message if error value returned
    if (lastWinIdx == -1)
    {
        cout << "ERROR IN SCENARIO" << endl;
        return;
    }

    // Print out winning hands
    cout << "(" << players->at(0)->printCards() << ")";
    for (int idx = 1; idx <= lastWinIdx; ++idx)
    {
        cout << ", "
             << "(" << players->at(idx)->printCards() << ")";
    }
    // Format string based on whether ties are present
    if (lastWinIdx > 0)
    {
        cout << " Tie for the Win.";
    }
    else
    {
        cout << " Wins.";
    }

    // Print out losing hands
    bool multiLoser = false;
    for (int idx = lastWinIdx + 1; idx < players->size(); ++idx)
    {
        cout << " "
             << "(" << players->at(idx)->printCards() << ")";
        if (idx < players->size() - 1)
        {
            multiLoser = true;
            cout << " and";
        }
    }
    // Format string based on presence of multiple losing hands
    if (multiLoser)
    {
        cout << " Lose.";
    }
    else if (lastWinIdx < players->size() - 1)
    {
        cout << " Loses.";
    }
    cout << endl;
} // End function printResults

// Main function; runs Poker Hand Scorer for each input file provided
int main(int argc, char **argv)
{
    Scorer *scorer = new Scorer();

    // Iterate through input args, and read as paths
    for (int idx = 1; idx < argc; ++idx)
    {
        Config *cfg = new Config();
        char *path = argv[idx];

        // Attempt to parse Config files
        try
        {
            cout << path << endl;
            cfg->readFile(path);
        }
        // Catch file path errors
        catch (const FileIOException &fioex)
        {
            cerr << fioex.what() << " while reading file " << path << endl;
            return (EXIT_FAILURE);
        }
        // Catch config file format errors
        catch (const ParseException &pex)
        {
            cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                 << " - " << pex.getError() << endl;
            return (EXIT_FAILURE);
        }

        vector<Hand*> *players = new vector<Hand*>;

        const Setting &root = cfg->getRoot();
        // Find "hands" data set in config file
        try
        {
            const Setting &hands = root["hands"];
            int numHands = hands.getLength();

            // Create a Hand object for each hand in Config
            for (int handIdx = 0; handIdx < numHands; ++handIdx)
            {

                Hand *hand = new Hand();

                // Read Cards list in config
                const Setting &cards = hands[handIdx];
                int numCards = cards.getLength();
                for (int cardIdx = 0; cardIdx < numCards; ++cardIdx)
                {
                    const Setting &card = cards[cardIdx];

                    string suit;
                    bool suitFound = false;
                    bool valueFound = false;

                    // Find required suit and value
                    suitFound = card.lookupValue("suit", suit);
                    if (suitFound)
                    {
                        int value;
                        string valueString;
                        // Search for card values formatted as Integers
                        valueFound = card.lookupValue("value", value);
                        if (valueFound)
                        {
                            Card card = makeCard(value, suit);
                            // Add valid card to hand
                            if (card.isValid())
                            {
                                hand->deal(&card);
                            }
                        }
                        else
                        {
                            // Search for card values formatted as Strings
                            valueFound = card.lookupValue("value", valueString);
                            if (valueFound)
                            {
                                Card card = makeCard(valueString, suit);
                                // Add valid card to hand
                                if (card.isValid())
                                {
                                    hand->deal(&card);
                                }
                            }
                        }
                    }
                    // Print error for bad hand
                    if (!(valueFound && suitFound))
                    {
                        cout << "Could not find 'suit' and/or 'value' in Hand " << handIdx + 1 << " Card " << cardIdx + 1 << endl;
                    }
                }
                players->push_back(hand);
            }

            // Run scorer if multiple hands present
            if (players->size() > 1)
            {
                int winnerIdx = scorer->findBestHand(players);
                for (Hand *hand : *players)
                {
                    cout << "(" << hand->printCards() << "): " << hand->printHandType() << endl;
                }
                printResults(winnerIdx, players);
            }
        }
        // Print error message for improperly formatted file
        catch (const SettingNotFoundException &nfex)
        {
            cout << nfex.what() << ": Could not find 'hands' in " << path << endl;
        }
    }
    return 0;
} // End function main
