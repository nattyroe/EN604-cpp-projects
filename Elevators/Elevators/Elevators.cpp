#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Building.h"

using namespace std;

int main()
{
    Building *building = new Building();

    int passenger;
    int startTime;
    int startFloor;
    int endFloor;

    vector<string> row;
    string line;
    string word;
    string temp;


    fstream fin;
    fin.open("../Input/Elevator.csv", ios::in);
    while (fin >> temp)
    {
        row.clear();

        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        try
        {
            passenger = stoi(row[0]);
            startTime = stoi(row[1]);
            startFloor = stoi(row[2]);
            endFloor = stoi(row[3]);
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
        }
    }

}
