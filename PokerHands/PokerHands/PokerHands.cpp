#include "card.h"
#include "hand.h"
#include <iostream>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;




int main(int argc, char** argv)
{
    for (int idx = 1; idx < argc; ++idx)
    {
        Config* cfg = new Config();
        char* path = argv[idx];
        try
        {
            cout << path << endl;
            cfg->readFile(path);
        }
        catch (const FileIOException& fioex)
        {
            cerr << fioex.what() << " while reading file " << path << endl;
            return(EXIT_FAILURE);
        }
        catch (const ParseException& pex)
        {
            cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << endl;
            return(EXIT_FAILURE);
        }

        const Setting& root = cfg->getRoot();
        try
        {
            const Setting &hands = root["hands"];
            int numHands = hands.getLength();

            for (int handIdx = 0; handIdx < numHands; ++handIdx)
            {
                const Setting& cards = hands[handIdx];
                int numCards = cards.getLength();
                for (int cardIdx = 0; cardIdx < numCards; ++cardIdx)
                {
                    const Setting& card = cards[cardIdx];

                    string suit;
                    bool suitFound = false;
                    bool valueFound = false;

                    suitFound = card.lookupValue("suit", suit);
                    if (suitFound)
                    {
                        int value;
                        string valueString;
                        valueFound = card.lookupValue("value", value);
                        if (valueFound)
                        {
                            cout << "INT value found" << endl;
                        }
                        else
                        {
                            valueFound = card.lookupValue("value", valueString);
                            if (valueFound)
                            {
                                cout << "STRING value found" << endl;
                            }
                        }
                    }
                    if (!(valueFound && suitFound))
                    {
                        cout << "Could not find 'suit' and/or 'value' in Hand " << handIdx + 1 << " Card " << cardIdx + 1 << endl;
                    }
                }
            }
        }
        catch (const SettingNotFoundException& nfex)
        {
            cout << nfex.what() << ": Could not find 'hands' in " << path << endl;
        }

        Hand* hand = new Hand();

        hand->printCards();
    }
    return 0;
}