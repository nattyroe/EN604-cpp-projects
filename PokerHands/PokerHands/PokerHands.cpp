#include "card.h"
#include "hand.h"
#include <iostream>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;


int main(int argc, char** argv)
{
    for (int path = 1; path < argc; ++path)
    {
        Config *cfg = new Config();
        try
        {
            cout << argv[path] << endl;
 //           cfg->readFile(argv[path]);
        }
        catch (const ConfigException& fioex)
        {
            cerr << "I/O error while reading file." << endl;
            return(EXIT_FAILURE);
        }

        Hand* hand = new Hand();
        hand->deal(Card(Card::Value::Eight, Card::Suit::Clubs));
        hand->deal(Card(Card::Value::Ace, Card::Suit::Clubs));
        hand->deal(Card(Card::Value::Three, Card::Suit::Diamonds));
        hand->deal(Card(Card::Value::Three, Card::Suit::Diamonds));

        hand->printCards();
    }
    return 0;
}